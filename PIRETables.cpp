#include "stdafx.h"
#include "PIRETables.h"
#include "StringUtils.h"

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

std::string PireTable::SELECT_ALL = " * ";

PireTable::PireTable()
{
}

PireTable::PireTable(const std::string & sIP, const std::string & sUser, const std::string & sPassword)
{
	connect(sIP, sUser, sPassword);
}

PireTable::PireTable(std::shared_ptr<sql::Connection> newConn)
{
	setConnection(newConn);
}

PireTable::PireTable(const PireTable & pt) : con(pt.con)
{
}

PireTable::PireTable(const JoinTable & jt) : con(jt.con)
{
}

bool PireTable::connect(const std::string & sIP, const std::string & sUser, const std::string & sPassword)
{
	/* Create a connection */
	sql::Driver *driver = get_driver_instance();
	if (!driver) {
		std::cerr << "Could not find driver.\n";
		return false;
	}
	con.reset(driver->connect(sIP, sUser, sPassword));
	if (!con) {
		std::cerr << "Could not connect.\n";
		return false;
	}
	con->setSchema("sar_test_db");

	return true;
}

bool PireTable::setConnection(std::shared_ptr<sql::Connection> newConn)
{
	con = newConn;
	return con.get() && con->isValid();
}

std::shared_ptr<sql::Connection> PireTable::getConnection()
{
	return this->con;
}

std::string PireTable::getColumnName(int iCol) const
{
	auto iter = mapCols.find(iCol);
	return iter == mapCols.end() ? std::string() : iter->second;
}

int PireTable::generateTable()
{
	int iRet = -1;
	if (con && con->isValid()) {
		sQuery = getTableSQL();
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}
	return iRet;
}

std::string PireTable::getTableSQL() const
{
	return std::string();
}

std::string PireTable::getQuery() const
{
	return sQuery;
}

void PireTable::clearQuery()
{
	sQuery = "";
}

void PireTable::clearWhere()
{
	sWhere = "";
}

void PireTable::clearSet()
{
	sSet = "";
}

std::string PireTable::escapeString(const std::string & sEsc) const
{
	std::string sRet;
	if (con) {
		sRet = dynamic_cast<sql::mysql::MySQL_Connection*>(con.get())->escapeString(sEsc);
	}
	else {
		sRet = StringUtils::replace(sEsc, "'", "\\'");
	}
	return sRet;
}

std::string PireTable::quote(const std::string & sQuote) const
{
	return "'" + escapeString(sQuote) + "'";
}

std::string PireTable::sanitize(const std::string & sInput)
{
	return StringUtils::replace(sInput, " .,;:\'\"`~!@#$%^&*()=+?/\\\n", "", false);
}

int PireTable::deleteRows()
{
	int iRet = -1;
	if (con && con->isValid()) {
		sQuery = "DELETE FROM " + getTableName() + " " + sWhere;
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}
	return iRet;
}

std::string PireTable::getCompare(MatchType e)
{
	std::string sRet;
	switch (e) {
	case Equal:
		sRet = " = ";
		break;
	case NotEqual:
		sRet = " <> ";
		break;
	case Like:
		sRet = " LIKE ";
		break;
	case LessThan:
		sRet = " < ";
		break;
	case GreaterThan:
		sRet = " > ";
		break;
	case LessThanEq:
		sRet = " <= ";
		break;
	case GreaterThanEq:
		sRet = " >= ";
		break;
	default:
		break;
	}
	return sRet;
}

std::string PireTable::getOperation(Operation e)
{
	std::string sRet;
	switch (e) {
	case AND:
		sRet = " AND ";
		break;
	case OR:
		sRet = " OR ";
		break;
	case XOR:
		sRet = " XOR ";
		break;
	case NOT:
		sRet = " NOT ";
		break;
	default:
		break;
	}
	return sRet;
}

