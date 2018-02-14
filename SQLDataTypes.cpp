#include "SQLDataTypes.h"

SQLPoint::SQLPoint(double x, double y) : dX(x), dY(y)
{
	this->sExpr = "POINT(" + std::to_string(dX) + ", " + std::to_string(dY) + ")";
}

double SQLPoint::getX() const
{
	return dX;
}

double SQLPoint::getY() const
{
	return dY;
}

SQLLineString::SQLLineString(const std::vector<SQLPoint>& vec) : vecPoints(vec)
{
	sExpr = getLineString();
}

const std::vector<SQLPoint> &SQLLineString::getPoints() const
{
	return this->vecPoints;
}

std::vector<SQLPoint>& SQLLineString::getPoints()
{
	return getPoints();
}

std::string SQLLineString::getLineString() const
{
	return "LINESTRING(" + getPointsString() + ")";
}

std::string SQLLineString::getPointsString() const
{
	std::string sRet;
	for (size_t i = 0; i < vecPoints.size(); ++i) {
		if (i > 0) {
			sRet += ", ";
		}

		sRet += std::to_string(vecPoints[i].getX()) + " " + std::to_string(vecPoints[i].getY());
	}

	return sRet;
}

SQLPolygon::SQLPolygon(const std::vector<SQLLineString>& vec) : vecRings(vec)
{
	sExpr = getPolygonString();
}

const std::vector<SQLLineString>& SQLPolygon::getRings() const
{
	return vecRings;
}

std::vector<SQLLineString>& SQLPolygon::getRings()
{
	return vecRings;
}

std::string SQLPolygon::getPolygonString() const
{
	std::string sRet = "POLYGON(";
	for (size_t i = 0; i < vecRings.size(); ++i) {
		if (i > 0) {
			sRet += ", ";
		}

		sRet += vecRings[i].getPointsString();
	}
	sRet += ")";
	return std::string();
}
