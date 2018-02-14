/* Copyright (C) 2017-2018 Alexander Downey */
#include "StringUtils.h"

#include <string>

using namespace std;

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
