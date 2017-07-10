/* Copyright (C) 2017 Alexander Downey */
#ifndef _DATABASEOBJECT_H
#define _DATABASEOBJECT_H

#include <string>
#include <memory>
#include <list>

#include <pqxx/pqxx>

class SQLClause {
    protected:
        std::string sValue;
        std::string sColumn;
};

class SQLQuery;
class DatabaseObject {
    public:
        bool connect(const std::string &sdbstring);
        bool disconnect();
        bool beginWork();
        bool endWork(bool bCommit = true);
        bool addQuery(std::shared_ptr<SQLQuery> spquery);
        size_t runQueries();
        bool runQuery(std::shared_ptr<SQLQuery> spquery);
    protected:
        std::shared_ptr<pqxx::connection> spconn;
        std::shared_ptr<pqxx::work> spwork;
        std::shared_ptr<pqxx::nontransaction> spnon;
        std::list<std::shared_ptr<SQLQuery> > listQueries;
};

#endif
