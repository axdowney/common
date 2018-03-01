#include "SQLDataTypes.h"
void SQLGeometry::updateGeometry()
{
}

SQLPoint::SQLPoint(double x, double y) : dX(x), dY(y)
{
	this->sCore = "POINT(" + std::to_string(dX) + ", " + std::to_string(dY) + ")";
}

double SQLPoint::getX() const
{
	return dX;
}

double SQLPoint::getY() const
{
	return dY;
}

void SQLPoint::setX(double x)
{
	dX = x;
}

void SQLPoint::setY(double y)
{
	dY = y;
}

void SQLPoint::updateGeometry()
{
	sCore = "POINT(" + std::to_string(dX) + ", " + std::to_string(dY) + ")";
}

SQLLineString::SQLLineString(const std::vector<SQLPoint>& vec) : vecPoints(vec)
{
	sCore = getLineString();
}

const std::vector<SQLPoint> &SQLLineString::getPoints() const
{
	return this->vecPoints;
}

std::vector<SQLPoint>& SQLLineString::getPoints()
{
	return this->vecPoints;
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

void SQLLineString::updateGeometry()
{
	for (auto &geom : vecPoints) {
		geom.updateGeometry();
	}

	sCore = getLineString();
}

SQLPolygon::SQLPolygon(const std::vector<SQLLineString>& vec) : vecRings(vec)
{
	sCore = getPolygonString();
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
	std::string sRet = "POLYGON(" + getRingsString() + ")";
	return sRet;
}

std::string SQLPolygon::getRingsString() const
{
	std::string sRet;
	for (size_t i = 0; i < vecRings.size(); ++i) {
		if (i > 0) {
			sRet += ", ";
		}

		sRet += "(" + vecRings[i].getPointsString() + ")";
	}
	return sRet;
}

void SQLPolygon::updateGeometry()
{
	for (auto &geom : vecRings) {
		geom.updateGeometry();
	}

	sCore = getPolygonString();
}

SQLNull::SQLNull()
{
	sCore = "null";
}

SQLMultiPoint::SQLMultiPoint(const std::vector<SQLPoint>& vec) : vecPoints(vec)
{
	sCore = getMultiPointString();
}

const std::vector<SQLPoint>& SQLMultiPoint::getPoints() const
{
	return vecPoints;
}

std::vector<SQLPoint>& SQLMultiPoint::getPoints()
{
	return vecPoints;
}

std::string SQLMultiPoint::getMultiPointString() const
{
	return "MULTIPOINT(" + getPointsString() + ")";
}

std::string SQLMultiPoint::getPointsString() const
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

void SQLMultiPoint::updateGeometry()
{
	for (auto &geom : vecPoints) {
		geom.updateGeometry();
	}

	sCore = getMultiPointString();
}

SQLMultiLineString::SQLMultiLineString(const std::vector<SQLLineString>& vec) : vecLines(vec)
{
	sCore = getMultiLineString();
}

const std::vector<SQLLineString>& SQLMultiLineString::getLines() const
{
	return vecLines;
}

std::vector<SQLLineString>& SQLMultiLineString::getLines()
{
	return vecLines;
}

std::string SQLMultiLineString::getMultiLineString() const
{
	std::string sRet = "MULTILINESTRING(";
	for (size_t i = 0; i < vecLines.size(); ++i) {
		if (i > 0) {
			sRet += ", ";
		}

		sRet += "(" + vecLines[i].getPointsString() + ")";
	}
	sRet += ")";
	return sRet;
}

void SQLMultiLineString::updateGeometry()
{
	for (auto &geom : vecLines) {
		geom.updateGeometry();
	}

	sCore = getMultiLineString();
}

SQLMultiPolygon::SQLMultiPolygon(const std::vector<SQLPolygon>& vec) : vecPolygons(vec)
{
	sCore = getMultiPolygonString();
}

const std::vector<SQLPolygon>& SQLMultiPolygon::getPolygons() const
{
	return vecPolygons;
}

std::vector<SQLPolygon>& SQLMultiPolygon::getPolygons()
{
	return vecPolygons;
}

std::string SQLMultiPolygon::getMultiPolygonString() const
{
	std::string sRet = "MULTIPOLYGON(";
	for (size_t i = 0; i < vecPolygons.size(); ++i) {
		if (i > 0) {
			sRet += ",";
		}

		sRet += "(" + vecPolygons[i].getRingsString() + ")";
	}
	sRet += ")";
	return sRet;
}

void SQLMultiPolygon::updateGeometry()
{
	for (auto &geom : vecPolygons) {
		geom.updateGeometry();
	}

	sCore = getMultiPolygonString();
}

SQLGeometryCollection::SQLGeometryCollection(const std::vector<SQLGeometry>& vec) : vecGeoms(vec)
{
	sCore = getGeometryCollectionString();
}

const std::vector<SQLGeometry>& SQLGeometryCollection::getGeoms() const
{
	return vecGeoms;
}

std::vector<SQLGeometry>& SQLGeometryCollection::getGeoms()
{
	return vecGeoms;
}

std::string SQLGeometryCollection::getGeomsString() const
{
	std::string sRet;
	for (size_t i = 0; i < vecGeoms.size(); ++i) {
		if (i > 0) {
			sRet += ",";
		}

		sRet += vecGeoms[i].getCore();
	}
	return sRet;
}

std::string SQLGeometryCollection::getGeometryCollectionString() const
{
	return "GEOMETRYCOLLECTION(" + getGeomsString() + ")";
}

void SQLGeometryCollection::updateGeometry()
{
	sCore = getGeometryCollectionString();
}

SQLRand::SQLRand()
{
	sCore = "RAND()";
}

SQLRand::SQLRand(const SQLExpression & sqle)
{
	changeSeed(sqle);
}

void SQLRand::changeSeed(const SQLExpression & sqle)
{
	sCore = "RAND(" + sqle.toString() + ")";
}
