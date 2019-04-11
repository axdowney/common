#include "StringUtils.h"
#include "StringUtils.h"
#include "StringUtils.h"
/* Copyright (C) 2017-2018 Alexander Downey */
#include "StringUtils.h"

#include <string>
#include <fstream>
#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

void StringUtils::splitFirst(const std::string str, const std::string & delim, std::string & sFirst, std::string & sLast, bool bFirst)
{
	size_t t = str.find_first_of(delim);
	if (t != std::string::npos) {
		sFirst = str.substr(0, t);
		sLast = str.substr(t + delim.size());
	}
	else if (bFirst) {
		sFirst = str;
		sLast = "";
	}
	else {
		sFirst = "";
		sLast = str;
	}
}

void StringUtils::splitLast(const std::string str, const std::string & delim, std::string & sFirst, std::string & sLast, bool bFirst)
{
	size_t t = str.find_last_of(delim);
	if (t != std::string::npos) {
		sFirst = str.substr(0, t);
		sLast = str.substr(t + 1);
	}
	else if (bFirst) {
		sFirst = str;
		sLast = "";
	}
	else {
		sFirst = "";
		sLast = str;
	}
}

//Copied from https://stackoverflow.com/questions/289347/using-strtok-with-a-stdstring
void StringUtils::split(const string& str, const string& delim, vector<string>& parts, bool bExact, bool bIncludeEmpty, std::vector<std::string> *delims) {
    if (delim.empty()) {
        if (!str.empty() || bIncludeEmpty) {
            parts.push_back(str);
        }
        return;
    }
    size_t start = 0, end = 0;
    while (end < str.size()) {
        if (!bExact) {
            start = end;
            while (start < str.size() && (delim.find(str[start]) != string::npos)) {
                start++;  // skip initial whitespace
            }
			if (delims) {
				delims->push_back(std::string(str, end, start - end));
			}
            end = start;
            while (end < str.size() && (delim.find(str[end]) == string::npos)) {
                end++; // skip to end of word
            }
            if (end-start != 0 || bIncludeEmpty) {  // just ignore zero-length strings.
                parts.push_back(string(str, start, end-start));
            }
        } else {
            end = str.find(delim, start);
            if (start != end || bIncludeEmpty) {
                parts.push_back(str.substr(start, end - start));
            }

            if (end == string::npos) {
                break;
            } else {
                start = end + delim.size();
            }
        }
    }
}

void StringUtils::combine(std::string& str, const std::string& delim, const std::vector<std::string>& parts, bool bIncludeEmpty) {
    str = "";
    for (size_t i = 0; i < parts.size(); ++i) {
        if (bIncludeEmpty || !parts[i].empty()) {
            if (!str.empty() || bIncludeEmpty && i > 0) {
                str += delim;
            }

            str += parts[i];
        }
    }
}

std::string StringUtils::getExt(const std::string sFile) {
    vector<string> parts;
    split(sFile, ".", parts);
    return parts.size() > 1 ? parts.back() : std::string();
}

std::string StringUtils::replace(const std::string& str, const std::string& sReplace, const std::string &sReplaceWith, bool bExact) {
    std::vector<std::string> vec;
    std::string sRet;
    split(str, sReplace, vec, bExact, true);
    combine(sRet, sReplaceWith, vec, true);
    return sRet;
}

std::string StringUtils::under_scoreToCamelCase(const std::string &str) {
	std::vector<std::string> vec;
	std::string sRet;
	split(str, "_", vec, true, false);
	for (int i = 0; i < vec.size(); ++i) {
		vec[i][0] = toupper(vec[i][0]);
	}
	combine(sRet, "", vec, false);
	return sRet;
}

std::string StringUtils::trim(const std::string & str, bool bExtend)
{
	int iFirst = 0;
	int iEnd = str.size() - 1;
	while (iFirst <= iEnd && (isspace((unsigned char)str[iFirst]) || bExtend && str[iFirst] < 0)) {
		++iFirst;
	}
	while (iEnd >= iFirst && (isspace((unsigned char)str[iEnd]) || bExtend && str[iEnd] < 0)) {
		--iEnd;
	}
	return iFirst <= iEnd ? str.substr(iFirst, iEnd - iFirst + 1) : std::string();
}

std::string StringUtils::trimChar(const std::string & str, char c)
{
	int iFirst = 0;
	int iEnd = str.size() - 1;
	while (iFirst <= iEnd && str[iFirst] == c) {
		++iFirst;
	}
	while (iEnd >= iFirst && str[iEnd] == c) {
		--iEnd;
	}
	return iFirst <= iEnd ? str.substr(iFirst, iEnd - iFirst + 1) : std::string();
}

