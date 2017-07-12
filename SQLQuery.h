/* Copyright (C) 2017 Alexander Downey */
#ifndef _SQLQUERY_H
#define _SQLQUERY_H

#include <string>


class SQLQuery {
    public:
        virtual std::string toString();
};

class SQLQueryRaw : public SQLQuery {
    public:
        SQLQueryRaw();
        SQLQueryRaw(const std::string &sQuery);
        virtual std::string toString();
        void setQuery(const std::string &sQuery);
    protected:
        std::string sQuery;
};

#endif
