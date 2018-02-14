#pragma once
#ifndef _PIRETABLES_H
#define _PIRETABLES_H

#include <memory>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <list>
#include <initializer_list>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "SQLExpression.h"

#ifdef SWIG
%javamethodmodifiers PireTable::getColumnName(int iCol) const "
/**
 * Gets the name of the sql column.  Class dependent.
 * @param iCol 0 indexed column number.  Subclasses should have enums for their columns.
 * @return the name of the sql column.
 */
	public";
#endif

class JoinTable;
class PireTable {
public:
	enum MatchType {
		Equal,
		NotEqual,
		Like,
		LessThan,
		GreaterThan,
		LessThanEq,
		GreaterThanEq
	};

	enum Operation{
		AND,
		OR,
		XOR,
		NOT,
	};

	enum Aggregate {
		COUNT,
		MIN,
		AVG,
		MAX,
		SUM,
	};

	PireTable();
	PireTable(const std::string &sIP, const std::string &sUser, const std::string &sPassword);
	PireTable(std::shared_ptr<sql::Connection> newConn);
	PireTable(const PireTable &pt);
	PireTable(const JoinTable &jt);
	bool connect(const std::string &sIP, const std::string &sUser, const std::string &sPassword);
	bool setConnection(std::shared_ptr<sql::Connection> newConn);
	std::shared_ptr<sql::Connection> getConnection();
#ifdef SWIG
%javamethodmodifiers PireTable::getTableName() const "
/**
* Gets the name of the sql table.  Class dependent.
* @return the name of the sql table.
*/
	public";
#endif
	virtual std::string getTableName() const { return ""; }

