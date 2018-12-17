/* Copyright (C) 2017 Alexander Downey */
#include <cmath>
#include <algorithm>
#include "FloatUtils.h"


bool FloatUtils::approximatelyEqual(long double a, long double b, long double epsilon)
{
	int aclass = fpclassify(a);
	int bclass = fpclassify(b);
	bool bOK = aclass == bclass;
    return fpclassify(a) == fpclassify(b) && (fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon));
}

bool FloatUtils::essentiallyEqual(long double a, long double b, long double epsilon)
{
    return std::isfinite(a) && std::isfinite(b) && (fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon));
}

bool FloatUtils::precisionCompare(long double left, long double right, unsigned int precision) {
    return (long int) (left * pow(10, precision)) == (long int) (right * pow(10,precision));
}

bool FloatUtils::diffEqual(long double left, long double right, long double diff) {
    return fabs(left - right) <= fabs(diff);
}

bool FloatUtils::sigdigEqual(long double left, long double right, size_t sigdigits, bool bRound)
{
	int iMatch = edgeCases(left, right,true,true);
	bool bOK = iMatch >= 0;
	if (iMatch == 0) {
		int iExpLeft = 0;
		int iExpRight = 0;
		int64_t iLeft = 0;
		int64_t iRight = 0;
		double dRound = bRound ? 0.5 : 0.0;
		if (left != 0) {
			iExpLeft = std::floor(log10(fabs(left)));
			iLeft = left * pow<int64_t>(10, (long int)sigdigits - iExpLeft - 1) + dRound;
		}
		if (right != 0) {
			iExpRight = right == 0 ? 0 : std::floor(log10(fabs(right)));
			iRight = right * pow<int64_t>(10, (long int)sigdigits - iExpRight - 1) + dRound;
		}
 
		//bOK = iExpLeft == iExpRight && sigdigits > 0;	
			
		bOK = iLeft == iRight;
	}

	return bOK;
}

