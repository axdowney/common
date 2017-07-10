#include "HexUtils.h"
#include "CHexUtils.h"


std::string HexUtils::hexEncode(const std::string &sOrigin, bool bUpper) {
    size_t iOriginSize = sOrigin.size();
    size_t iDestSize = iOriginSize * 2;
    unsigned char *szDest = new unsigned char[iDestSize]();
    HexEncode(reinterpret_cast<const unsigned char *>(sOrigin.c_str()), sOrigin.size(), szDest, iDestSize, bUpper);
    std::string sRet(reinterpret_cast<char *>(szDest), iDestSize);
    delete [] szDest;
    return sRet;
}

std::string HexUtils::hexDecode(const std::string &sOrigin) {
    size_t iOriginSize = sOrigin.size();
    size_t iDestSize = iOriginSize / 2;
    unsigned char *szDest = new unsigned char[iDestSize]();
    HexDecode(reinterpret_cast<const unsigned char *>(sOrigin.c_str()), iOriginSize, szDest, iDestSize);
    std::string sRet(reinterpret_cast<char *>(szDest), iDestSize);
    delete [] szDest;
    return sRet;
}

