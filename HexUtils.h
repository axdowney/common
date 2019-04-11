#ifndef _HEXUTILS_H
#define _HEXUTILS_H

#include <string>
#include <chrono>


extern "C" int HexEncode(const unsigned char *szOrigin, size_t iOriginSize, unsigned char *szDest, size_t iDestSize, int iUpper);
extern "C" int HexDecode(const unsigned char *szOrigin, size_t iOriginSize, unsigned char *szDest, size_t iDestSize);
class HexUtils {
public:
	static std::string hexEncode(const std::string &sOrigin, bool bUpper = true);
	static std::string hexDecode(const std::string &sOrigin);
	static int xtoi(char c, int iBase = 16);
	static std::string itox(int i, int iBase = 16, bool bUpper = true);
	static std::string convertBase(const std::string &s, int iBaseFrom, int iBaseTo);
	static bool div(const std::string &s, int iBaseFrom, int iDivisor, std::string &sQuot, int &iRem);
	static int iMine, iTheirs;
	static std::chrono::duration<double> elapsed_seconds;


	static inline char * Convert(int from, int to, const char * s, char * out)
	{
		std::chrono::time_point<std::chrono::system_clock> start, end;
		start = std::chrono::system_clock::now();
		if (s == NULL)
			return NULL;

		if (from < 2 || from > 36 || to < 2 || to > 36) { return NULL; }

		int il = strlen(s);

		int *fs = new int[il];
		int k = 0;
		int i, j;


		for (i = il - 1; i >= 0; i--)
		{
			if (s[i] >= '0' && s[i] <= '9')
			{
				fs[k] = (int)(s[i] - '0');
			}
			else
			{
				if (s[i] >= 'A' && s[i] <= 'Z')
				{
					fs[k] = 10 + (int)(s[i] - 'A');
				}
				else if (s[i] >= 'a' && s[i] <= 'z')
				{
					fs[k] = 10 + (int)(s[i] - 'a');
				}
				else
				{
					delete[]fs;
					return NULL;
				} //only allow 0-9 A-Z characters
			}
			k++;
		}

		for (i = 0; i < il; i++)
		{
			if (fs[i] >= from)
				return NULL;
		}

		double x = ceil(log(from) / log(to));
		int ol = 1 + (il * x);

		int * ts = new int[ol];
		int * cums = new int[ol];

		for (i = 0; i < ol; i++)
		{
			ts[i] = 0;
			cums[i] = 0;
		}
		ts[0] = 1;


		//evaluate the output
		for (i = 0; i < il; i++) //for each input digit
		{
			for (j = 0; j < ol; j++) //add the input digit times (base:to from^i) to the output cumulator
			{
				++iTheirs;
				cums[j] += ts[j] * fs[i];
				int temp = cums[j];
				int rem = 0;
				int ip = j;
				do // fix up any remainders in base:to
				{
					//++iTheirs;
					div_t ans = std::div(temp, to);
					rem = ans.quot;//temp / to;
					cums[ip] = ans.rem;//temp - rem * to;
					ip++;
					if (ip >= ol)
					{
						if (rem > 0)
						{
							delete[]ts;
							delete[]cums;
							delete[]fs;
							return NULL;
						}
						break;
					}
					cums[ip] += rem;
					temp = cums[ip];
				} while (temp >= to);
			}

			for (j = 0; j < ol; j++)
			{
				ts[j] = ts[j] * from;
			}

			for (j = 0; j < ol; j++) //check for any remainders
			{
				int temp = ts[j];
				int rem = 0;
				int ip = j;
				do  //fix up any remainders
				{
					rem = temp / to;
					ts[ip] = temp - rem * to;
					ip++;
					if (ip >= ol)
					{
						if (rem > 0)
						{
							delete[]ts;
							delete[]cums;
							delete[]fs;
							return NULL;
						}
						break;
					}
					ts[ip] += rem;
					temp = ts[ip];
				} while (temp >= to);
			}
		}

		if (out == NULL)
		{
			out = (char*)malloc(sizeof(char) * (ol + 1));
		}

		int spos = 0;
		bool first = false; //leading zero flag
		for (i = ol - 1; i >= 0; i--)
		{
			if (cums[i] != 0)
			{
				first = true;
			}
			if (!first)
			{
				continue;
			}

			if (cums[i] < 10)
			{
				out[spos] = (char)(cums[i] + '0');
			}
			else
			{
				out[spos] = (char)(cums[i] + 'A' - 10);
			}
			spos++;
		}
		out[spos] = 0;

		delete[]ts;
		delete[]cums;
		delete[]fs;
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		return out;
	}
};

#endif
