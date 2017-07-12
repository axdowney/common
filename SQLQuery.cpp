/* Copyright (C) 2017 Alexander Downey */
#include "SQLQuery.h"


std::string SQLQuery::toString() {
    return "";
}

SQLQueryRaw::SQLQueryRaw() : SQLQuery() {
}

SQLQueryRaw::SQLQueryRaw(const std::string &sQuery) : SQLQuery(), sQuery(sQuery) {
}

std::string SQLQueryRaw::toString() {
    return sQuery;
}

void SQLQueryRaw::setQuery(const std::string &sQuery) {
    this->sQuery = sQuery;
}
