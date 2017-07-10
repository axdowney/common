#ifndef _CHEXUTILS_H
#define _CHEXUTILS_H
#include <string.h>
/* allocates memory which must be deallocated by caller */
/*unsigned char *hexEncode(unsigned char *szOrigin, size_t iSize);
unsigned char *hexDecode(unsigned char *szOrigin, size_t iSize);*/

unsigned char charToHex(unsigned char c, int iUpper);
unsigned char hexToChar(unsigned char c);
int HexEncode(const unsigned char *szOrigin, size_t iOriginSize, unsigned char *szDest, size_t iDestSize, int iUpper);
/*int hexEncode(unsigned char *szOrigin, size_t iOriginSize, unsigned char *szDest, size_t iDestSize);*/
int HexDecode(const unsigned char *szOrigin, size_t iOriginSize, unsigned char *szDest, size_t iDestSize);

#endif

