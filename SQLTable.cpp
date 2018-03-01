#include "SQLTable.h"

#include "stdafx.h"
#include "SQLTable.h"
#include "StringUtils.h"

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

std::string SQLTable::SELECT_ALL = " * ";

SQLTable::SQLTable()
{
}

SQLTable::SQLTable(const std::string & sIP, const std::string & sUser, const std::string & sPassword)
{
	connect(sIP, sUser, sPassword);
}

SQLTable::SQLTable(std::shared_ptr<sql::Connection> newConn)
{
	setConnection(newConn);
}

SQLTable::SQLTable(const SQLTable & pt) : con(pt.con)
{
}

SQLTable::SQLTable(const JoinTable & jt) : con(jt.con)
{
}

bool SQLTable::connect(const std::string & sIP, const std::string & sUser, const std::string & sPassword)
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

bool SQLTable::setConnection(std::shared_ptr<sql::Connection> newConn)
{
	con = newConn;
	return con.get() && con->isValid();
}

std::shared_ptr<sql::Connection> SQLTable::getConnection()
{
	return this->con;
}

std::string SQLTable::getColumnName(int iCol) const
{
	auto iter = mapCols.find(iCol);
	return iter == mapCols.end() ? std::string() : iter->second;
}

int SQLTable::generateTable()
{
	int iRet = -1;
	if (con && con->isValid()) {
		sQuery = getTableSQL();
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}
	return iRet;
}

std::string SQLTable::getTableSQL() const
{
	return std::string();
}

std::string SQLTable::getQuery() const
{
	return sQuery;
}

void SQLTable::clearQuery()
{
	sQuery = "";
}

void SQLTable::clearWhere()
{
	sWhere = "";
}

std::string SQLTable::escapeString(const std::string & sEsc) const
{
	std::string sRet;
	if (con) {
		sRet = dynamic_cast<sql::mysql::MySQL_Connection*>(con.get())->escapeString(sEsc);
	}
	else {
		sRet = escapeStringStatic(sEsc);
	}
	return sRet;
}

std::string SQLTable::escapeStringStatic(const std::string & sEsc)
{
	std::string sRet = StringUtils::replace(sEsc, "\\", "\\\\");
	sRet = StringUtils::replace(sRet, "'", "\\'");
	return sRet;
}

std::string SQLTable::quote(const std::string & sQuote) const
{
	return "'" + escapeString(sQuote) + "'";
}

std::string SQLTable::sanitize(const std::string & sInput)
{
	return StringUtils::replace(sInput, " .,;:\'\"`~!@#$%^&*()=+?/\\\n", "", false);
}

int SQLTable::deleteRows()
{
	int iRet = -1;
	if (con && con->isValid()) {
		sQuery = "DELETE FROM " + getTableName() + " " + sWhere;
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}
	return iRet;
}

std::string SQLTable::getCompare(MatchType e)
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

std::string SQLTable::getOperation(Operation e)
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

std::string SQLTable::getAggregate(Aggregate e)
{
	std::string sRet;
	switch (e) {
	case SQLTable::COUNT:
		sRet = "COUNT";
		break;
	case SQLTable::MIN:
		sRet = "MIN";
		break;
	case SQLTable::AVG:
		sRet = "AVG";
		break;
	case SQLTable::MAX:
		sRet = "MAX";
		break;
	case SQLTable::SUM:
		sRet = "SUM";
		break;
	default:
		break;
	}

	return sRet;
}

void SQLTable::addSelect(int iCol)
{
	if (!sSelect.empty()) {
		sSelect += ", ";
	}

	sSelect += getColumnName(iCol);
}

void SQLTable::addAggregateSelect(Aggregate e, int iCol, bool bAll)
{
	if (!sSelect.empty()) {
		sSelect += ",";
	}
	sSelect += " " + getAggregate(e) + "(";
	sSelect += bAll ? " ALL " : " DISTINCT ";
	sSelect += getColumnName(iCol) + " )";
}

void SQLTable::addSelect(const SQLExpression & sqle)
{
	if (!sSelect.empty()) {
		sSelect += ", ";
	}

	sSelect += sqle.toString();
}

void SQLTable::clearSelect()
{
	sSelect = "";
}

std::string SQLTable::getSelect() const
{
	return sSelect.empty() ? SQLTable::SELECT_ALL : sSelect;
}

std::string SQLTable::getFrom() const
{
	return getTableName();
}

std::string SQLTable::getWhere() const
{
	return sWhere;
}

std::shared_ptr<sql::ResultSet> SQLTable::selectRows(bool bDistinct)
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
std::vector< std::vector<std::string> > SQLTable::selectRowStrings(bool bDistinct)
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

std::string SQLTable::getSelectQuery(bool bDistinct) const
{
	std::string sQuery = "SELECT ";
	if (bDistinct) {
		sQuery += "DISTINCT ";
	}
	sQuery += getSelect() + " FROM " + getFrom() + " " + sWhere;
	sQuery += getEndingClause();

	return sQuery;
}