std::string PireTable::getAggregate(Aggregate e)
{
	std::string sRet;
	switch (e) {
	case PireTable::COUNT:
		sRet = "COUNT";
		break;
	case PireTable::MIN:
		sRet = "MIN";
		break;
	case PireTable::AVG:
		sRet = "AVG";
		break;
	case PireTable::MAX:
		sRet = "MAX";
		break;
	case PireTable::SUM:
		sRet = "SUM";
		break;
	default:
		break;
	}

	return sRet;
}

void PireTable::addSelect(int iCol)
{
	if (!sSelect.empty()) {
		sSelect += ", ";
	}

	sSelect += getColumnName(iCol);
}

void PireTable::addAggregateSelect(Aggregate e, int iCol, bool bAll)
{
	if (!sSelect.empty()) {
		sSelect += ",";
	}
	sSelect += " " + getAggregate(e) + "(";
	sSelect += bAll ? " ALL " : " DISTINCT ";
	sSelect += getColumnName(iCol) + " )";
}

void PireTable::addSelect(const SQLExpression & sqle)
{
	if (!sSelect.empty()) {
		sSelect += ", ";
	}

	sSelect += sqle.toString();
}

void PireTable::clearSelect()
{
	sSelect = "";
}

std::string PireTable::getSelect() const
{
	return sSelect.empty() ? PireTable::SELECT_ALL : sSelect;
}

std::string PireTable::getFrom() const
{
	return getTableName();
}

std::string PireTable::getWhere() const
{
	return sWhere;
}

std::shared_ptr<sql::ResultSet> PireTable::selectRows(bool bDistinct)
{
	std::shared_ptr<sql::ResultSet> rs;
	if (con && con->isValid()) {
		if (sUnion.empty()) {
			sQuery = getSelectQuery(bDistinct);
		}
		else {
			sQuery = sUnion + getEndingClause();
		}
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		rs.reset(stmt->executeQuery(sQuery));
	}
	return rs;
}

/**
* Select Rows From Source
*/
std::vector< std::vector<std::string> > PireTable::selectRowStrings(bool bDistinct)
{
	std::vector< std::vector<std::string> > vecRows;
	std::shared_ptr<sql::ResultSet> rs = selectRows(bDistinct);
	if (rs) {
		while (rs->next()) {
			std::vector<std::string> vecRow(rs->getMetaData()->getColumnCount(), std::string());
			for (int i = 1; i <= rs->getMetaData()->getColumnCount(); ++i) {
				vecRow[i - 1] = rs->getString(i);
			}
			vecRows.push_back(vecRow);
		}
	}
	return vecRows;
}

int PireTable::updateRows()
{
	int iRet = -1;
	if (con && con->isValid() && !sSet.empty()) {
		sQuery = "UPDATE " + getTableName() + " SET " + sSet + " " + sWhere;
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}
	return iRet;
}

std::string PireTable::getSelectQuery(bool bDistinct) const
{
	std::string sQuery = "SELECT ";
	if (bDistinct) {
		sQuery += "DISTINCT ";
	}
	sQuery += getSelect() + " FROM " + getFrom() + " " + sWhere;
	sQuery += getEndingClause();

	return sQuery;
}

bool PireTable::Union(const PireTable & table, bool bALL, bool bChain, bool bClear)
{
	bool bOK = getTableName() == table.getTableName();
	if (bOK) {
		if (bChain && !sUnion.empty()) {
			sUnion += " UNION ";
		}
		else {
			sUnion = "( " + getSelectQuery() + " ) UNION ";
		}

		if (bALL) {
			sUnion += "ALL ";
		}
		sUnion += "( " + table.getSelectQuery() + " )";

		if (bClear) {
			clearSelect();
			clearWhere();
		}
	}
	return bOK;
}

std::string PireTable::getUnion() const
{
	return sUnion;
}

std::string PireTable::getEndingClause() const
{
	std::string sQuery;
	if (!sGroupBy.empty()) {
		sQuery += " " + sGroupBy;
		if (!sHaving.empty()) {
			sQuery += sHaving;
		}
	}

	if (!sOrderBy.empty()) {
		sQuery += " " + sOrderBy;
	}

	if (iLimit > 0) {
		sQuery += " LIMIT " + std::to_string(iLimit);
	}

	if (iOffset > 0) {
		sQuery += " OFFSET " + std::to_string(iOffset);
	}

	return sQuery;
}

