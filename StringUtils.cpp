/* Copyright (C) 2017 Alexander Downey */
#include "StringUtils.h"

using namespace std;

//Copied from https://stackoverflow.com/questions/289347/using-strtok-with-a-stdstring
void StringUtils::split(const string& str, const string& delim, vector<string>& parts) {
    size_t start, end = 0;
    while (end < str.size()) {
	start = end;
	while (start < str.size() && (delim.find(str[start]) != string::npos)) {
	    start++;  // skip initial whitespace
	}
	end = start;
	while (end < str.size() && (delim.find(str[end]) == string::npos)) {
	    end++; // skip to end of word
	}
	if (end-start != 0) {  // just ignore zero-length strings.
	    parts.push_back(string(str, start, end-start));
	}
    }
}

void StringUtils::combine(std::string& str, const std::string& delim, const std::vector<std::string>& parts, bool bIncludeEmpty) {
    str = "";
    for (size_t i = 0; i < parts.size(); ++i) {
        if (bIncludeEmpty || !parts[i].empty()) {
            if (!str.empty()) {
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
