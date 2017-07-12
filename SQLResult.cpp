/* Copyright (C) 2017 Alexander Downey */
#include "SQLResult.h"


SQLResult::SQLResult(const pqxx::result &res) : pqxx::result(res), bSuccess(true) {}
SQLResult::SQLResult() : pqxx::result(), bSuccess(true) {}
SQLResult::SQLResult(bool bSuccess, const std::string &sErr) : pqxx::result(), bSuccess(bSuccess), sErr(sErr) {}

bool SQLResult::getSuccess() const {
    return bSuccess;
}

std::string SQLResult::getErrorMessage() const {
    return sErr;
}