void PireTable::addOrderBy(int iCol, bool bAsc)
{
	if (sOrderBy.empty()) {
		sOrderBy += " ORDER BY ";
	}
	else {
		sOrderBy += ", ";
	}

	sOrderBy += getColumnName(iCol);
	sOrderBy += bAsc ? " ASC " : " DESC ";
}

void PireTable::addGroupBy(int iCol)
{
	if (sGroupBy.empty()) {
		sGroupBy += " GROUP BY ";
	}
	else {
		sGroupBy += ", ";
	}

	sGroupBy += getColumnName(iCol);
}

void PireTable::clearOrderBy()
{
	sOrderBy.clear();
}

void PireTable::clearGroupBy()
{
	sGroupBy.clear();
}

void PireTable::setLimit(int i)
{
	iLimit = i;
}

void PireTable::setOffset(int i)
{
	iOffset = i;
}

void PireTable::addHaving(Operation eOp, Aggregate eAgg, int iCol, bool bAll, MatchType eCom, double dVal)
{
	if (sHaving.empty()) {
		sHaving = " HAVING ";
	}
	else {
		sHaving += getOperation(eOp);
	}

	sHaving += getAggregate(eAgg) + "(";
	sHaving += bAll ? "ALL " : "DISTINCT ";
	sHaving += getColumnName(iCol) + ") ";
	sHaving += getCompare(eCom) + " ";
	sHaving += std::to_string(dVal);
}

std::map<int, std::string> PireTable::getColumnMap() const
{
	return mapCols;
}

size_t PireTable::getColumnCount() const
{
	return mapCols.size();
}

bool PireTable::setAlias(const std::string & sA)
{
	sAlias = sanitize(sA);
	bool bOK = sAlias == sA;
	if (!bOK) {
		clearAlias();
	}
	return bOK;
}

void PireTable::clearAlias()
{
	sAlias.clear();
}

ModelTable::ModelTable(const std::string & sIP, const std::string & sUser, const std::string & sPassword) : PireTable(sIP, sUser, sPassword)
{
	mapCols = initColumnMap();
}

ModelTable::ModelTable(std::shared_ptr<sql::Connection> newConn) : PireTable(newConn)
{
	mapCols = initColumnMap();
}

std::map<int, std::string> ModelTable::initColumnMap() const
{
	return {
		{model, "model"},
		ValNamePair(height),
		ValNamePair(width),
		ValNamePair(depth),
		ValNamePair(mass),
		ValNamePair(model_type),
		ValNamePair(description)
	};
}

int ModelTable::insertRow(std::string sModel, double dH, double dW, double dD, double dM, std::string sType, const std::string &sDescription)
{
	int iRet = -1;
	if (con && con->isValid()) {
		sQuery = "INSERT INTO " + getTableName() + " VALUES (" + quote(sModel) + "," + std::to_string(dH) + "," + std::to_string(dW)
			+ "," + std::to_string(dD) + "," + std::to_string(dM) + "," + quote(sType) + "," + quote(sDescription) + ")";
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}
	
	return iRet;
}

ModelResolutionTable::ModelResolutionTable(const std::string & sIP, const std::string & sUser, const std::string & sPassword) : PireTable(sIP, sUser, sPassword)
{
	mapCols = initColumnMap();
}

ModelResolutionTable::ModelResolutionTable(std::shared_ptr<sql::Connection> newConn) : PireTable(newConn)
{
	mapCols = initColumnMap();
}

std::map<int, std::string> ModelResolutionTable::initColumnMap() const
{
	return {
		ValNamePair(model),
		ValNamePair(model_res),
		ValNamePair(nx),
		ValNamePair(ny),
		ValNamePair(nz),
		ValNamePair(dx),
		ValNamePair(dy),
		ValNamePair(dz)
	};
}

