/* Copyright (C) 2017 Alexander Downey */
#include "SQLQuery.h"
#include <vector>
#include <string>


std::string SQLQuery::toString() {
    return "";
}

SQLQueryRaw::SQLQueryRaw() : SQLQuery() {
    std::vector< std::vector< std::vector< std::string > > > matrix(3, std::vector< std::vector< std::string > >(4, std::vector< std::string >(5)));
}

SQLQueryRaw::SQLQueryRaw(const std::string &sQuery) : SQLQuery(), sQuery(sQuery) {
}

std::string SQLQueryRaw::toString() {
    return sQuery;
}

void SQLQueryRaw::setQuery(const std::string &sQuery) {
    this->sQuery = sQuery;
}