	virtual std::string getColumnName(int iCol) const;
#ifdef SWIG
	%javamethodmodifiers generateTable() "
		/**
		* Generates the table in the database.
		* If the database already exists, then it throws an exception.
		* If the connection is invalid, then it returns a negative.
		* Class dependent.
		* @return the number of rows updated.
		*/
		public";
#endif
/**
* Generates the table in the database.
* If the database already exists, then it throws an exception.
* If the connection is invalid, then it returns a negative.
* Class dependent.
* @return the number of rows updated.
*/
	int generateTable();
#ifdef SWIG
	%javamethodmodifiers getTableSQL() const "
		/**
		* Returns the sql code for the table.
		* Class dependent.
		* @return the sql code for the table.
		*/
		public";
#endif
	virtual std::string getTableSQL() const;
#ifdef SWIG
	%javamethodmodifiers getQuery() const "
		/**
		* @return the last executed query
		*/
		public";
#endif
	std::string getQuery() const;
#ifdef SWIG
	%javamethodmodifiers clearQuery() "
		/**
		* clears the last executed query
		*/
		public";
#endif
	void clearQuery();
#ifdef SWIG
	%javamethodmodifiers clearWhere() "
		/**
		* clears the where clause
		*/
		public";
#endif
	void clearWhere();
#ifdef SWIG
	%javamethodmodifiers clearSet() "
		/**
		* clears the set clause in an update statement
		*/
		public";
#endif
	void clearSet();
#ifdef SWIG
	%javamethodmodifiers escapeString const "
		/**
		* escapes quotation marks to prevent sql injections
		* @return sql safe string
		*/
		public";
#endif
	std::string escapeString(const std::string &sEsc) const;
#ifdef SWIG
	%javamethodmodifiers quote const "
		/**
		* First escapes the string and then surrounds it with single quotes
		* @return sql safe sql string
		*/
		public";
#endif
	std::string quote(const std::string &sQuote) const;
#ifdef SWIG
	%javamethodmodifiers sanitize(const std::string &sInput) "
		/**
		* Removes illegal characters for sql names
		* @return sql safe name or empty string
		*/
		public";
#endif
	static std::string sanitize(const std::string &sInput);
#ifdef SWIG
	%javamethodmodifiers deleteRows() "
		/**
		* Deletes rows from table according to where clause.
		* WARNING!  If where clause not set it will remove all entries.
		* @return number of rows deleted
		*/
		public";
#endif
	int deleteRows();
#ifdef SWIG
	%javamethodmodifiers getCompare(MatchType e) "
		/**
		* Gets the string version of the MatchType.
		* @param e MatchType enum represents comparison operators such as = < LIKE.
		* @return the string version of the MatchType enum
		*/
		public";
#endif
	static std::string getCompare(MatchType e);
#ifdef SWIG
	%javamethodmodifiers getOperation(Operation e) "
		/**
		* Gets the string version of the Operation.
		* @param e Operation enum represents boolean operators such as AND OR XOR.
		* @return the string version of the Operation enum
		*/
		public";
#endif
	static std::string getOperation(Operation e);
#ifdef SWIG
	%javamethodmodifiers getAggregate(Aggregate e) "
		/**
		* Gets the string version of the Aggregate.
		* @param e Aggregate enum represents Aggregation function such as COUNT, MAX, SUM.
		* @return the string version of the Aggregate enum
		*/
		public";
#endif
	static std::string getAggregate(Aggregate e);
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* Add a column to the selection clause.
		* @param iCol the index of the column to add to select
		*/
		public";
#endif
	void addSelect(int iCol);
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* Add an aggregation of a column to the selection clause.
		* @param e the aggregation function
		* @param iCol the column index
		* @param bAll if true aggregate all entries, if false aggregate distinct entries
		*/
		public";
#endif
	void addAggregateSelect(Aggregate e, int iCol, bool bAll = true);
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* Add an expression to the selection clause.
		* @param sqle expression to select
		*/
		public";
#endif
	void addSelect(const SQLExpression &sqle);
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* clears the select clause
		*/
		public";
#endif
	void clearSelect();
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* Gets the select clause for a slect query.
		* If no selection is set, it returns the select all string.
		* @return the select clause
		*/
		public";
#endif
	std::string getSelect() const;
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* Gets the from clause.  For most tables this is the same
		* as getTableName, but some tables use subqueries.
		* @return the from clause
		*/
		public";
#endif
	virtual std::string getFrom() const;
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* Gets the where clause.
		* @return the where clause
		*/
		public";
#endif
		virtual std::string getWhere() const;
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* Gets the results of a select query.
		* This is mostly a helper function since sql::ResultSet is not wrapped.
		* This result set has more functionality in c++, but selectRowStrings is
		* a portable version of this function.
		* @param bDistinct if true remove duplicate rows from result set, default false
		* @return a sql::ResultSet of result set values
		*/
		public";
#endif
	std::shared_ptr<sql::ResultSet> selectRows(bool bDistinct = false);
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* Gets the results of a select query.
		* This is the prefered method for language wrappers.
		* @param bDistinct if true remove duplicate rows from result set, default false
		* @return a 2D string vector of result set values
		*/
		public";
#endif
	std::vector< std::vector<std::string> > selectRowStrings(bool bDistinct = false);
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* Run an update command based on set and where clauses.
		* WARNING!  If where clause is not set all entries will be updated.  
		* @return the number of affected rows
		*/
		public";
#endif
	int updateRows();
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* Gets the complete select query as a string.
		* Mostly used for debugging or as a helper function.
		* @return the current select query
		*/
		public";
#endif
	virtual std::string getSelectQuery(bool bDistinct = false) const;
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* Unions another table with the current select query.
		* This table's selection and where clauses are used in both the
		* union subquery and the whole query.
		* The clear boolean makes most sense when bChain is false.
		* @param table the table to union
		* @param bALL if true include duplicate entries found in both selects, default false
		* @param bChain if true add this union to the chain, else union current select, default true
		* @param bClear clear select and where clauses after including them in the union, default false
		* @return true if union is successfull
		*/
		public";
#endif
	bool Union(const PireTable &table, bool bALL = false, bool bChain = true, bool bClear = false);
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* Gets the current union chain.
		* @return the union chain as a string
		*/
		public";
#endif
	std::string getUnion() const;
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* A helper function which gets the clauses which follow the where clause.
		* @return the GROUP BY, HAVING, ORDER BY, LIMIT and OFFSET clauses as a string
		*/
		public";
#endif
	std::string getEndingClause() const;
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* Adds a condition to the where clause.
		* The operation parameter is ignored if this is the first condition.
		* @param eOP the operation used to connect to the previous condition
		* @param iCol the column index
		* @param iMatchType the operator used to compair with the value
		* @param val the value to compare with the column entry
		*/
		public";
#endif
	template<typename T>
	void addWhere(Operation eOP, int iCol, MatchType iMatchType, T val, bool bNot = false) {
		std::string sTmp = getColumnName(iCol) + getCompare(iMatchType);
		std::string sVal;
		std::stringstream ss;
		ss << val;
		sVal = quote(ss.str());
		if (sWhere.empty()) {
			sWhere += " WHERE ";
		}
		else {
			sWhere += getOperation(eOP);
		}
		sTmp += sVal;
		if (bNot) {
			sTmp = " NOT (" + sTmp + ")";
		}

		sWhere += sTmp;
	}
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* Adds a condition to the where clause.
		* The operation parameter is ignored if this is the first condition.
		* @param eOP the operation used to connect to the previous condition
		* @param sqle the expression to add to the where clause
		*/
		public";
#endif
	void addWhere(Operation eOP, const SQLExpression &sqle) {
		if (sWhere.empty()) {
			sWhere += " WHERE ";
		}
		else {
			sWhere += getOperation(eOP);
		}
		
		sWhere += sqle.toString();
	}
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* Adds a condition to the where clause.
		* The operation parameter is ignored if this is the first condition.
		* @param eOP the operation used to connect to the previous condition
		* @param iCol the column index
		* @param iMatchType the operator used to compair with the value
		* @param iMatchingCol the column to compare with the column entry
		* @param bNot if true inver the comparison, defualt false
		*/
		public";
#endif
	void addWhereCol(Operation eOP, int iCol, MatchType iMatchType, int iMatchingCol, bool bNot = false) {
		if (sWhere.empty()) {
			sWhere += " WHERE ";
		}
		else {
			sWhere += getOperation(eOP);
		}

		std::string sTmp = getColumnName(iCol) + getCompare(iMatchType) + getColumnName(iMatchingCol);
		if (bNot) {
			sTmp = " NOT (" + sTmp + ")";
		}

		sWhere += sTmp;
	}
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* @return
		*/
		public";
#endif
	template<typename T>
	void addWhereIn(Operation eOP, int iCol, const std::vector<T> &vecVals, std::vector<int> vecCols, bool bNot = false) {
		std::string sTmp;
		std::string sVal;
		for (int i = 0; i < vecVals.size(); ++i) {
			std::stringstream ss;
			ss << vecVals[i];
			sVal = quote(ss.str());
			if (!sTmp.empty()) {
				sTmp += ",";
			}
			sTmp += sVal;
		}

		for (int i = 0; i < vecCols.size(); ++i) {
			if (!sTmp.empty()) {
				sTmp += ",";
			}
			sTmp += getColumnName(vecCols[i]);
		}

		sTmp = getColumnName(iCol);
		if (bNot) {
			sTmp += " NOT";
		}

		sTmp += " IN (" + sTmp + ") ";
		if (sWhere.empty()) {
			sWhere += " WHERE ";
		}
		else {
			sWhere += getOperation(eOP);
		}

		sWhere += sTmp;
	}
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* @return
		*/
		public";
#endif
	template<typename T>
	void addSet(int iCol, T val) {
		std::string sVal;
		std::stringstream ss;
		ss << val;
		sVal = quote(ss.str());
		if (!sSet.empty()) {
			sSet += ", ";
		}
		sSet += getColumnName(iCol) + " = " + sVal;
	}
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* @return
		*/
		public";
#endif
	void addOrderBy(int iCol, bool bAsc = true);
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* @return
		*/
		public";
#endif
	void addGroupBy(int iCol);
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* @return
		*/
		public";
#endif
	void clearOrderBy();
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* @return
		*/
		public";
#endif
	void clearGroupBy();
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* @return
		*/
		public";
#endif
	void setLimit(int i);
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* @return
		*/
		public";
#endif
	void setOffset(int i);
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* @return
		*/
		public";
#endif
	void addHaving(Operation eOp, Aggregate eAgg, int iCol, bool bAll, MatchType eCom, double dVal);
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* @return
		*/
		public";
#endif
	std::map<int, std::string> getColumnMap() const;
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* @return
		*/
		public";
#endif
	virtual size_t getColumnCount() const;

