#pragma once
#ifndef SQLDATATYPES_H
#define SQLDATATYPES_H

#include <initializer_list>

#include "SQLExpression.h"


class SQLDataType : public SQLExpression {
};

class SQLNull : public SQLDataType {
public:
	SQLNull();
};

class SQLRand : public SQLDataType {
public:
	SQLRand();
	SQLRand(const SQLExpression &sqle);
	void changeSeed(const SQLExpression &sqle = SQLExpression());
};

class SQLGeometry : public SQLDataType {
public:
	virtual void updateGeometry();
};

class SQLPoint : public SQLGeometry {
public:
	SQLPoint(double x = 0, double y = 0);
	double getX() const;
	double getY() const;
	void setX(double x);
	void setY(double y);
	virtual void updateGeometry();

protected:
	double dX;
	double dY;
};

class SQLLineString : public SQLGeometry {
public:
	SQLLineString(const std::vector<SQLPoint> &vec);
	const std::vector<SQLPoint> &getPoints() const;
	std::vector<SQLPoint> &getPoints();
	std::string getLineString() const;
	std::string getPointsString() const;
	virtual void updateGeometry();

protected:
	std::vector<SQLPoint> vecPoints;
};

class SQLPolygon : public SQLGeometry {
public:
	SQLPolygon(const std::vector<SQLLineString> &vec);
	const std::vector<SQLLineString> &getRings() const;
	std::vector<SQLLineString> &getRings();
	std::string getPolygonString() const;
	std::string getRingsString() const;
	virtual void updateGeometry();

protected:
	std::vector<SQLLineString> vecRings;
};

class SQLMultiPoint : public SQLGeometry {
public:
	SQLMultiPoint(const std::vector<SQLPoint> &vec);
	const std::vector<SQLPoint> &getPoints() const;
	std::vector<SQLPoint> &getPoints();
	std::string getMultiPointString() const;
	std::string getPointsString() const;
	virtual void updateGeometry();

protected:
	std::vector<SQLPoint> vecPoints;
};

class SQLMultiLineString : public SQLGeometry {
public:
	SQLMultiLineString(const std::vector<SQLLineString> &vec);
	const std::vector<SQLLineString> &getLines() const;
	std::vector<SQLLineString> &getLines();
	std::string getMultiLineString() const;
	virtual void updateGeometry();

protected:
	std::vector<SQLLineString> vecLines;
};

class SQLMultiPolygon : public SQLGeometry {
public:
	SQLMultiPolygon(const std::vector<SQLPolygon> &vec);
	const std::vector<SQLPolygon> &getPolygons() const;
	std::vector<SQLPolygon> &getPolygons();
	std::string getMultiPolygonString() const;
	virtual void updateGeometry();

protected:
	std::vector<SQLPolygon> vecPolygons;
};

class SQLGeometryCollection : public SQLGeometry {
public:
	SQLGeometryCollection(const std::vector<SQLGeometry> &vec);
	const std::vector<SQLGeometry> &getGeoms() const;
	std::vector<SQLGeometry> &getGeoms();
	std::string getGeomsString() const;
	std::string getGeometryCollectionString() const;
	virtual void updateGeometry();

protected:
	std::vector<SQLGeometry> vecGeoms;
};
#endif