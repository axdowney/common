/* Copyright (C) 2017-2018 Alexander Downey */
#ifndef _STRINGUTILS_H
#define _STRINGUTILS_H
#include <string>
#include <vector>
#include <utility>
#include <map>



class StringUtils {
    public:
		static void splitFirst(const std::string str, const std::string &delim, std::string &sFirst, std::string &sLast, bool bFirst = true);
		static void splitLast(const std::string str, const std::string &delim, std::string &sFirst, std::string &sLast, bool bFirst = true);
        static void split(const std::string& str, const std::string& delim, std::vector<std::string>& parts, bool bExact = false, bool bIncludeEmpty = false);
        static void combine(std::string& str, const std::string& delim, const std::vector<std::string>& parts, bool bIncludeEmpty = false);
        static std::string getExt(const std::string sFile);
        static std::string replace(const std::string& str, const std::string& sReplace, const std::string &sReplaceWith, bool bExact = true);
		static std::string under_scoreToCamelCase(const std::string &str);
		static std::string trim(const std::string &str);
		static bool isTrue(std::string str);
		static bool isFalse(std::string str);
		static void readConfig(std::string sConfigFile, std::map<std::string, std::string> &mapOptions, const std::string &sDelim, bool bTrim = true);
		static std::string repeatString(const std::string &sCopy, size_t n, const std::string &sDelimc= "");
		static std::string toalnum(const std::string &str, int iCase);
		static int sprintf(std::string &sOut, char* format, ...);

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		static const char slash = '\\';
#else
		static const char slash = '/';
#endif
};
#endif