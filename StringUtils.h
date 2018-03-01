/* Copyright (C) 2017-2018 Alexander Downey */
#include <string>
#include <vector>

class StringUtils {
    public:
        static void split(const std::string& str, const std::string& delim, std::vector<std::string>& parts, bool bExact = false, bool bIncludeEmpty = false);
        static void combine(std::string& str, const std::string& delim, const std::vector<std::string>& parts, bool bIncludeEmpty = false);
        static std::string getExt(const std::string sFile);
        static std::string replace(const std::string& str, const std::string& sReplace, const std::string &sReplaceWith, bool bExact = true);
		static std::string under_scoreToCamelCase(const std::string &str);
};
