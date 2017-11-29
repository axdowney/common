#include <sstream>

#include <boost/date_time/special_defs.hpp>
using namespace boost::date_time;
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/local_time/local_date_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
using namespace boost::local_time;
#include <boost/date_time/local_time/local_time_io.hpp>


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

std::string DateTime::toString(const std::string &sFormat, bool bLocal) const {
    struct tm *ptmValue = NULL;
    if (bLocal) {
        ptmValue = localtime(&tValue);
    } else {
        ptmValue = gmtime(&tValue);
    }

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

bool DateTime::fromString(const std::string &sFormat, const std::string &sTime, bool bLocal) {
    struct tm tmValue;
    char *pc = strptime(sTime.c_str(), sFormat.c_str(), &tmValue);
    bool bOK = pc;
    local_time_input_facet *input_facet = new local_time_input_facet(sFormat);
    std::stringstream ss;
    ss.imbue(std::locale(ss.getloc(), input_facet));

    // This is our output date time.
    boost::local_time::local_date_time ldt(not_a_date_time);
    

    // Read the timestamp into ldt.
    ss.str(sTime);
    ss >> ldt;
    bOK = !ldt.is_special();
    if (bOK) {
        tmValue = to_tm(ldt);
    }
    std::cerr << ldt.is_special() << ldt.is_not_a_date_time() << ldt << std::endl;

    if (bOK) {
        if (bLocal) {
            this->tValue = mktime(&tmValue);
        } else {
            this->tValue = timegm(&tmValue);
        }
    }

    return bOK;
}

bool DateTime::operator==(const DateTime &dtLeft) const {
    return this->tValue == dtLeft.tValue;
}