int ModelResolutionTable::insertRow(std::string sModel, std::string sModelRes, double dNX, double dNY, double dNZ, double dDX, double dDY, double dDZ)
{
	int iRet = -1;
	if (con && con->isValid()) {
		sQuery = "INSERT INTO " + getTableName() + " VALUES (" + quote(sModel) + "," + quote(sModelRes) + "," + std::to_string(dNX) + "," + std::to_string(dNY)
			+ "," + std::to_string(dNZ) + "," + std::to_string(dDX) + "," + std::to_string(dDY) + "," + std::to_string(dDZ) + ")";
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}

	return iRet;
}

SimInputTable::SimInputTable(const std::string & sIP, const std::string & sUser, const std::string & sPassword) : PireTable(sIP, sUser, sPassword)
{
	mapCols = initColumnMap();
}

SimInputTable::SimInputTable(std::shared_ptr<sql::Connection> newConn) : PireTable(newConn)
{
	mapCols = initColumnMap();
}

std::map<int, std::string> SimInputTable::initColumnMap() const
{
	return {
		ValNamePair(model),
		ValNamePair(model_res),
		ValNamePair(frequency),
		ValNamePair(power_density),
		ValNamePair(power_limit),
		ValNamePair(theta),
		ValNamePair(phi),
		ValNamePair(polarization),
		ValNamePair(duration),
		ValNamePair(material),
		ValNamePair(sim_id)
	};
}

int SimInputTable::insertRow(std::string sModel, std::string sModelRes, double dFreq, double dPowerDensity, double dPowerLimit, double dTheta, double dPhi, double dPolarization, double dDuration, std::string sMaterial, double dID)
{
	int iRet = -1;
	if (con && con->isValid()) {
		sQuery = "INSERT INTO " + getTableName() + " VALUES (" + quote(sModel) + "," + quote(sModelRes) + "," + std::to_string(dFreq)
			+ "," + std::to_string(dPowerDensity) + "," + std::to_string(dPowerLimit) + "," + std::to_string(dTheta) + ","
			+ std::to_string(dPhi) + "," + std::to_string(dPolarization) + "," + std::to_string(dDuration) + "," + quote(sMaterial) +
			"," + std::to_string(dID) + ")";
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}

	return iRet;
}

SimOutputTable::SimOutputTable(const std::string & sIP, const std::string & sUser, const std::string & sPassword) : PireTable(sIP, sUser, sPassword)
{
	mapCols = initColumnMap();
}

SimOutputTable::SimOutputTable(std::shared_ptr<sql::Connection> newConn) : PireTable(newConn)
{
	mapCols = initColumnMap();
}

std::map<int, std::string> SimOutputTable::initColumnMap() const
{
	return {
		ValNamePair(output_id),
		ValNamePair(output_tissue),
		ValNamePair(output_name),
		ValNamePair(output_value)
	};
}

int SimOutputTable::insertRow(double dID, const std::string & sTissue, const std::string & sName, double dValue)
{
	int iRet = -1;
	if (con && con->isValid()) {
		sQuery = "INSERT INTO " + getTableName() + " VALUES (" + std::to_string(dID) + ","
			+ quote(sTissue) + "," + quote(sName) + "," + std::to_string(dValue) + ")";
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}

	return iRet;
}

ThermalTissueTable::ThermalTissueTable(const std::string & sIP, const std::string & sUser, const std::string & sPassword) : PireTable(sIP, sUser, sPassword)
{
	mapCols = initColumnMap();
}

ThermalTissueTable::ThermalTissueTable(std::shared_ptr<sql::Connection> newConn) : PireTable(newConn)
{
	mapCols = initColumnMap();
}

std::map<int, std::string> ThermalTissueTable::initColumnMap() const
{
	return {
		ValNamePair(model),
		ValNamePair(Tissue_label),
		ValNamePair(tissue_ID),
		ValNamePair(Density),
		ValNamePair(HeatCapacity),
		ValNamePair(Conductivity),
		ValNamePair(PerfusionRate),
		ValNamePair(MetabolicRate)
	};
}

