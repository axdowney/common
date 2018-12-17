/* Copyright (C) 2017 Alexander Downey */
#ifndef _FLOATUTILS_H
#define _FLOATUTILS_H

#include <map>
#include <vector>
#include <string>
#include <algorithm>

class FloatUtils {
    public:
		static const int kiMaxColor = 0x0FF;
        static bool approximatelyEqual(long double a, long double b, long double epsilon);
        static bool essentiallyEqual(long double a, long double b, long double epsilon);
        static bool precisionCompare(long double left, long double right, unsigned int precision);
        static bool diffEqual(long double left, long double right, long double diff);
		static bool sigdigEqual(long double left, long double right, size_t sigdigits, bool bRound = false);
		static bool frexEqual(long double left, long double right, size_t sigdigits);
		static int edgeCases(long double left, long double right, bool bInfMatch = true, bool bNaNMatch = false);

		static std::vector<double> generateSteps(double dBegin, double dEnd, size_t tNum);
		static std::vector<double> generateStepsLogx(double dBegin, double dEnd, size_t tNum, size_t base);
		static std::vector<double> generateStepsLn(double dBegin, double dEnd, size_t tNum);
		static double logx(double a, double base);
		static bool calcRGB(double dMin, double dMax, double dVal, double &dRed, double &dGreen, double &dBlue);
		static bool calcRGB(double dMin, double dMax, double dVal, int &iRed, int &iGreen, int &iBlue);

        template<typename typeX, typename typeY>
        static typeY interp1(typeX X0, typeX X1, typeY Y0, typeY Y1, typeX XQ);

        template<typename typeX, typename typeY>
        static typeY interp1(const std::map<typeX, typeY> &mapXY, typeX dXQ);

        template<typename typeX, typename typeY>
        static std::vector<typeY> interp1(const std::map<typeX, typeY> &mapXY, const std::vector<typeX> vecXQ);

		template<typename typeX, typename typeY>
		static typeY interp1Improve(const std::map<typeX, typeY> &mapXY, typeX dXQ);

		std::string fpclassifyString(int fpclass);

		static long double truncDiff(long double a, long double b);
		static long double diffZeroRel(long double a, long double b, long double eps);
		static long double diffZeroAbs(long double a, long double b, long double eps);

		template<template<class, class> class C, class T>
		static T getMode(const C<T, std::allocator<T> > &container) {
			std::map<T, int> mapCount;
			auto iter = mapCount.end();
			for (T curr : container) {
				++mapCount[curr];
				if (iter == mapCount.end() || iter->second < mapCount[curr]) {
					iter = mapCount.find(curr);
				}
			}
			T tRet = T();
			if (iter != mapCount.end()) {
				tRet = iter->first;
			}
			return tRet;
		}

		template<class Iterator, class T>
		static bool getMedian(Iterator begin, Iterator end, T &tDest) {
			bool bRet = begin != end;
			if (bRet) {
				size_t siz = std::distance(begin, end);
				size_t iCount = 0;
				size_t iMid = siz / 2;
				Iterator iter = begin;
				while (iCount < iMid) {
					++iter;
					++iCount;
				}
				tDest = *iter;
				if ((siz & 1) == 0) {
					--iter;
					tDest = (*iter + tDest) / 2;
				}
			}
			return bRet;
		}

		template<template<class, class, class> class C, class T>
		static T getMedian(const C<T, std::less<T>, std::allocator<T> > &container) {
			T tRet = T();
			getMedian(container.begin(), container.end(), tRet);
			return tRet;
		}

		template<template<class, class> class C, class T>
		static T getMedian(C<T, std::allocator<T> > container) {
			T tRet = 0;
			if (container.size()) {
				std::sort(container.begin(), container.end());
				getMedian(container.begin(), container.end(), tRet);
			}
			return tRet;
		}

		enum RED_OP {
			RED_MIN,
			RED_MAX,
			RED_SUM,
			RED_PROD,
			RED_LAND,
			RED_LOR,
			RED_BAND,
			RED_BOR,
			RED_LNOR,
			RED_LNAND,
			RED_BNOR,
			RED_BNAND,

			RED_LXOR,
			RED_LXNOR,
			RED_BXOR,
			RED_BXNOR,

			RED_LXAND = RED_LXNOR,
			RED_BXAND = RED_BXNOR,

			RED_AVG,
			RED_MED,
			RED_MODE,
			RED_MEAN_DEV,
			RED_MEDIAN_DEV,
			RED_STD_DEV,
			RED_BEGIN,
			RED_END
		};
		
		template <class C>
		static double diffAvg(const C &container, double dSub) {
			double dRet = 0;
			if (container.size() > 0) {
				for (auto d : container) {
					dRet += std::abs(d - dSub);
				}
				dRet /= container.size();
			}
			return dRet;
		}

		template <class C>
		static double stdDev(const C &container, double dDev) {
			size_t N = container.size() - 1;
			double dRet = -1;
			if (N > 0) {
				for (double d : container) {
					dRet += std::pow(d - dDev, 2);
				}
				dRet = std::sqrt(dRet / N);
			}

			return dRet;
		}

		static double reduceOp(double dLeft, RED_OP e, double dRight);

