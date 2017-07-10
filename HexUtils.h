#ifndef _HEXUTILS_H
#define _HEXUTILS_H

#include <string>


extern "C" int HexEncode(const unsigned char *szOrigin, size_t iOriginSize, unsigned char *szDest, size_t iDestSize, int iUpper);
extern "C" int HexDecode(const unsigned char *szOrigin, size_t iOriginSize, unsigned char *szDest, size_t iDestSize);
class HexUtils {
    public:
        static std::string hexEncode(const std::string &sOrigin, bool bUpper = true);
        static std::string hexDecode(const std::string &sOrigin);
};





#endif
