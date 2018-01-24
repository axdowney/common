/* Copyright (C) 2017 Alexander Downey */
#ifndef _DATABASEOBJECT_H
#define _DATABASEOBJECT_H

#include <string>
#include <memory>
#include <queue>
#include <list>

#include <pqxx/pqxx>

class SQLClause {
    protected:
        std::string sValue;
        std::string sColumn;
};

class SQLQuery;
class SQLResult;
class DatabaseObject {
    public:
        bool connect(const std::string &sdbstring);
        bool connect(const std::string &sdbstring, std::string &sErr);
        bool disconnect();
        bool disconnect(std::string &sErr);
        bool beginWork();
        bool beginWork(std::string &sErr);
        bool endWork(bool bCommit = true);
        bool endWork(bool bCommit, std::string &sErr);
        bool addQuery(std::shared_ptr<SQLQuery> spquery);
        std::list<SQLResult> runQueries();
        std::list<SQLResult> runQueries(std::string &sErr);
        SQLResult runQuery(std::shared_ptr<SQLQuery> spquery);
        SQLResult runQuery(std::shared_ptr<SQLQuery> spquery, std::string &sErr);

        std::shared_ptr<pqxx::connection> getConnection();
    protected:
        std::shared_ptr<pqxx::connection> spconn;
        std::shared_ptr<pqxx::work> spwork;
        std::shared_ptr<pqxx::nontransaction> spnon;
        std::queue<std::shared_ptr<SQLQuery> > queueQueries;
};


template <size_t t, typename v >
class Matrix {
    protected:
        std::list<Matrix<t - 1, v> > listOfMatrix;

};

template <typename v>
class Matrix<0, v> {
    protected:
        std::list< v > listOfMatrix;
};

#define DECLARE_M(a) \


#endif
