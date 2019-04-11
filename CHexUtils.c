#include "CHexUtils.h"
#include <string.h>
#include <stdlib.h>
/*unsigned char *hexEncode(unsigned char *szOrigin, size_t iSize) {
    return szOrigin;
}

unsigned char *hexDecode(unsigned char *szOrigin, size_t iSize) {
    return szOrigin;
}*/




unsigned char charToHex(unsigned char c, int iUpper) {
    unsigned char cRet = '0';
    if (c < 0xA) {
        cRet = '0' + c;
    } else if (c < 0x10) {
        if (iUpper == 0) {
            cRet = 'a' + c - 0xa;
        } else {
            cRet = 'A' + c - 0xA;
        }
    }

    return cRet;
}

unsigned char hexToChar(unsigned char c) {
    unsigned char cRet = '\000';
    if (c >= '0' && c <= '9') {
        cRet = c - '0';
    } else if (c >= 'A' && c <= 'F') {
        cRet = c - 'A' + 0xA;
    } else if (c >= 'a' && c <= 'f') {
        cRet = c - 'a' + 0xa;
    }

    return cRet;
}




int HexEncode(const unsigned char *szOrigin, size_t iOriginSize, unsigned char *szDest, size_t iDestSize, int iUpper) {
    int iRet = -1;
    if (iDestSize >= iOriginSize * 2) {
        size_t i = 0;
        size_t j = 0;
        for (i = 0; i < iOriginSize; i++) { 
            szDest[j] = charToHex(szOrigin[i] >> 4, iUpper);
            szDest[j + 1] = charToHex(szOrigin[i] & 0x0F, iUpper);
            j += 2;
        }

        iRet = i;
    }

    return iRet;
}

int HexDecode(const unsigned char *szOrigin, size_t iOriginSize, unsigned char *szDest, size_t iDestSize) {
    int iRet = -1;
    if (iDestSize >= iOriginSize / 2) {
        size_t i = 0;
        size_t j = 0;
        for (i = 0; i < iOriginSize; i += 2) {
            szDest[j] = hexToChar(szOrigin[i + 1]);
            szDest[j] |= hexToChar(szOrigin[i]) << 4;
            ++j;
        }

        iRet = i;
    }

    return iRet;
    return 0;
}

int StrToDigits(const char * cz, int iSize, int * iarr, int iBase)
{
	int iRet = 0;
	if (1 < iBase && iBase < 37) {
		for (iRet = 0; iRet < iSize; ++iRet) {
			if ('0' <= cz[iRet] && cz[iRet] <= '9') {
				iarr[iRet] = cz[iRet] - '0';
			}
			else if ('A' <= cz[iRet] && cz[iRet] <= 'Z') {
				iarr[iRet] = cz[iRet] - 'A' + 10;
			}
			else if ('a' <= cz[iRet] && cz[iRet] <= 'z') {
				iarr[iRet] = cz[iRet] - 'a' + 10;
			}
			else {
				break;
			}
		}
	}
	return iRet;
}

int BigNumDiv(int * iarr, int iSize, int iBase, int iDivisor, int * iaQuot, int * iRem, int *iStart)
{

	int iRet = 0;
	*iRem = 0;
	*iStart = 0;
	for (; iRet < iSize; ++iRet) {
		//++iMine;
		*iRem = (*iRem) * iBase + iarr[iRet];
		div_t ans = div(*iRem, iDivisor);
		iaQuot[iRet] = ans.quot;
		*iRem = ans.rem;
		if (iaQuot[*iStart] == 0) {
			++(*iStart);
		}
	}
	return iRet;
}