int ThermalTissueTable::insertRow(const std::string & sModel, const std::string & sLable, double dID, double dDensity, double dConductivity, double dHeatCapacity, double dPerfusionRate, double dMetabolicRate)
{
	int iRet = -1;
	if (con && con->isValid()) {
		sQuery = "INSERT INTO " + getTableName() + " VALUES (" + quote(sModel) + "," + quote(sLable) + "," + std::to_string(dID)
			+ "," + std::to_string(dDensity) + "," + std::to_string(dConductivity) + "," + std::to_string(dHeatCapacity)
			+ "," + std::to_string(dPerfusionRate) + "," + std::to_string(dMetabolicRate) + ")";
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}

	return iRet;
}

ITISTissueTable::ITISTissueTable(const std::string & sIP, const std::string & sUser, const std::string & sPassword) : PireTable(sIP, sUser, sPassword)
{
	mapCols = initColumnMap();
}

ITISTissueTable::ITISTissueTable(std::shared_ptr<sql::Connection> newConn) : PireTable(newConn)
{
	mapCols = initColumnMap();
}

std::map<int, std::string> ITISTissueTable::initColumnMap() const
{
	return {
		ValNamePair(tissue_name),
		ValNamePair(itis_version),
		ValNamePair(Density_avg),
		ValNamePair(Density_min),
		ValNamePair(Density_max),
		ValNamePair(HeatCapacity_avg),
		ValNamePair(HeatCapacity_min),
		ValNamePair(HeatCapacity_max),
		ValNamePair(Conductivity_avg),
		ValNamePair(Conductivity_min),
		ValNamePair(Conductivity_max),
		ValNamePair(HeatTransferRate_avg),
		ValNamePair(HeatTransferRate_min),
		ValNamePair(HeatTransferRate_max),
		ValNamePair(HeatGenerationRate_avg),
		ValNamePair(HeatGenerationRate_min),
		ValNamePair(HeatGenerationRate_max),
		ValNamePair(ef),
		ValNamePair(del1),
		ValNamePair(tau1),
		ValNamePair(alf1),
		ValNamePair(del2),
		ValNamePair(tau2),
		ValNamePair(alf2),
		ValNamePair(sig),
		ValNamePair(del3),
		ValNamePair(tau3),
		ValNamePair(alf3),
		ValNamePair(del4),
		ValNamePair(tau4),
		ValNamePair(alf4)
	};
}

int ITISTissueTable::insertRow(const std::string & sName, const std::string & sVersion,
	double dDenAvg, double dDenMin, double dDenMax,
	double dHCAvg, double dHCMin, double dHCMax,
	double dCondAvg, double dCondMin, double dCondMax,
	double dHTAvg, double dHTMin, double dHTMax,
	double dHGAvg, double dHGMin, double dHGMax,
	double def, double ddel1, double dtau1, double dalf1, double ddel2, double dtau2, double dalf2,
	double dsig, double ddel3, double dtau3, double dalf3, double ddel4, double dtau4, double dalf4)
{
	int iRet = -1;
	if (con && con->isValid()) {
		sQuery = "INSERT INTO " + getTableName() + " VALUES (" + quote(sName) + "," + quote(sVersion)
			+ ","+ std::to_string(dDenAvg) + "," + std::to_string(dDenMin) + "," + std::to_string(dDenMax)
			+ "," + std::to_string(dHCAvg) + "," + std::to_string(dHCMin) + "," + std::to_string(dHCMax)
			+ "," + std::to_string(dCondAvg) + "," + std::to_string(dCondMin) + "," + std::to_string(dCondMax)
			+ "," + std::to_string(dHTAvg) + "," + std::to_string(dHTMin) + "," + std::to_string(dHTMax)
			+ "," + std::to_string(dHGAvg) + "," + std::to_string(dHGMin) + "," + std::to_string(dHGMax)
			+ "," + std::to_string(def)  + "," + std::to_string(ddel1) + "," + std::to_string(dtau1) + "," + std::to_string(dalf1)
		                                 + "," + std::to_string(ddel2) + "," + std::to_string(dtau2) + "," + std::to_string(dalf2)
			+ "," + std::to_string(dsig) + "," + std::to_string(ddel3) + "," + std::to_string(dtau3) + "," + std::to_string(dalf3)
			                             + "," + std::to_string(ddel4) + "," + std::to_string(dtau4) + "," + std::to_string(dalf4)
			+ ")";
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}

	return iRet;
}