bool StringUtils::isTrue(std::string str)
{
	for (char &c : str) {
		c = toupper(c);
	}
	return str == "TRUE";
}

bool StringUtils::isFalse(std::string str)
{
	for (char &c : str) {
		c = toupper(c);
	}
	return str == "FALSE";
}

bool StringUtils::readConfig(std::string sConfigFile, std::map<std::string, std::string> &mapOptions, const std::string &sDelim, bool bTrim, bool bExtend) {
	std::ifstream fin;
	fin.open(sConfigFile.c_str());
	bool bOK = fin.good();
	if (bOK) {
		std::string sLine;
		std::getline(fin, sLine);
		while (fin.good()) {
			std::string sKey;
			std::string sValue;
			StringUtils::splitFirst(sLine, sDelim, sKey, sValue, true);
			if (bTrim) {
				std::cerr << "Before trim \"" << sKey; 
				sKey = trim(sKey, bExtend);
				std::cerr << "\" after trim \"" << sKey << "\"\n";
				std::cerr << "Before trim \"" << sValue;
				sValue = trim(sValue, bExtend);
				std::cerr << "\" after trim \"" << sValue << "\"\n";
			}
			mapOptions[sKey] = sValue;
			std::getline(fin, sLine);
		}
	}
	return bOK;
}

std::string StringUtils::repeatString(const std::string & sCopy, size_t n, const std::string & sDelim)
{
	std::string sRet;
	if (n > 0) {
		sRet = sCopy;
		for (size_t t = 1; t < n; ++t) {
			sRet += sDelim + sCopy;
		}
	}
	return sRet;
}

std::string StringUtils::toalnum(const std::string &str, int iCase, bool bSign, bool bFloat)
{
	int(*cond)(int) = isalnum;
	if (bSign && bFloat) {
		cond = isalfloatsign;
	}
	else if (bSign) {
		cond = isalnumsign;
	}
	else if (bFloat) {
		cond = isalfloat;
	}
	std::string sRet;
	for (const char &c : str) {
		if (cond((unsigned char)c)) {
			if (iCase > 0) {
				sRet += toupper((unsigned char)c);
			}
			else if (iCase < 0) {
				sRet += tolower((unsigned char)c);
			}
			else {
				sRet += c;
			}
		}
	}
	return sRet;
}

int StringUtils::sprintf(std::string & sOut, const char * format, ...)
{
	va_list args;
	va_start(args, format);
	int result = vsnprintf(NULL, 0, format, args);
	va_end(args);
	va_start(args, format);
	char *cz = new char[result + 1]();
	if ((result = vsnprintf(cz, result + 1, format, args)) > 0) {
		sOut += cz;
	}
	va_end(args);
	delete[] cz;
	
	return result;
}

std::string StringUtils::filterInclude(const std::string & str, const std::set<char> &sInclude)
{
	std::string sRet;
	if (!sInclude.empty()) {
		for (size_t i = 0; i < str.size(); ++i) {
			if (sInclude.find(str[i]) != sInclude.end()) {
				sRet += str[i];
			}
		}
	}
	return sRet;
}

std::string StringUtils::d2string(double d, int iPrecision)
{
	std::stringstream ss;
	ss << std::fixed << setprecision(iPrecision) << d;
	return ss.str();
}

int StringUtils::isalnumsign(int c)
{
	return isalnum(c) || c == '-' || c == '+';
}

int StringUtils::isalfloat(int c)
{
	return isalnum(c) || c == '.';
}

int StringUtils::isalfloatsign(int c)
{
	return isalnum(c) || c == '.' || c == '-' || c == '+';
}

int StringUtils::isInt(const std::string & s, std::string & sPrefix, int & i, std::string & sPostfix)
{
	int iRet = 1;
	int n = s.find_first_of("0123456789");
	if (n != std::string::npos) {
		if (n > 0 && (s[n - 1] == '-')) {
			--n;
		}
		if (n > 0) {
			sPrefix = s.substr(0, n);
		}
		else {
			sPrefix = "";
		}
		int m = s.find_first_not_of("0123456789", n + 1);
		if (m != std::string::npos) {
			i = atoi(s.substr(n, m).c_str());
			sPostfix = s.substr(m);
			iRet = 3;
		}
		else {
			i = atoi(s.substr(n).c_str());
			sPostfix = "";
			iRet = 2;
		}
	}
	else {
		sPrefix = s;
	}
	return iRet;
}
