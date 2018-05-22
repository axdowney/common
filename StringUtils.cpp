#include "StringUtils.h"
#include "StringUtils.h"
#include "StringUtils.h"
/* Copyright (C) 2017-2018 Alexander Downey */
#include "StringUtils.h"

#include <string>
#include <fstream>
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
void StringUtils::split(const string& str, const string& delim, vector<string>& parts, bool bExact, bool bIncludeEmpty) {
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

std::string StringUtils::trim(const std::string & str)
{
	int iFirst = 0;
	int iEnd = str.size() - 1;
	while (iFirst <= iEnd && isspace(str[iFirst])) {
		++iFirst;
	}
	while (iEnd >= iFirst && isspace(str[iEnd])) {
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

void StringUtils::readConfig(std::string sConfigFile, std::map<std::string, std::string> &mapOptions, const std::string &sDelim, bool bTrim) {
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
				sKey = trim(sKey);
				sValue = trim(sValue);
			}
			mapOptions[sKey] = sValue;
			std::getline(fin, sLine);
		}
	}
}

std::string StringUtils::repeatString(const std::string & sCopy, size_t n)
{
	std::string sRet;
	for (size_t t = 0; t < n; ++t) {
		sRet += sCopy;
	}
	return sRet;
}

std::string StringUtils::toalnum(const std::string &str, int iCase)
{
	std::string sRet;
	for (const char &c : str) {
		if (isalnum(c)) {
			if (iCase > 0) {
				sRet += toupper(c);
			}
			else if (iCase < 0) {
				sRet += tolower(c);
			}
			else {
				sRet += c;
			}
		}
	}
	return sRet;
}
