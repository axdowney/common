#ifndef _DATETIME_H
#define _DATETIME_H

#include <ctime>
#include <string>

class DateTime {
    public:
        DateTime();
        DateTime(time_t tValue);
        DateTime(const std::string &sFormat, const std::string &sTime);

        time_t toTime() const;
        void setTime(time_t tValue);

        std::string toString(const std::string &sFormat, bool bLocal = false) const;
        bool fromString(const std::string &sFormat, const std::string &sTime, bool bLocal = false);
        bool operator==(const DateTime &dtLeft) const;
        
    protected:
        time_t tValue;
};


#endif
