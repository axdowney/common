/* Copyright (C) 2017-2018 Alexander Downey */
#ifndef _STRINGUTILS_H
#define _STRINGUTILS_H
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <sstream>



class StringUtils {
public:
	static void splitFirst(const std::string str, const std::string &delim, std::string &sFirst, std::string &sLast, bool bFirst = true);
	static void splitLast(const std::string str, const std::string &delim, std::string &sFirst, std::string &sLast, bool bFirst = true);
	static void split(const std::string& str, const std::string& delim, std::vector<std::string>& parts, bool bExact = false, bool bIncludeEmpty = false, std::vector<std::string> *delims = NULL);
	static void combine(std::string& str, const std::string& delim, const std::vector<std::string>& parts, bool bIncludeEmpty = false);
	static std::string getExt(const std::string sFile);
	static std::string replace(const std::string& str, const std::string& sReplace, const std::string &sReplaceWith, bool bExact = true);
	static std::string under_scoreToCamelCase(const std::string &str);
	static std::string trim(const std::string &str, bool bExtend = false);
	static std::string trimChar(const std::string &str, char c);
	static bool isTrue(std::string str);
	static bool isFalse(std::string str);
	static bool readConfig(std::string sConfigFile, std::map<std::string, std::string> &mapOptions, const std::string &sDelim, bool bTrim = true, bool bExtend = false);
	static std::string repeatString(const std::string &sCopy, size_t n, const std::string &sDelimc = "");
	static std::string toalnum(const std::string &str, int iCase, bool bSign = false, bool bFloat = false);
	static int sprintf(std::string &sOut, const char* format, ...);
	static std::string filterInclude(const std::string &str, const std::set<char> &sInclude);
	static std::string d2string(double d, int iPrecision = 17);
	static int isalnumsign(int c);
	static int isalfloat(int c);
	static int isalfloatsign(int c);
	static int isInt(const std::string &s, std::string &sPrefix, int &i, std::string &sPostfix);
	template<typename T>
	static std::string to_string(const T& val) {
		std::stringstream ss;
		ss << val;
		return ss.str();
	}

	template<typename... Args>
	static void NameValue(std::map<std::string, std::string> &mapOptions, Args... args) {
		std::vector<std::string> vec;
		int dummy[] = { 0, (vec.push_back(StringUtils::to_string((args))), 0)... };
		std::string sName;
		for (int i = 1; i < vec.size(); i += 2) {
			mapOptions[vec[i - 1]] = vec[i];
		}
		if (vec.size() & 1) {
			mapOptions[vec.back()] = "";
		}

	}



#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		static const char slash = '\\';
#else
		static const char slash = '/';
#endif
};
#endif