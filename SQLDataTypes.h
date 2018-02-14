#pragma once
#ifndef SQLDATATYPES_H
#define SQLDATATYPES_H

#include <initializer_list>

#include "SQLExpression.h"


class SQLDataType : public SQLExpression {

};

class SQLPoint : public SQLDataType {
public:
	SQLPoint(double x = 0, double y = 0);
	double getX() const;
	double getY() const;

protected:
	double dX;
	double dY;
};

class SQLLineString : public SQLDataType {
public:
	SQLLineString(const std::vector<SQLPoint> &vec);
	const std::vector<SQLPoint> &getPoints() const;
	std::vector<SQLPoint> &getPoints();
	std::string getLineString() const;
	std::string getPointsString() const;

protected:
	std::vector<SQLPoint> vecPoints;
};

class SQLPolygon : public SQLDataType {
public:
	SQLPolygon(const std::vector<SQLLineString> &vec);
	const std::vector<SQLLineString> &getRings() const;
	std::vector<SQLLineString> &getRings();
	std::string getPolygonString() const;

protected:
	std::vector<SQLLineString> vecRings;
};
#endif