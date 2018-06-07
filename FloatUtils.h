/* Copyright (C) 2017 Alexander Downey */
#ifndef _FLOATUTILS_H
#define _FLOATUTILS_H

#include <map>
#include <vector>
#include <string>

class FloatUtils {
    public:
		static const int kiMaxColor = 0x0FF;
        static bool approximatelyEqual(long double a, long double b, long double epsilon);
        static bool essentiallyEqual(long double a, long double b, long double epsilon);
        static bool precisionCompare(long double left, long double right, unsigned int precision);
        static bool diffEqual(long double left, long double right, long double diff);
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

		std::string fpclassifyString(int fpclass);
};


/* Generic Interpolation Functions */

template<typename typeX, typename typeY>
typeY FloatUtils::interp1(typeX X0, typeX X1, typeY Y0, typeY Y1, typeX XQ) {
    typeY yRet = typeY();
    if (XQ < X0 || XQ > X1) {
        /* Extrapolate */
        yRet = Y0 * ((typeX) 1 - (XQ - X0)/(X1 - X0)) + Y1 * ((typeX) 1 - (X1 - XQ)/(X1 - X0));
    } else {
        yRet = (Y0*(X1 - XQ) + Y1*(XQ - X0))/(X1 - X0);
    }

    return yRet;
}

template<typename typeX, typename typeY>
typeY FloatUtils::interp1(const std::map<typeX, typeY> &mapXY, typeX dXQ) {
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
#endif