		static double reduce(const std::vector<double> &a, RED_OP e) {
			double dRet = 0;
			if (!a.empty()) {
				switch (e) {
				case RED_BEGIN:
					dRet = a.front();
					break;
				case RED_END:
					dRet = a.back();
					break;
				case RED_AVG:
					dRet = reduce(a, RED_SUM) / a.size();
					break;
				case RED_MED:
				{
					dRet = getMedian(a);
				}
					break;
				case RED_MODE:
					dRet = getMode(a);
					break;
				case RED_MEAN_DEV:
					dRet = diffAvg(a, reduce(a, RED_AVG));
					break;
				case RED_MEDIAN_DEV:
					dRet = diffAvg(a, getMedian(a));
					break;
				case RED_STD_DEV:
					dRet = stdDev(a, reduce(a, RED_AVG));
					break;
				default:
					if (e >= RED_MIN && e < RED_AVG) {
						dRet = a.front();
						for (size_t i = 1; i < a.size(); ++i) {
							dRet = reduceOp(dRet, e, a[i]);
						}
					}
					break;
				}
			}
			return dRet;
		}

		static double possibilities(double n, double r, bool bRep, bool bOrder);

		template<template<class, class> class Container, typename TypeFrom, typename TypeTo>
		Container<TypeTo, std::allocator<TypeTo> > &&castContainer(const Container<TypeFrom, std::allocator<TypeFrom> > &con) {
			Container<TypeTo, std::allocator<TypeTo> > cond(con.begin(), con.end());
			return cond;
		}


		static double series(long long int i0, long long int in, double (*f_ptrJoin)(double dTotal, double dY), double (*f_ptrTransform)(long long int));
		static double summation(long long int i0, long long int in);
		static double product(long long int i0, long long int in);
		static double factorial(long long int n);
		template <typename T>
		T absub(T a, T b);
};


/* Generic Interpolation Functions */

template<typename typeX, typename typeY>
typeY FloatUtils::interp1(typeX X0, typeX X1, typeY Y0, typeY Y1, typeX XQ) {
    typeY yRet = typeY();
    if (XQ < X0 || XQ > X1) {
        /* Extrapolate */
        yRet = Y0 * ((typeX) 1 - (XQ - X0)/(X1 - X0)) + Y1 * ((typeX) 1 - (X1 - XQ)/(X1 - X0));
    } else {
        //yRet = (Y0*(X1 - XQ) + Y1*(XQ - X0))/(X1 - X0);
		if ((X1 - XQ) < (XQ - X0)) {
			yRet = Y1 - (X1 - XQ) * (Y1 - Y0) / (X1 - X0);
		}
		else {
			yRet = Y0 + (XQ - X0) * (Y1 - Y0) / (X1 - X0);
		}
    }

    return yRet;
}

template<typename typeX, typename typeY>
typeY FloatUtils::interp1Improve(const std::map<typeX, typeY> &mapXY, typeX dXQ) {
    typeY dRet = 0;
    if (mapXY.size() > 1 ) {
        auto mapIter = mapXY.find(dXQ);
        if (mapIter != mapXY.end()) {
            return mapIter->second;
        } else {
            mapIter = mapXY.begin();
        }


        typeX dX1 = mapXY.rbegin()->first;
        typeX dX0 = mapIter->first;
        typeY dY1 = 0;
        typeY dY0 = mapIter->second;
        if (dXQ < mapIter->first || dXQ > dX1) {
            dY1 = mapXY.rbegin()->second;
        } else {
            ++mapIter;
            for (; mapIter != mapXY.end(); ++mapIter) {
                if (mapIter->first > dXQ) {
                    break;
                }
            }

            dX1 = mapIter->first;
            dY1 = mapIter->second;
            --mapIter;
            dX0 = mapIter->first;
            dY0 = mapIter->second;
        }

        dRet = FloatUtils::interp1(dX0, dX1, dY0, dY1, dXQ);
    }

    return dRet;
}

template<typename typeX, typename typeY>
std::vector<typeY> FloatUtils::interp1(const std::map<typeX, typeY> &mapXY, const std::vector<typeX> vecXQ) {
    std::vector<typeY> vecRet;
    if (mapXY.size() > 1 && !vecXQ.empty()) {
        for (auto dXQ : vecXQ) {
            vecRet.push_back(interp1(mapXY, dXQ));
        }
    }

    return vecRet;
}


template<typename typeX, typename typeY>
typeY FloatUtils::interp1(const std::map<typeX, typeY> &mapXY, typeX dXQ) {
	typeY dRet = 0;
	if (mapXY.size() > 1) {
		auto upper = mapXY.upper_bound(dXQ);
		auto lower = upper;
		typeX dX0, dX1;
		typeY dY0, dY1;
		if (upper == mapXY.end()) {
			--upper;
			dX1 = upper->first;
			dY1 = upper->second;
			--upper;
			dX0 = upper->first;
			dY0 = upper->second;
		}
		else if (upper == mapXY.begin()) {
			dX0 = upper->first;
			dY0 = upper->second;
			++upper;
			dX1 = upper->first;
			dY1 = upper->second;
		}
		else {
			--lower;
			if (lower->first == dXQ) {
				return lower->second;
			}
			else {
				dX0 = lower->first;
				dY0 = lower->second;
				dX1 = upper->first;
				dY1 = upper->second;
			}
		}

		dRet = FloatUtils::interp1(dX0, dX1, dY0, dY1, dXQ);
	}

	return dRet;
}



template <typename T>
T FloatUtils::absub(T a, T b) {
	return std::max(a, b) - std::min(a, b);
}

#endif