bool SQLTable::Union(const SQLTable & table, bool bALL, bool bChain, bool bClear)
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

std::string SQLTable::getUnion() const
{
	return sUnion;
}

std::string SQLTable::getEndingClause() const
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

void SQLTable::addOrderBy(int iCol, bool bAsc)
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

void SQLTable::addGroupBy(int iCol)
{
	if (sGroupBy.empty()) {
		sGroupBy += " GROUP BY ";
	}
	else {
		sGroupBy += ", ";
	}

	sGroupBy += getColumnName(iCol);
}

void SQLTable::clearOrderBy()
{
	sOrderBy.clear();
}

void SQLTable::clearGroupBy()
{
	sGroupBy.clear();
}

void SQLTable::setLimit(int i)
{
	iLimit = i;
}

void SQLTable::setOffset(int i)
{
	iOffset = i;
}

void SQLTable::addHaving(Operation eOp, Aggregate eAgg, int iCol, bool bAll, MatchType eCom, double dVal)
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

std::map<int, std::string> SQLTable::getColumnMap() const
{
	return mapCols;
}

size_t SQLTable::getColumnCount() const
{
	return mapCols.size();
}

bool SQLTable::setAlias(const std::string & sA)
{
	sAlias = sanitize(sA);
	bool bOK = sAlias == sA;
	if (!bOK) {
		clearAlias();
	}
	return bOK;
}

void SQLTable::clearAlias()
{
	sAlias.clear();
}


MutableSQLTable::MutableSQLTable() : SQLTable()
{
}

MutableSQLTable::MutableSQLTable(const std::string & sIP, const std::string & sUser, const std::string & sPassword) : SQLTable(sIP, sUser, sPassword)
{
}

MutableSQLTable::MutableSQLTable(std::shared_ptr<sql::Connection> newConn) : SQLTable(newConn)
{
}

MutableSQLTable::MutableSQLTable(const SQLTable & pt) : SQLTable(pt)
{
}

void MutableSQLTable::addSet(int iCol, const SQLExpression &sqle) {
	if (!sSet.empty()) {
		sSet += ", ";
	}
	sSet += getColumnName(iCol) + " = " + sqle.toString();
}

int MutableSQLTable::updateRows()
{
	int iRet = -1;
	if (con && con->isValid() && !sSet.empty()) {
		sQuery = "UPDATE " + getTableName() + " " + getSetQuery();
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}
	return iRet;
}

std::string MutableSQLTable::getSetQuery()
{
	return "SET " + sSet + " " + sWhere + " " + getEndingClause();
}

int MutableSQLTable::insertValues(bool bIgnore)
{
	int iRet = -1;
	if (con) {
		sQuery = "INSERT ";
		if (bIgnore) {
			sQuery += "IGNORE ";
		}
		sQuery += "INTO " + getTableName() + " " + sInsertCols + " VALUES " + sInsertValues + " " + getOnDuplicateKeyUpdate();
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}
	return iRet;
}

int MutableSQLTable::insertSelect(bool bIgnore)
{
	int iRet = -1;
	if (con) {
		sQuery = "INSERT ";
		if (bIgnore) {
			sQuery += "IGNORE ";
		}
		sQuery += sInsertCols + " " + getSelectQuery() + " " + getOnDuplicateKeyUpdate();
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}
	return iRet;
}

int MutableSQLTable::insertSet(bool bIgnore)
{
	int iRet = -1;
	if (con) {
		sQuery = "INSERT ";
		if (bIgnore) {
			sQuery += "IGNORE ";
		}
		sQuery += sInsertCols + " " + getSetQuery() + " " + getOnDuplicateKeyUpdate();
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}
	return iRet;
}

int MutableSQLTable::insertAll(const SQLExpressionList & sqleList, bool bReplace, bool bIgnore)
{
	return insertColumns({}, sqleList, bReplace, bIgnore);
}

int MutableSQLTable::insertColumns(const std::vector<int>& vecCols, const SQLExpressionList & sqleList, bool bReplace, bool bIgnore)
{
	int iRet = -1;
	if (!con) {
		return iRet;
	}
	//std::string sInsert = "INSERT INTO " + getTableName() + " ";
	if (vecCols.empty() || vecCols.size() == sqleList.size()) {
		setInsertColumns(vecCols);
		clearInsertValues();
		addInsertValues(sqleList);
		iRet = bReplace ? replaceValues() : insertValues(bIgnore);
	}
	return iRet;
}

void MutableSQLTable::addInsertValues(const SQLExpressionList & sqleList)
{
	if (!sInsertValues.empty()) {
		sInsertValues += ",";
	}
	sInsertValues += "(" + sqleList.getListString() + ")";
}

void MutableSQLTable::clearInsertValues()
{
	sInsertValues = "";
}

