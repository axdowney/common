#include "DateTime.h"

DateTime::DateTime() {
    time(&tValue);
}

DateTime::DateTime(time_t tValue) {
    setTime(tValue);
}

DateTime::DateTime(const std::string &sFormat, const std::string &sTime) {
    fromString(sFormat, sTime);
}

time_t DateTime::toTime() const {
    return tValue;
}

void DateTime::setTime(time_t tValue) {
    this->tValue = tValue;
}

std::string DateTime::toString(const std::string &sFormat) const {
    struct tm *ptmValue = NULL;
    ptmValue = gmtime(&tValue);
    std::string sRet;
    if (ptmValue) {
        size_t tLength = sFormat.size() * 10;
        tLength = tLength < 100 ? 100 : tLength;
        char *psz = new char[tLength]();
        strftime(psz, tLength - 1, sFormat.c_str(), ptmValue);
        sRet = psz;
        delete [] psz;
    }

    return sRet;
}

bool DateTime::fromString(const std::string &sFormat, const std::string &sTime) {
    struct tm tmValue;
    bool bOK = NULL != strptime(sTime.c_str(), sFormat.c_str(), &tmValue);
    if (bOK) {
        this->tValue = mktime(&tmValue);
    }

    return bOK;
}