	virtual bool setAlias(const std::string &sA);
	void clearAlias();

	static std::string SELECT_ALL;

protected:
	std::shared_ptr<sql::Connection> con;
	std::string sQuery;
	std::string sWhere;
	std::string sSelect;
	std::string sSet;
	std::string sOrderBy;
	std::string sGroupBy;
	std::string sHaving;
	std::string sUnion;
	std::string sAlias;
	std::map<int, std::string> mapCols;
	int iLimit = -1;
	int iOffset = -1;
	friend class JoinTable;
};
#define ValNamePair(a) \
	{a, #a}



class JoinTable : public PireTable {
public:
	enum JoinType {
		INNER,
		LEFT,
		RIGHT,
		FULL, // Not supported in MySQL
		CROSS, // Same as INNER in MySQL
	};

	JoinTable(const std::string &sIP, const std::string &sUser, const std::string &sPassword);
	JoinTable(std::shared_ptr<sql::Connection> newConn);
	JoinTable(const PireTable &pt);
	JoinTable(const JoinTable &jt);

	virtual std::string getFrom() const;
	std::string getJoin(JoinType eJoin) const;
	void joinTables(JoinType eJoin, const PireTable &ptLeft, const PireTable &ptRight, const std::string &sLeftAlias = "", const std::string &sRightAlias = "");
	void joinTable(JoinType eJoin, const PireTable &pt, const std::string &sAlias = "");
	bool addOn(Operation eOp, int iTableLeft, int iColumnLeft, MatchType eMatch, int iTableRight, int iColumnRight);
	std::string getTableColumn(int iTable, int iColumn);
	void clearJoin();
	virtual std::string getColumnName(int iCol) const;
	virtual int getColumnIndex(int iTable, int iCol);
	virtual size_t getColumnCount() const;
	void beginTransaction();
	bool endTransaction(bool bCommit);

protected:
	std::string sFrom;
	std::string sOn;
	std::vector<std::string> vecTables;
	std::vector<std::map<int, std::string> > vecMapCols;
};

class SubQuery : public PireTable {
public:
	SubQuery(const std::string &sIP, const std::string &sUser, const std::string &sPassword);
	SubQuery(std::shared_ptr<sql::Connection> newConn);
	SubQuery(const PireTable &pt);
	virtual std::string getFrom() const;
	void setSubQuery(const PireTable &pt, const std::string sAlias);
	void clearSubQuery();
	void setColumnsFromSelect(std::string sSelect, std::string sTable);

protected:
	std::string sFrom;
};

class ModelTable : public PireTable {
public:
	enum {
		model,
		height,
		width,
		depth,
		mass,
		model_type,
		description,
	};
	
	ModelTable(const std::string &sIP, const std::string &sUser, const std::string &sPassword);
	ModelTable(std::shared_ptr<sql::Connection> newConn);
	virtual std::string getTableName() const { return "model_table"; }
	virtual std::string getTableSQL() const { return "CREATE TABLE MODEL_TABLE (\n"
		"model varchar(50) NOT NULL DEFAULT \"\",\n"
		"height DOUBLE NOT NULL,\n"
		"width DOUBLE NOT NULL,\n"
		"depth DOUBLE NOT NULL,\n"
		"mass DOUBLE NOT NULL,\n"
		"model_type ENUM('human', 'rat'),\n"
		"description VARCHAR(256),\n"
		"CONSTRAINT PK_MODEL_TABLE PRIMARY KEY(model)\n"
		"); "; };
	std::map<int, std::string> initColumnMap() const;
	int insertRow(std::string sModel, double dH, double dW, double dD, double dM, std::string sType, const std::string &sDescription = "");
private:
};

class ModelResolutionTable : public PireTable {
public:
	enum {
		model,
		model_res,
		nx,
		ny,
		nz,
		dx,
		dy,
		dz,
	};
	ModelResolutionTable(const std::string &sIP, const std::string &sUser, const std::string &sPassword);
	ModelResolutionTable(std::shared_ptr<sql::Connection> newConn);
	virtual std::string getTableName() const { return "model_resolution_table"; }
	virtual std::string getTableSQL() const { return "CREATE TABLE MODEL_RESOLUTION_TABLE (\n"
		"model varchar(50) NOT NULL DEFAULT \"\"\n",
		"model_res varchar(50) NOT NULL DEFAULT \"\"\n",
		"nx INT NOT NULL,\n"
		"ny INT NOT NULL,\n"
		"nz INT NOT NULL,\n"
		"dx DOUBLE NOT NULL,\n"
		"dy DOUBLE NOT NULL,\n"
		"dz DOUBLE NOT NULL,\n"
		"CONSTRAINT PK_MODEL_RESOLUTION_TABLE PRIMARY KEY(model, model_res),\n"
		"FOREIGN KEY(model) REFERENCES MODEL_TABLE(model) \n"
		")"; }
	std::map<int, std::string> initColumnMap() const;
	int insertRow(std::string sModel, std::string sModelRes, double dNX, double dNY, double dNZ, double dDX, double dDY, double dDZ);
};

class SimInputTable : public PireTable {
public:
	enum {
		model /*varchar(50) default ""*/,
		model_res /*varchar(50) NOT NULL DEFAULT ""*/,
		frequency  /*float(30, 10) default 0.0*/,
		power_density /*float(30, 6) default 0.0*/,
		power_limit /*float(30, 6) default 0.0*/,
		theta /*int(3) default 0*/,
		phi /*int(3) default 0*/,
		polarization /*enum('horizontal', 'vertical')*/,
		duration  /*float(30, 10) default 4.0*/,
		material /*varchar(50) default 0.0*/,
		sim_id
	};
	SimInputTable(const std::string &sIP, const std::string &sUser, const std::string &sPassword);
	SimInputTable(std::shared_ptr<sql::Connection> newConn);
	virtual std::string getTableName() const { return "sim_input_table"; }
	virtual std::string getTableSQL() const { return "CREATE TABLE SIM_INPUT_TABLE (\n"
		"model varchar(50) default \"\",\n"
		"model_res varchar(50) NOT NULL DEFAULT "",\n"
		"frequency  float(30, 10) default 0.0,\n"
		"power_density float(30, 6) default 0.0,\n"
		"power_limit float(30, 6) default 0.0,\n"
		"theta int(3) default 0,\n"
		"phi int(3) default 0,\n"
		"polarization enum('horizontal', 'vertical'),\n"
		"duration  float(30, 10) default 4.0,\n"
		"material varchar(50) default 0.0,\n"
		"sim_id int NOT NULL AUTO_INCREMENT,\n"
		"insertion_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\n"
		"CONSTRAINT UNIQUE(model, frequency, power_density, theta, phi, polarization, duration, material),\n"
		"CONSTRAINT PK_SAR_TEST_TABLE PRIMARY KEY(sim_id),\n"
		"FOREIGN KEY(model) REFERENCES MODEL_TABLE(model),\n"
		"FOREIGN KEY(model, model_res) REFERENCES MODEL_RESOLUTION_TABLE(model, model_res)\n"
		")"; }
	std::map<int, std::string> initColumnMap() const;
	int insertRow(std::string sModel, std::string sModelRes, double dFreq, double dPowerDensity, double dPowerLimit,
		double dTheta, double dPhi, double dPolarization, double dDuration, std::string sMaterial, double dID);
};

class SimOutputTable : public PireTable {
public:
	enum {
		output_id /*INT NOT NULL*/,
		output_tissue /*varchar(50) NOT NULL*/,
		output_name /*varchar(50) NOT NULL*/,
		output_value /*varchar(256) NOT NULL*/,
	};
	SimOutputTable(const std::string &sIP, const std::string &sUser, const std::string &sPassword);
	SimOutputTable(std::shared_ptr<sql::Connection> newConn);
	virtual std::string getTableName() const { return "sim_output_table"; }
	virtual std::string getTableSQL() const { return "CREATE TABLE SIM_OUTPUT_TABLE (\n"
		"output_id INT NOT NULL,\n"
		"output_tissue varchar(50) NOT NULL,\n"
		"output_name varchar(50) NOT NULL,\n"
		"output_value varchar(256) NOT NULL,\n"
		"CONSTRAINT PK_SAR_TEST_TABLE PRIMARY KEY(output_id, output_name),\n"
		"FOREIGN KEY(output_id) REFERENCES SIM_INPUT_TABLE(sim_id)\n"
		")"; }
	std::map<int, std::string> initColumnMap() const;
	int insertRow(double dID, const std::string &sTissue, const std::string &sName, double dValue);

};

class ThermalTissueTable : public PireTable {
public:
	enum {
		model /*varchar(50) NOT NULL DEFAULT ""*/,
		Tissue_label /*varchar(50) NOT NULL DEFAULT ""*/,
		tissue_ID /*INT NOT NULL*/,
		Density /*DOUBLE NOT NULL, #(kg / m ^ 2)*/,
		HeatCapacity /*DOUBLE NOT NULL, #(J / kg - K)*/,
		Conductivity /*DOUBLE NOT NULL, #(W / m - K)*/,
		PerfusionRate /*DOUBLE NOT NULL, #(mL / min / 100g)*/,
		MetabolicRate /*DOUBLE NOT NULL, #(W / kg)*/
	};
	ThermalTissueTable(const std::string &sIP, const std::string &sUser, const std::string &sPassword);
	ThermalTissueTable(std::shared_ptr<sql::Connection> newConn);
	virtual std::string getTableName() const { return "thermal_tissue_table"; }
	virtual std::string getTableSQL() const { return "CREATE TABLE THERMAL_TISSUE_TABLE (\n"
		"model varchar(50) NOT NULL DEFAULT \"\",\n"
		"Tissue_label varchar(50) NOT NULL DEFAULT \"\",\n"
		"tissue_ID INT NOT NULL,\n"
		"Density DOUBLE NOT NULL, #(kg / m ^ 2)\n"
		"HeatCapacity DOUBLE NOT NULL, #(J / kg - K)\n"
		"Conductivity DOUBLE NOT NULL, #(W / m - K)\n"
		"PerfusionRate DOUBLE NOT NULL, #(mL / min / 100g)\n"
		"MetabolicRate DOUBLE NOT NULL, #(W / kg)\n"
		"CONSTRAINT PK_THERMAL_TISSUE_TABLE PRIMARY KEY(model, tissue_label),\n"
		"CONSTRAINT UNIQUE(model, tissue_id),\n"
		"FOREIGN KEY(model) REFERENCES MODEL_TABLE(model)\n"
		")"; }
	std::map<int, std::string> initColumnMap() const;
	int insertRow(const std::string &sModel, const std::string &sLable, double dID, double dDensity,
		double dHeatCapacity, double dConductivity, double dPerfusionRate, double dMetabolicRate);
};

class ITISTissueTable : public PireTable {
public:
	enum {
		tissue_name /*varchar(50)*/,
		itis_version /*varchar(50)*/,
		Density_avg /*DOUBLE, #(kg / m ^ 2)*/,
		Density_min /*DOUBLE, #(kg / m ^ 2)*/,
		Density_max /*DOUBLE, #(kg / m ^ 2)*/,
		HeatCapacity_avg /*DOUBLE, #(J / kg - K)*/,
		HeatCapacity_min /*DOUBLE, #(J / kg - K)*/,
		HeatCapacity_max /*DOUBLE, #(J / kg - K)*/,
		Conductivity_avg /*DOUBLE, #(W / m - K)*/,
		Conductivity_min /*DOUBLE, #(W / m - K)*/,
		Conductivity_max /*DOUBLE, #(W / m - K)*/,
		HeatTransferRate_avg /*DOUBLE, #(mL / min / kg)*/,
		HeatTransferRate_min /*DOUBLE, #(mL / min / kg)*/,
		HeatTransferRate_max /*DOUBLE, #(mL / min / kg)*/,
		HeatGenerationRate_avg /*DOUBLE, #(W / kg)*/,
		HeatGenerationRate_min /*DOUBLE, #(W / kg)*/,
		HeatGenerationRate_max /*DOUBLE, #(W / kg)*/,
		ef /*DOUBLE*/,
		del1 /*DOUBLE*/,
		tau1 /*DOUBLE, # (ps)*/,
		alf1 /*DOUBLE*/,
		del2 /*DOUBLE*/,
		tau2 /*DOUBLE, # (ns)*/,
		alf2 /*DOUBLE*/,
		sig /*DOUBLE*/,
		del3 /*DOUBLE*/,
		tau3 /*DOUBLE, # (µs)*/,
		alf3 /*DOUBLE*/,
		del4 /*DOUBLE*/,
		tau4 /*DOUBLE, # (ms)*/,
		alf4 /*DOUBLE*/,
	};

	ITISTissueTable(const std::string &sIP, const std::string &sUser, const std::string &sPassword);
	ITISTissueTable(std::shared_ptr<sql::Connection> newConn);
	virtual std::string getTableName() const { return "itis_tissue_table"; }
	virtual std::string getTableSQL() const { return "CREATE TABLE ITIS_TISSUE_TABLE (\n"
		"tissue_name varchar(50),\n"
		"itis_version varchar(50),\n"
		"Density_avg DOUBLE, #(kg / m ^ 2)\n"
		"Density_min DOUBLE, #(kg / m ^ 2)\n"
		"Density_max DOUBLE, #(kg / m ^ 2)\n"
		"HeatCapacity_avg DOUBLE, #(J / kg - K)\n"
		"HeatCapacity_min DOUBLE, #(J / kg - K)\n"
		"HeatCapacity_max DOUBLE, #(J / kg - K)\n"
		"Conductivity_avg DOUBLE, #(W / m - K)\n"
		"Conductivity_min DOUBLE, #(W / m - K)\n"
		"Conductivity_max DOUBLE, #(W / m - K)\n"
		"HeatTransferRate_avg DOUBLE, #(mL / min / kg)\n"
		"HeatTransferRate_min DOUBLE, #(mL / min / kg)\n"
		"HeatTransferRate_max DOUBLE, #(mL / min / kg)\n"
		"HeatGenerationRate_avg DOUBLE, #(W / kg)\n"
		"HeatGenerationRate_min DOUBLE, #(W / kg)\n"
		"HeatGenerationRate_max DOUBLE, #(W / kg)\n"
		"ef DOUBLE,\n"
		"del1 DOUBLE,\n"
		"tau1 DOUBLE, # (ps)\n"
		"alf1 DOUBLE,\n"
		"del2 DOUBLE,\n"
		"tau2 DOUBLE, # (ns)\n"
		"alf2 DOUBLE,\n"
		"sig DOUBLE,\n"
		"del3 DOUBLE,\n"
		"tau3 DOUBLE, # (µs)\n"
		"alf3 DOUBLE,\n"
		"del4 DOUBLE,\n"
		"tau4 DOUBLE, # (ms)\n"
		"alf4 DOUBLE,\n"
		"CONSTRAINT PK_ITIS_TISSUE_TABLE PRIMARY KEY(tissue_name, itis_version)\n"
		")"; }
	std::map<int, std::string> initColumnMap() const;
	int insertRow(const std::string &sName, const std::string &sVersion,
		double dDenAvg, double dDenMin, double dDenMax,
		double dHCAvg, double dHCMin, double dHCMax,
		double dCondAvg, double dCondMin, double dCondMax,
		double dHTAvg, double dHTMin, double dHTMax,
		double dHGAvg, double dHGMin, double dHGMax,
		double def,  double ddel1, double dtau1, double dalf1,
		             double ddel2, double dtau2, double dalf2,
	    double dsig, double ddel3, double dtau3, double dalf3,
		             double ddel4, double dtau4, double dalf4);
};
#endif