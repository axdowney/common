/* Copyright (C) 2017 Alexander Downey */
#include "DatabaseObject.h"
#include "SQLQuery.h"
#include "SQLResult.h"


bool DatabaseObject::connect(const std::string &sdbstring) {
    std::string sErr;
    return connect(sdbstring, sErr);
}

bool DatabaseObject::connect(const std::string &sdbstring, std::string &sErr) {
    bool bOK = true;
    try {
        spwork.reset();
        spnon.reset();
        spconn.reset(new pqxx::connection(sdbstring));
        spnon.reset(new pqxx::nontransaction(*spconn));
    } catch(const std::exception &e) {
        bOK = false;
        sErr = e.what();
        spwork.reset();
        spnon.reset();
        spconn.reset();
    }

    return bOK;
}

bool DatabaseObject::disconnect() {
    std::string sErr;
    return disconnect(sErr);
}

bool DatabaseObject::disconnect(std::string &sErr) {
    bool bOK = static_cast<bool>(spconn);
    if (bOK) {
        try {
            spwork.reset();
            spnon.reset();
            spconn->disconnect();
            spconn.reset();
        } catch(const std::exception &e) {
            bOK = false;
            sErr = e.what();
            spwork.reset();
            spnon.reset();
            spconn.reset();
        }
    }

    return bOK;
}

bool DatabaseObject::beginWork() {
    std::string sErr;
    return beginWork(sErr);
}

bool DatabaseObject::beginWork(std::string &sErr) {
    bool bOK = true;
    try {
        spwork.reset();
        spwork.reset(new pqxx::work(*spconn));
    } catch(const std::exception &e) {
        bOK = false;
        sErr = e.what();
        spwork.reset();
    }

    return bOK;
}

bool DatabaseObject::endWork(bool bCommit) {
    std::string sErr;
    return endWork(bCommit, sErr);
}

bool DatabaseObject::endWork(bool bCommit, std::string &sErr) {
    bool bOK = static_cast<bool>(spwork);
    if (bOK) {
        try {
            if (bCommit) {
                spwork->commit();
            } else {
                spwork->abort();
            }

            spwork.reset();
        } catch(const std::exception &e) {
            bOK = false;
            sErr = e.what();
            spwork.reset();
        }
    }

    return bOK;
}

bool DatabaseObject::addQuery(std::shared_ptr<SQLQuery> spquery) {
    queueQueries.push(spquery);
    return true;
}

std::list<SQLResult> DatabaseObject::runQueries() {
    std::string sErr;
    return runQueries(sErr);
}

std::list<SQLResult> DatabaseObject::runQueries(std::string &sErr) {
    std::list<SQLResult> listRet;
    while(!queueQueries.empty()) {
        auto spquery = queueQueries.front();
        SQLResult sqlr = runQuery(spquery, sErr);
        listRet.push_back(sqlr);
        if (sqlr.getSuccess()) {
            queueQueries.pop();
        } else {
            break;
        }
    }

    return listRet;
}

SQLResult DatabaseObject::runQuery(std::shared_ptr<SQLQuery> spquery) {
    std::string sErr;
    return runQuery(spquery, sErr);
}

SQLResult DatabaseObject::runQuery(std::shared_ptr<SQLQuery> spquery, std::string &sErr) {
    SQLResult sqlr;
    try {
        if (spwork) {
            sqlr = SQLResult(spwork->exec(spquery->toString()));
        } else if (spnon) {
            sqlr = SQLResult(spnon->exec(spquery->toString()));
        } else {
            sqlr = SQLResult(false, "Disconnected");
        }
    } catch(const std::exception &e) {
        sErr = e.what();
        spwork.reset();
        spnon.reset();
        spconn.reset();
        queueQueries = std::queue<std::shared_ptr<SQLQuery> >();
        sqlr = SQLResult(false, sErr);
    }

    return sqlr;
}

std::shared_ptr<pqxx::connection> DatabaseObject::getConnection() {
    return spconn;
}