void MutableSQLTable::setInsertColumns(const std::vector<int>& vecCols)
{
	if (vecCols.empty()) {
		sInsertCols = "";
	}
	else {
		sInsertCols += "(";
		for (size_t i = 0; i < vecCols.size(); ++i) {
			if (i > 0) {
				sInsertCols += ",";
			}

			sInsertCols += getColumnName(vecCols[i]);
		}
		sInsertCols += ")";
	}
}

int MutableSQLTable::replaceValues()
{
	int iRet = -1;
	if (con) {
		sQuery = "REPLACE ";
		sQuery += "INTO " + getTableName() + " " + sInsertCols + " VALUES " + sInsertValues;
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}
	return iRet;
}

int MutableSQLTable::replaceSelect()
{
	int iRet = -1;
	if (con) {
		sQuery = "REPLACE ";
		sQuery += sInsertCols + " " + getSelectQuery();
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}
	return iRet;
}

int MutableSQLTable::replaceSet()
{
	int iRet = -1;
	if (con) {
		sQuery = "REPLACE ";
		sQuery += sInsertCols + " " + getSetQuery();
		std::shared_ptr<sql::Statement> stmt(con->createStatement());
		iRet = stmt->executeUpdate(sQuery);
	}
	return iRet;
}

void MutableSQLTable::addOnDuplicateKeyUpdate(int iCol, const SQLExpression & sqle)
{
	if (!sInsertUpdate.empty()) {
		sInsertUpdate += ", ";
	}
	sInsertUpdate += getColumnName(iCol) + " = " + sqle.toString();
}

std::string MutableSQLTable::getOnDuplicateKeyUpdate() const
{
	return sInsertUpdate.empty() ? sInsertUpdate : " ON DUPLICATE KEY UPDATE " + sInsertUpdate;
}

void MutableSQLTable::clearSet()
{
	sSet = "";
}



JoinTable::JoinTable(const std::string & sIP, const std::string & sUser, const std::string & sPassword) : SQLTable(sIP, sUser, sPassword)
{
}

JoinTable::JoinTable(std::shared_ptr<sql::Connection> newConn) : SQLTable(newConn)
{
}

JoinTable::JoinTable(const SQLTable & pt) : SQLTable(pt)
{
}

JoinTable::JoinTable(const JoinTable & jt) : SQLTable(jt)
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

void JoinTable::joinTables(JoinType eJoin, const SQLTable & ptLeft, const SQLTable & ptRight, const std::string & sLeftAlias, const std::string & sRightAlias)
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
		std::string sTmp = SQLTable::sanitize(sLeftAlias);
		sFrom += " AS " + sTmp;
		vecTables.push_back(sTmp);
	}
	else {
		vecTables.push_back(ptLeft.getFrom());
	}

	sFrom += getJoin(eJoin) + " " + ptRight.getFrom();
	if (!sRightAlias.empty()) {
		std::string sTmp = SQLTable::sanitize(sRightAlias);
		sFrom += " AS " + sTmp;
		vecTables.push_back(sTmp);
	}
	else {
		vecTables.push_back(ptRight.getFrom());
	}
}

void JoinTable::joinTable(JoinType eJoin, const SQLTable & pt, const std::string & sAlias)
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
		std::string sTmp = SQLTable::sanitize(sAlias);
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

SubQuery::SubQuery(const std::string & sIP, const std::string & sUser, const std::string & sPassword) : SQLTable(sIP, sUser, sPassword)
{
}

SubQuery::SubQuery(std::shared_ptr<sql::Connection> newConn) : SQLTable(newConn)
{
}

SubQuery::SubQuery(const SQLTable & pt) : SQLTable(pt)
{
}

std::string SubQuery::getFrom() const
{
	return sFrom;
}

void SubQuery::setSubQuery(const SQLTable & pt, const std::string sAlias)
{
	sFrom = "(" + pt.getSelectQuery() + ") AS " + SQLTable::sanitize(sAlias);
	if (pt.getSelect() == SQLTable::SELECT_ALL) {
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
	sTable = SQLTable::sanitize(sTable);
	std::vector<std::string> vecCols;
	StringUtils::split(sSelect, ",", vecCols);
	for (size_t i = 0; i < vecCols.size(); ++i) {
		std::string sTmp = vecCols[i];
		if (sTmp.find(" AS ") != std::string::npos) {
			sTmp = sTmp.substr(sTmp.find(" AS ") + 4);

		}

		sTmp = SQLTable::sanitize(sTmp);

		if (!sTable.empty()) {
			sTmp = sTable + "." + sTmp;
		}

		mapCols[i] = sTmp;
	}
}

ColumnsTable::ColumnsTable(const std::string &sIP, const std::string &sUser, const std::string &sPassword) : SQLTable(sIP, sUser, sPassword) {

}
ColumnsTable::ColumnsTable(std::shared_ptr<sql::Connection> newConn) : SQLTable(newConn) {

}