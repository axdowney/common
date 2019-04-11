#include "HexUtils.h"
extern "C" {
#include "CHexUtils.h"
}
#include <stack>
#include <vector>

int HexUtils::iMine = 0;
int HexUtils::iTheirs = 0;
std::chrono::duration<double> HexUtils::elapsed_seconds(0.0);
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

int HexUtils::xtoi(char c, int iBase)
{
	int iRet = -1;
	if (iBase > 1 && iBase < 37) {
		if ('0' <= c && c <= '9') {
			iRet = c - '0';
		}
		else if ('A' <= c && c <= 'Z') {
			iRet = c - 'A' + 10;
		}
		else if ('a' <= c && c <= 'z') {
			iRet = c - 'a' + 10;
		}
		if (iRet >= iBase) {
			iRet = -1;
		}
	}
	return iRet;
}

std::string HexUtils::itox(int i, int iBase, bool bUpper)
{
	std::string sSign;
	std::string sRet;
	if (iBase > 1 && iBase < 37) {
		if (i < 0) {
			sSign = "-";
			i = -i;
		}
		do {
			int r = i % iBase;
			i = i / iBase;
			//if (r != 0) {
				if (r < 10) {
					sRet = std::string(1, '0' + (char) r) + sRet;
				}
				else {
					if (bUpper) {
						sRet = std::string(1, 'A' + (char)r - 10) + sRet;
					}
					else {
						sRet = std::string(1, 'a' + (char)r - 10) + sRet;
					}
				}
			//} 
		} while (i);
	}
	return sSign + sRet;
}

std::string HexUtils::convertBase(const std::string & s, int iBaseFrom, int iBaseTo)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	if (s.empty()) {
		return "Error empty string.";
	}
	if (iBaseFrom < 2 && iBaseFrom > 36) {
		return "Error invalid from base " + std::to_string(iBaseFrom);
	}
	if (iBaseTo < 2 && iBaseTo > 36) {
		return "Error invalid to base " + std::to_string(iBaseTo);
	}
	size_t iREnd = 0;
	std::string sSign;
	if (s[0] == '-' || s[0] == '+') {
		sSign = s.substr(0, 1);
		iREnd = 1;
	}
	std::stack<int> st;
	//st.reserve(ceil(log(iBaseFrom) / log(iBaseTo)));
	const char *sQuot = s.c_str() + iREnd;
	size_t iSize = s.size() - iREnd;
	int iRem = 0;
	std::vector<int> vec(iSize);
	StrToDigits(sQuot, iSize, vec.data(), iBaseFrom);
	int iStart = 0;
	int iTmp = 0;
	while (iStart < iSize) {
		iMine += BigNumDiv(vec.data() + iStart, vec.size() - iStart, iBaseFrom, iBaseTo, vec.data() + iStart, &iRem, &iTmp);
		st.push(iRem);
		iStart += iTmp;
	}
	std::string sRet;
	sRet.reserve(st.size());
	while (!st.empty()) {
		sRet += itox(st.top(), iBaseTo);
		st.pop();
	}
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	return sSign + sRet;
}

bool HexUtils::div(const std::string & s, int iBaseFrom, int iDivisor, std::string & sQuot, int & iRem)
{
	if (s.empty()) {
		return false;
	}
	if (iBaseFrom < 2 || iBaseFrom > 36) {
		return false;
	}
	std::string sSign;
	int iSign = 1;
	int iBeg = 0;
	if (s[0] == '+') {
		iBeg = 1;
	}
	else if (s[0] == '-') {
		iBeg = 1;
		iSign = -1;
	}
	if (iDivisor < 0) {
		iDivisor = -iDivisor;
		iSign = -1;
	}
	if (iSign < 0) {
		sSign = "-";
	}
	std::vector<int> vec(s.size() - iBeg, 0);
	for (int i = iBeg; i < s.size(); ++i) {
		vec[i - iBeg] = xtoi(s[i], iBaseFrom);
		if (vec[i - iBeg] < 0) {
			return false;
		}
	}

	sQuot = iSign < 0 ? "-" : "";
	sQuot.reserve(vec.size() + 1);
	int iCurr = 0;
	for (size_t i = 0; i < vec.size(); ++i) {
		++iMine;
		iCurr = iCurr * iBaseFrom + vec[i];
		div_t ans = std::div(iCurr, iDivisor);
		iCurr = ans.rem;
		if (ans.quot != 0 || !sQuot.empty()) {
			sQuot += itox(ans.quot, iBaseFrom);
		}
	}
	iRem = iCurr;
	if (sQuot.size() == iBeg) {
		sQuot += "0";
	}
	/*if (iSign < 0) {
		iRem = -iRem;
		sQuot = "-" + sQuot;
	}*/

	return true;
}

