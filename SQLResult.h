/* Copyright (C) 2017 Alexander Downey */
#ifndef _SQLRESULT_H
#define _SQLRESULT_H

#include <string>
#include <pqxx/pqxx>


class SQLResult : public pqxx::result {
    public:
        SQLResult(const pqxx::result &res);
        SQLResult();
        SQLResult(bool bSuccess, const std::string &sErr);

        bool getSuccess() const;
        std::string getErrorMessage() const;

    protected:
        bool bSuccess;
        std::string sErr;
};


#endif
