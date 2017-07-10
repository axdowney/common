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

        std::string toString(const std::string &sFormat) const;
        bool fromString(const std::string &sFormat, const std::string &sTime);
        
    protected:
        time_t tValue;
};


#endif