JoinTable::JoinTable(const std::string & sIP, const std::string & sUser, const std::string & sPassword) : PireTable(sIP, sUser, sPassword)
{
}

JoinTable::JoinTable(std::shared_ptr<sql::Connection> newConn) : PireTable(newConn)
{
}

JoinTable::JoinTable(const PireTable & pt) : PireTable(pt)
{
}

JoinTable::JoinTable(const JoinTable & jt) : PireTable(jt)
{
}

std::string JoinTable::getFrom() const
{
	return sFrom + " " + sOn;
}

std::string JoinTable::getJoin(JoinType eJoin) const
{
	std::string sRet;
	switch (eJoin) {
	case INNER:
		sRet = " INNER JOIN ";
		break;
	case LEFT:
		sRet = " LEFT JOIN ";
		break;
	case RIGHT:
		sRet = " RIGHT JOIN ";
		break;
	case FULL:
		sRet = " FULL OUTER JOIN ";
		break;
	case CROSS:
		sRet = " CROSS JOIN ";
		break;
	default:
		break;
	}
	return sRet;
}

void JoinTable::joinTables(JoinType eJoin, const PireTable & ptLeft, const PireTable & ptRight, const std::string & sLeftAlias, const std::string & sRightAlias)
{
	if (!sFrom.empty()) {
		if (!sOn.empty()) {
			sFrom += " " + sOn + " ";
			sOn.clear();
		}

		sFrom += getJoin(eJoin);
	}

	sFrom += " " + ptLeft.getFrom();
	if (!sLeftAlias.empty()) {
		std::string sTmp = PireTable::sanitize(sLeftAlias);
		sFrom += " AS " + sTmp;
		vecTables.push_back(sTmp);
	}
	else {
		vecTables.push_back(ptLeft.getFrom());
	}
	
	sFrom += getJoin(eJoin) + " " + ptRight.getFrom();
	if (!sRightAlias.empty()) {
		std::string sTmp = PireTable::sanitize(sRightAlias);
		sFrom += " AS " + sTmp;
		vecTables.push_back(sTmp);
	}
	else {
		vecTables.push_back(ptRight.getFrom());
	}
}

void JoinTable::joinTable(JoinType eJoin, const PireTable & pt, const std::string & sAlias)
{
	if (!sFrom.empty()) {
		if (!sOn.empty()) {
			sFrom += " " + sOn + " ";
			sOn.clear();
		}

		sFrom += getJoin(eJoin);
	}

	sFrom += " " + pt.getFrom();
	if (!sAlias.empty()) {
		std::string sTmp = PireTable::sanitize(sAlias);
		sFrom += " AS " + sTmp;
		vecTables.push_back(sTmp);
	}
	else {
		vecTables.push_back(pt.getFrom());
	}
	vecMapCols.push_back(pt.mapCols);
}

bool JoinTable::addOn(Operation eOp, int iTableLeft, int iColumnLeft, MatchType eMatch, int iTableRight, int iColumnRight)
{
	std::string sLeft = getTableColumn(iTableLeft, iColumnLeft);
	std::string sRight = getTableColumn(iTableRight, iColumnRight);
	bool bOK = !sLeft.empty() && !sRight.empty();
	if (bOK) {
		if (sOn.empty()) {
			sOn = " ON";
		}
		else {
			sOn += " " + getOperation(eOp);
		}

		sOn += " " + sLeft + getCompare(eMatch) + sRight;
	}

	return bOK;
}

