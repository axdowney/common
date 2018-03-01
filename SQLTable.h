#pragma once
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
%javamethodmodifiers SQLTable::getColumnName(int iCol) const "
/**
* Gets the name of the sql column.  Class dependent.
* @param iCol 0 indexed column number.  Subclasses should have enums for their columns.
* @return the name of the sql column.
*/
public";
#endif

class JoinTable;
class SQLTable {
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

	enum Operation {
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

	SQLTable();
	SQLTable(const std::string &sIP, const std::string &sUser, const std::string &sPassword);
	SQLTable(std::shared_ptr<sql::Connection> newConn);
	SQLTable(const SQLTable &pt);
	SQLTable(const JoinTable &jt);
	bool connect(const std::string &sIP, const std::string &sUser, const std::string &sPassword);
	bool setConnection(std::shared_ptr<sql::Connection> newConn);
	std::shared_ptr<sql::Connection> getConnection();
#ifdef SWIG
	%javamethodmodifiers SQLTable::getTableName() const "
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
	%javamethodmodifiers escapeString const "
		/**
		* escapes quotation marks to prevent sql injections
		* @return sql safe string
		*/
		public";
#endif
		std::string escapeString(const std::string &sEsc) const;
#ifdef SWIG
	%javamethodmodifiers escapeString const "
		/**
		* escapes quotation marks to prevent sql injections
		* @return sql safe string
		*/
		public";
#endif
		static std::string escapeStringStatic(const std::string &sEsc);
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
		bool Union(const SQLTable &table, bool bALL = false, bool bChain = true, bool bClear = false);
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

class MutableSQLTable : public SQLTable {
public:
	MutableSQLTable();
	MutableSQLTable(const std::string &sIP, const std::string &sUser, const std::string &sPassword);
	MutableSQLTable(std::shared_ptr<sql::Connection> newConn);
	MutableSQLTable(const SQLTable &pt);

#ifdef SWIG
	%javamethodmodifiers "
		/**
		* @return
		*/
		public";
#endif
	void addSet(int iCol, const SQLExpression &sqle);

#ifdef SWIG
	%javamethodmodifiers clearSet() "
		/**
		* clears the set clause in an update statement
		*/
		public";
#endif
	void clearSet();
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
		* Run an update command based on set and where clauses.
		* WARNING!  If where clause is not set all entries will be updated.
		* @return the number of affected rows
		*/
		public";
#endif
		std::string getSetQuery();
public:
#ifdef SWIG
	%javamethodmodifiers "
		/**
		* Run an update command based on set and where clauses.
		* WARNING!  If where clause is not set all entries will be updated.
		* @return the number of affected rows
		*/
		public";
#endif
	int insertValues(bool bIgnore);
	int insertSelect(bool bIgnore);
	int insertSet(bool bIgnore);
	
	int insertAll(const SQLExpressionList &sqleList, bool bReplace, bool bIgnore);
	int insertColumns(const std::vector<int> &vecCols,  const SQLExpressionList &sqleList, bool bReplace, bool bIgnore);
	void addInsertValues(const SQLExpressionList &sqleList);
	void clearInsertValues();
	void setInsertColumns(const std::vector<int> &vecCols);
	/* MySQL extensions */
	int replaceValues();
	int replaceSelect();
	int replaceSet();
	void addOnDuplicateKeyUpdate(int iCol, const SQLExpression &sqle);
	std::string getOnDuplicateKeyUpdate() const;
protected:	
	std::string sSet;
	std::string sInsertCols;
	std::string sInsertValues;
	std::string sInsertUpdate;
};

class JoinTable : public SQLTable {
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
	JoinTable(const SQLTable &pt);
	JoinTable(const JoinTable &jt);

	virtual std::string getFrom() const;
	std::string getJoin(JoinType eJoin) const;
	void joinTables(JoinType eJoin, const SQLTable &ptLeft, const SQLTable &ptRight, const std::string &sLeftAlias = "", const std::string &sRightAlias = "");
	void joinTable(JoinType eJoin, const SQLTable &pt, const std::string &sAlias = "");
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

class SubQuery : public SQLTable {
public:
	SubQuery(const std::string &sIP, const std::string &sUser, const std::string &sPassword);
	SubQuery(std::shared_ptr<sql::Connection> newConn);
	SubQuery(const SQLTable &pt);
	virtual std::string getFrom() const;
	void setSubQuery(const SQLTable &pt, const std::string sAlias);
	void clearSubQuery();
	void setColumnsFromSelect(std::string sSelect, std::string sTable);

protected:
	std::string sFrom;
};

class ColumnsTable : public SQLTable {
public:
	enum {
		TABLE_CATALOG = 1,
		TABLE_SCHEMA,
		TABLE_NAME,
		COLUMN_NAME,
		ORDINAL_POSITION,
		COLUMN_DEFAULT,
		IS_NULLABLE,
		DATA_TYPE,
		CHARACTER_MAXIMUM_LENGTH,
		CHARACTER_OCTET_LENGTH,
		NUMERIC_PRECISION,
		NUMERIC_SCALE,
		DATETIME_PRECISION,
		CHARACTER_SET_NAME,
		COLLATION_NAME,
		COLUMN_TYPE,
		COLUMN_KEY,
		EXTRA,
		PRIVILEGES,
		COLUMN_COMMENT,
		GENERATION_EXPRESSION
	};
	ColumnsTable(const std::string &sIP, const std::string &sUser, const std::string &sPassword);
	ColumnsTable(std::shared_ptr<sql::Connection> newConn);

};