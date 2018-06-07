/* Copyright (C) 2017 Alexander Downey */
#include <cmath>
#include <algorithm>
#include "FloatUtils.h"


bool FloatUtils::approximatelyEqual(long double a, long double b, long double epsilon)
{
    return fpclassify(a) == fpclassify(b) && fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

bool FloatUtils::essentiallyEqual(long double a, long double b, long double epsilon)
{
    return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

bool FloatUtils::precisionCompare(long double left, long double right, unsigned int precision) {
    return (long int) (left * pow(10, precision)) == (long int) (right * pow(10,precision));
}

bool FloatUtils::diffEqual(long double left, long double right, long double diff) {
    return fabs(left - right) <= fabs(diff);
}

std::vector<double> FloatUtils::generateSteps(double dBegin, double dEnd, size_t tNum)
{
	std::vector<double> vecRet;
	if (dEnd > dBegin) {
		vecRet.resize(tNum, 0);
		for (size_t i = 0; i < tNum; ++i) {
			vecRet[i] = dBegin + i * (dEnd - dBegin) / tNum;
		}
	}
	return vecRet;
}

std::vector<double> FloatUtils::generateStepsLogx(double dBegin, double dEnd, size_t tNum, size_t base)
{
	
	dBegin = logx(dBegin, base);
	dEnd = logx(dEnd, base);
	std::vector<double> vecRet = generateSteps(dBegin, dEnd, tNum);
	for (size_t i = 0; i < vecRet.size(); ++i) {
		vecRet[i] = pow(base, vecRet[i]);
	}

	return vecRet;
}

std::vector<double> FloatUtils::generateStepsLn(double dBegin, double dEnd, size_t tNum)
{
	dBegin = log(dBegin);
	dEnd = log(dEnd);
	std::vector<double> vecRet = generateSteps(dBegin, dEnd, tNum);
	for (size_t i = 0; i < vecRet.size(); ++i) {
		vecRet[i] = exp(vecRet[i]);
	}

	return vecRet;
}

double FloatUtils::logx(double a, double base)
{
	return std::log(a) / std::log(base);
}


bool FloatUtils::calcRGB(double dMin, double dMax, double dVal, double &dRed, double &dGreen, double &dBlue)
{
	int iRed = -1;
	int iGreen = -1;
	int iBlue = -1;
	bool bRet = calcRGB(dMin, dMax, dVal, iRed, iGreen, iBlue);
	if (bRet) {
		dRed = (double)iRed / (double)kiMaxColor;
		dGreen = (double)iGreen / (double)kiMaxColor;
		dBlue = (double)iBlue / (double)kiMaxColor;
	}
	return bRet;
}

bool FloatUtils::calcRGB(double dMin, double dMax, double dVal, int &iRed, int &iGreen, int &iBlue)
{
	bool bRet = dMin < dVal && dVal < dMax;
	if (bRet) {
		double dRatio = 2 * (dVal - dMin) / (dMax - dMin);
		iBlue = std::max(0.0, kiMaxColor * (1 - dRatio));
		iRed = std::max(0.0, kiMaxColor * (dRatio - 1));
		iGreen = kiMaxColor - iBlue - iRed;
	}
	return bRet;
}

std::string FloatUtils::fpclassifyString(int fpclass)
{
	std::string sRet;
	switch (fpclass) {
	case FP_NAN:
		sRet = "NAN";
		break;
	case FP_INFINITE:
		sRet = "INFINITE";
		break;
	case FP_SUBNORMAL:
		sRet = "SUBNORMAL";
		break;
	case FP_ZERO:
		sRet = "ZERO";
		break;
	case FP_NORMAL:
		sRet = "NORMAL";
		break;
	default:
		sRet = "default";
		break;
	}
	return sRet;
}