std::string JoinTable::getTableColumn(int iTable, int iColumn)
{
	std::string sRet;
	if (iTable >= 0 && iTable < vecTables.size() && !vecTables[iTable].empty() && iColumn >= 0 && iTable < vecMapCols.size()) {
		auto mapIter = vecMapCols[iTable].find(iColumn);
		if (mapIter != vecMapCols[iTable].end() && !mapIter->second.empty()) {
			sRet = vecTables[iTable] + "." + mapIter->second;
		}
	}

	return sRet;
}

void JoinTable::clearJoin()
{
	vecTables.clear();
	vecMapCols.clear();
	sFrom.clear();
	sOn.clear();
}

std::string JoinTable::getColumnName(int iCol) const
{
	std::string sRet;
	if (iCol >= 0) {
		int iTmp = iCol;
		for (int iTable = 0; iTable < vecMapCols.size(); ++iTable) {
			if (iTmp < vecMapCols[iTable].size()) {
				auto mapIter = vecMapCols[iTable].find(iTmp);
				if (mapIter != vecMapCols[iTable].end() && !mapIter->second.empty()) {
					sRet = vecTables[iTable] + "." + mapIter->second;
				}
				break;
			}
			else {
				iTmp -= vecMapCols[iTable].size();
			}
		}
	}

	return sRet;
}

int JoinTable::getColumnIndex(int iTable, int iCol)
{
	int iRet = -1;
	if (iTable >= 0 && iCol >= 0 && iTable < vecTables.size() && iCol < vecMapCols[iTable].size()) {
		int iRet = iCol;
		for (size_t i = 0; i < iTable; ++i) {
			iRet += vecMapCols[i].size();
		}
	}
	return iRet;
}

size_t JoinTable::getColumnCount() const
{
	size_t tRet = 0;
	for (size_t i = 0; i < vecMapCols.size(); ++i) {
		tRet += vecMapCols[i].size();
	}

	return tRet;
}

void JoinTable::beginTransaction()
{
	if (con) {
		con->setAutoCommit(false);
	}
}

bool JoinTable::endTransaction(bool bCommit)
{
	if (con) {
		if (bCommit) {
			con->commit();
		}
		else {
			con->rollback();
		}
		con->setAutoCommit(true);
	}
	return con && bCommit;
}

SubQuery::SubQuery(const std::string & sIP, const std::string & sUser, const std::string & sPassword) : PireTable(sIP, sUser, sPassword)
{
}

SubQuery::SubQuery(std::shared_ptr<sql::Connection> newConn) : PireTable(newConn)
{
}

SubQuery::SubQuery(const PireTable & pt) : PireTable(pt)
{
}

std::string SubQuery::getFrom() const
{
	return sFrom;
}

void SubQuery::setSubQuery(const PireTable & pt, const std::string sAlias)
{
	sFrom = "(" + pt.getSelectQuery() + ") AS " + PireTable::sanitize(sAlias);
	if (pt.getSelect() == PireTable::SELECT_ALL) {
		mapCols = pt.getColumnMap();
	}
	else {
		setColumnsFromSelect(pt.getSelect(), sAlias);
	}
}

void SubQuery::clearSubQuery()
{
	sFrom.clear();
	mapCols.clear();
}

void SubQuery::setColumnsFromSelect(std::string sSelect, std::string sTable)
{
	sTable = PireTable::sanitize(sTable);
	std::vector<std::string> vecCols;
	StringUtils::split(sSelect, ",", vecCols);
	for (size_t i = 0; i < vecCols.size(); ++i) {
		std::string sTmp = vecCols[i];
		if (sTmp.find(" AS ") != std::string::npos) {
			sTmp = sTmp.substr(sTmp.find(" AS ") + 4);
			
		}

		sTmp = PireTable::sanitize(sTmp);

		if (!sTable.empty()) {
			sTmp = sTable + "." + sTmp;
		}

		mapCols[i] = sTmp;
	}
}