bool FloatUtils::frexEqual(long double left, long double right, size_t sigdigits)
{
	bool bOK = sigdigits > 0;
	if (bOK) {
		double sigLeft = 0;
		int iExpLeft = 0;
		sigLeft = std::frexp(left, &iExpLeft);
		double sigRight = 0;
		int iExpRight = 0;
		sigRight = std::frexp(right, &iExpRight);
		bOK = iExpLeft == iExpRight;
		if (bOK) {
			bOK = FloatUtils::precisionCompare(sigLeft, sigRight, sigdigits);
		}
	}
	return bOK;
}
/**
* @param bNaNMatch set to true to consider two NaNs as equal
* @return returns the match status
		* -1 definitely not a match
		*  0 could be a match
		*  1 definitely a match
*/
int FloatUtils::edgeCases(long double left, long double right, bool bInfMatch, bool bNaNMatch) {
	int iRet = 0;
	int aclass = fpclassify(left);
	int bclass = fpclassify(right);
	if (aclass == bclass) {
		switch (aclass) {
		case FP_INFINITE:
			if ((left > 0) == (right > 0)) {
				iRet = bInfMatch;
			}
			else {
				iRet = -1;
			}
			break;
		case FP_NAN:
			iRet = bNaNMatch ? 1 : 0;
			break;
		case FP_ZERO:
			iRet = 1;
			break;
		case FP_SUBNORMAL:
		case FP_NORMAL:
		default:
			break;
		}
	}
	else {
		iRet = std::isfinite(left) && std::isfinite(right) ? 0 : -1;
	}
	return iRet;
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
	bool bRet = dMin <= dVal && dVal <= dMax;
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

long double FloatUtils::truncDiff(long double a, long double b)
{
	long double c = a - b;
	int iLeftExp = std::floor(std::log10(c));
	int iRightExp = std::floor(std::log10(std::fabs(std::max(a, b))));
	int d = 16 - (iRightExp - iLeftExp);
	long int i = c * std::pow(10, d - iLeftExp);
	double cd = i * std::pow(10, iLeftExp - d);
	cd = std::nextafter(cd, DBL_MAX);
	return cd;
}

long double FloatUtils::diffZeroRel(long double a, long double b, long double eps)
{
	return essentiallyEqual(a,b,eps) ? 0.0 : a - b;
}

long double FloatUtils::diffZeroAbs(long double a, long double b, long double eps)
{
	double d = a - b;
	return fabs(d) < fabs(eps) ? 0. : d;
}

double FloatUtils::reduceOp(double dLeft, RED_OP e, double dRight)
{
	double dRet;
	bool bLeft = static_cast<bool>(dLeft);
	bool bRight = static_cast<bool>(dRight);
	long long int iLeft = static_cast<long long int>(dLeft);
	long long int iRight = static_cast<long long int>(dRight);
	switch (e) {
	case RED_MIN:
		dRet = std::min(dLeft, dRight);
		break;
	case RED_MAX:
		dRet = std::max(dLeft, dRight);
		break;
	case RED_SUM:
		dRet = dLeft + dRight;
		break;
	case RED_PROD:
		dRet = dLeft * dRight;
		break;
	case RED_LAND:
		dRet = bLeft && bRight;
		break;
	case RED_LOR:
		dRet = bLeft || bRight;
		break;
	case RED_BAND:
		dRet = iLeft & iRight;
		break;
	case RED_BOR:
		dRet = iLeft | iRight;
		break;
	case RED_LNOR:
		dRet = !(bLeft || bRight);
		break;
	case RED_LNAND:
		dRet = !(bLeft && bRight);
		break;
	case RED_BNOR:
		dRet = ~(iLeft | iRight);
		break;
	case RED_BNAND:
		dRet = ~(iLeft & iRight);
		break;
	case RED_LXOR:
		dRet = (bLeft ^ bRight);
		break;
	case RED_LXNOR:
		dRet = !(bLeft ^ bRight);
		break;
	case RED_BXOR:
		dRet = (iLeft ^ iRight);
		break;
	case RED_BXNOR:
		dRet = ~(iLeft & iRight);
		break;
	case RED_AVG:
		dRet = (dLeft + dRight) / 2;
		break;
	case RED_BEGIN:
		dRet = dLeft;
		break;
	case RED_END:
		dRet = dRight;
		break;
	}
	return dRet;
}

double FloatUtils::possibilities(double n, double r, bool bRep, bool bOrder)
{
	double dRet = -1.0;
	if (bOrder) {
		//Permutations
		if (bRep) {
			dRet = std::pow(n, r);
		}
		else if (n > r) {
			dRet = product(n, n - r + 1);
		}
	}
	else {
		//Combinations
		if (bRep) {
			dRet = factorial(r + n - 1) / (factorial(r) * factorial(n - 1));
		}
		else if (n > r) {
			dRet = factorial(n) / (factorial(r) * factorial(n - r));
		}
	}
	return dRet;
}

double FloatUtils::series(long long int i0, long long int in, double(*f_ptrJoin)(double dTotal, double dY), double(*f_ptrTransform)(long long int))
{
	if (f_ptrTransform == nullptr) {
		f_ptrTransform = [](long long int Xi) { return static_cast<double>(Xi); };
	}
	if (f_ptrJoin == nullptr) {
		f_ptrJoin = [](double dTotal, double dY) { return dTotal + dY; };
	}
	long long int iCurr = i0;
	double dRet = f_ptrTransform(i0);
	int iInc = i0 < in ? 1 : -1;
	for (iCurr = i0 + iInc; iCurr != (in + iInc); iCurr += iInc) {
		dRet = f_ptrJoin(dRet, f_ptrTransform(iCurr));
	}

	return dRet;
}

double FloatUtils::summation(long long int i0, long long int in)
{
	return series(i0, in, nullptr, nullptr);
}

double FloatUtils::product(long long int i0, long long int in)
{
	return series(i0, in, [](double a, double b) { return a * b; }, nullptr);
}

double FloatUtils::factorial(long long int n)
{
	double dRet = -1;
	if (n > 0) {
		if (n <= 1) {
			dRet = 1;
		}
		else {
			dRet = product(n, 2);
		}
	}
	return dRet;
}
