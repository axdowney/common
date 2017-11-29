/* Copyright (C) 2017 Alexander Downey */
#include <string>
#include <vector>

class StringUtils {
    public:
        static void split(const std::string& str, const std::string& delim, std::vector<std::string>& parts);
        static void combine(std::string& str, const std::string& delim, const std::vector<std::string>& parts, bool bIncludeEmpty = false);
        static std::string getExt(const std::string sFile);
};
