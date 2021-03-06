#pragma once
#ifndef SQLEXPRESSION_H
#define SQLEXPRESSION_H

#include <list>
#include <string>
#include <vector>
#include "Expression.h"
//#include "SQLTables.h"
class SQLTable;
class SQLExpressionList;
class SQLExpression : public Expression {
public:
	enum Function {
		eFirst = 0,
		eABS = eFirst,
		eACOS,
		eADDDATE,
		eADDTIME,
		eAES_DECRYPT,
		eAES_ENCRYPT,
		eAND,
		eAndOp,
		eANY_VALUE,
		eArea,
		eAsBinary,
		eAsWKB,
		eASCII,
		eASIN,
		eEqual,
		eAssign,
		eAsText,
		eAsWKT,
		eASYMMETRIC_DECRYPT,
		eASYMMETRIC_DERIVE,
		eASYMMETRIC_ENCRYPT,
		eASYMMETRIC_SIGN,
		eASYMMETRIC_VERIFY,
		eATAN,
		eATAN2,
		eAVG,
		eBENCHMARK,
		eBETWEEN,
		eBIN,
		eBINARY,
		eBIT_AND,
		eBIT_COUNT,
		eBIT_LENGTH,
		eBIT_OR,
		eBIT_XOR,
		eBitwiseAnd,
		eBitwiseInvert,
		eBitwiseOr,
		eBitwiseXor,
		eBuffer,
		eCASE,
		eCAST,
		eCEIL,
		eCEILING,
		eCentroid,
		eCHAR,
		eCHAR_LENGTH,
		eCHARACTER_LENGTH,
		eCHARSET,
		eCOALESCE,
		eCOERCIBILITY,
		eCOLLATION,
		eCOMPRESS,
		eCONCAT,
		eCONCAT_WS,
		eCONNECTION_ID,
		eContains,
		eCONV,
		eCONVERT,
		eCONVERT_TZ,
		eConvexHull,
		eCOS,
		eCOT,
		eCOUNT,

		eCRC32,
		eCREATE_ASYMMETRIC_PRIV_KEY,
		eCREATE_ASYMMETRIC_PUB_KEY,
		eCREATE_DH_PARAMETERS,
		eCREATE_DIGEST,
		eCrosses,
		eCURDATE,
		eCURRENT_DATE,
		eCURRENT_TIME,
		eCURRENT_TIMESTAMP,
		eCURRENT_USER,
		eCURTIME,
		eDATABASE,
		eDATE,
		eDATE_ADD,
		eDATE_FORMAT,
		eDATE_SUB,
		eDATEDIFF,
		eDAY,
		eDAYNAME,
		eDAYOFMONTH,
		eDAYOFWEEK,
		eDAYOFYEAR,
		eDECODE,
		eDEFAULT,
		eDEGREES,
		eDES_DECRYPT,
		eDES_ENCRYPT,
		eDimension,
		eDisjoint,
		eDistance,
		eDIV,
		eDivide,
		eELT,
		eENCODE,
		eENCRYPT,
		eEndPoint,
		eEnvelope,

		eEqualNullSafe,
		eEquals,
		eEXP,
		eEXPORT_SET,
		eExteriorRing,
		eEXTRACT,
		eExtractValue,
		eFIELD,
		eFIND_IN_SET,
		eFLOOR,
		eFORMAT,
		eFOUND_ROWS,
		eFROM_BASE64,
		eFROM_DAYS,
		eFROM_UNIXTIME,
		eGeomCollFromText,
		eGeometryCollectionFromText,
		eGeomCollFromWKB,
		eGeometryCollectionFromWKB,
		eGeometryCollection,
		eGeometryN,
		eGeometryType,
		eGeomFromText,
		eGeometryFromText,
		eGeomFromWKB,
		eGeometryFromWKB,
		eGET_FORMAT,
		eGET_LOCK,
		eGLength,
		eGreaterThan,
		eGreaterThanEq,
		eGREATEST,
		eGROUP_CONCAT,
		eGTID_SUBSET,
		eGTID_SUBTRACT,
		eHEX,
		eHOUR,
		eIF,
		eIFNULL,
		eIN,
		eINET_ATON,
		eINET_NTOA,
		eINET6_ATON,
		eINET6_NTOA,
		eINSERT,
		eINSTR,
		eInteriorRingN,
		eIntersects,
		eINTERVAL,
		eIS,
		eIS_FREE_LOCK,
		eIS_IPV4,
		eIS_IPV4_COMPAT,
		eIS_IPV4_MAPPED,
		eIS_IPV6,
		eIS_NOT,
		eIS_NOT_NULL,
		eIS_NULL,
		eIS_USED_LOCK,
		eIsClosed,
		eIsEmpty,
		eISNULL,
		eIsSimple,
		eJSON_APPEND,
		eJSON_ARRAY,
		eJSON_ARRAY_APPEND,
		eJSON_ARRAY_INSERT,
		eJSON_ARRAYAGG,
		eJSON_ExtractOp,
		eJSON_CONTAINS,
		eJSON_CONTAINS_PATH,
		eJSON_DEPTH,
		eJSON_EXTRACT,
		eJSON_UnquoteExtractOp,
		eJSON_INSERT,
		eJSON_KEYS,
		eJSON_LENGTH,
		eJSON_MERGE,
		eJSON_MERGE_PATCH,
		eJSON_MERGE_PRESERVE,
		eJSON_OBJECT,
		eJSON_OBJECTAGG,
		eJSON_PRETTY,
		eJSON_QUOTE,
		eJSON_REMOVE,
		eJSON_REPLACE,
		eJSON_SEARCH,
		eJSON_SET,
		eJSON_STORAGE_SIZE,
		eJSON_TYPE,
		eJSON_UNQUOTE,
		eJSON_VALID,
		eLAST_DAY,
		eLAST_INSERT_ID,
		eLCASE,
		eLEAST,
		eLEFT,
		eLeftShift,
		eLENGTH,
		eLessThan,
		eLessThanEq,
		eLIKE,
		eLineFromText,
		eLineStringFromText,
		eLineFromWKB,
		eLineStringFromWKB,
		eLineString,
		eLN,
		eLOAD_FILE,
		eLOCALTIME,
		eLOCALTIMESTAMP,
		eLOCATE,
		eLOG,
		eLOG10,
		eLOG2,
		eLOWER,
		eLPAD,
		eLTRIM,
		eMAKE_SET,
		eMAKEDATE,
		eMAKETIME,
		eMASTER_POS_WAIT,
		eMATCH,
		eMAX,
		eMBRContains,
		eMBRCoveredBy,
		eMBRCovers,
		eMBRDisjoint,
		eMBREqual,
		eMBREquals,
		eMBRIntersects,
		eMBROverlaps,
		eMBRTouches,
		eMBRWithin,
		eMD5,
		eMICROSECOND,
		eMID,
		eMIN,
		eSubtract,
		eMINUTE,
		eMLineFromText,
		eMultiLineStringFromText,
		eMLineFromWKB,
		eMultiLineStringFromWKB,
		eMOD,

		eMONTH,
		eMONTHNAME,
		eMPointFromText,
		eMultiPointFromText,
		eMPointFromWKB,
		eMultiPointFromWKB,
		eMPolyFromText,
		eMultiPolygonFromText,
		eMPolyFromWKB,
		eMultiPolygonFromWKB,
		eMultiLineString,
		eMultiPoint,
		eMultiPolygon,
		eNAME_CONST,
		eNOT,
		eNotOp,

		eNotEqSQL,
		eNotEq,


		eNOW,
		eNULLIF,
		eNumGeometries,
		eNumInteriorRings,
		eNumPoints,
		eOCT,
		eOCTET_LENGTH,
		eOLD_PASSWORD,
		eOR,
		eOrOp,
		eORD,
		eOverlaps,
		ePASSWORD,
		ePERIOD_ADD,
		ePERIOD_DIFF,
		ePI,
		eadd,
		ePoint,
		ePointFromText,
		ePointFromWKB,
		ePointN,
		ePolyFromText,
		ePolygonFromText,
		ePolyFromWKB,
		ePolygonFromWKB,
		ePolygon,
		ePOSITION,
		ePOW,
		ePOWER,
		ePROCEDURE_ANALYSE,
		eQUARTER,
		eQUOTE,
		eRADIANS,
		eRAND,
		eRANDOM_BYTES,
		eREGEXP,
		eRELEASE_ALL_LOCKS,
		eRELEASE_LOCK,
		eREPEAT,
		eREPLACE,
		eREVERSE,
		eRIGHT,
		eRightShift,
		eRLIKE,
		eROUND,
		eROW_COUNT,
		eRPAD,
		eRTRIM,
		eSCHEMA,
		eSEC_TO_TIME,
		eSECOND,
		eSESSION_USER,
		eSHA1,
		eSHA2,
		eSIGN,
		eSIN,
		eSLEEP,
		eSOUNDEX,
		eSOUNDS_LIKE,
		eSPACE,
		eSQRT,
		eSRID,
		eST_Area,
		eST_AsBinary,
		eST_AsWKB,
		eST_AsGeoJSON,
		eST_AsText,
		eST_AsWKT,
		eST_Buffer,
		eST_Buffer_Strategy,
		eST_Centroid,
		eST_Contains,
		eST_ConvexHull,
		eST_Crosses,
		eST_Difference,
		eST_Dimension,
		eST_Disjoint,
		eST_Distance,
		eST_Distance_Sphere,
		eST_EndPoint,
		eST_Envelope,
		eST_Equals,
		eST_ExteriorRing,
		eST_GeoHash,
		eST_GeomCollFromText,
		eST_GeometryCollectionFromText,
		eST_GeomCollFromTxt,
		eST_GeomCollFromWKB,
		eST_GeometryCollectionFromWKB,
		eST_GeometryN,
		eST_GeometryType,
		eST_GeomFromGeoJSON,
		eST_GeomFromText,
		eST_GeometryFromText,
		eST_GeomFromWKB,
		eST_GeometryFromWKB,
		eST_GLength,
		eST_InteriorRingN,
		eST_Intersection,
		eST_Intersects,
		eST_IsClosed,
		eST_IsEmpty,
		eST_IsSimple,
		eST_IsValid,
		eST_LatFromGeoHash,
		eST_Length,
		eST_LineFromText,
		eST_LineStringFromText,
		eST_LineFromWKB,
		eST_LineStringFromWKB,
		eST_LongFromGeoHash,
		eST_MakeEnvelope,
		eST_MLineFromText,
		eST_MultiLineStringFromText,
		eST_MLineFromWKB,
		eST_MultiLineStringFromWKB,
		eST_MPointFromText,
		eST_MultiPointFromText,
		eST_MPointFromWKB,
		eST_MultiPointFromWKB,
		eST_MPolyFromText,
		eST_MultiPolygonFromText,
		eST_MPolyFromWKB,
		eST_MultiPolygonFromWKB,
		eST_NumGeometries,
		eST_NumInteriorRing,
		eST_NumPoints,
		eST_Overlaps,
		eST_PointFromGeoHash,
		eST_PointFromText,
		eST_PointFromWKB,
		eST_PointN,
		eST_PolyFromText,
		eST_PolygonFromText,
		eST_PolyFromWKB,
		eST_PolygonFromWKB,
		eST_Simplify,
		eST_SRID,
		eST_StartPoint,
		eST_SymDifference,
		eST_Touches,
		eST_Union,
		eST_Validate,
		eST_Within,
		eST_X,
		eST_Y,
		eStartPoint,
		eSTD,
		eSTDDEV,
		eSTDDEV_POP,
		eSTDDEV_SAMP,
		eSTR_TO_DATE,
		eSTRCMP,
		eSUBDATE,
		eSUBSTR,
		eSUBSTRING,
		eSUBSTRING_INDEX,
		eSUBTIME,
		eSUM,
		eSYSDATE,
		eSYSTEM_USER,
		eTAN,
		eTIME,
		eTIME_FORMAT,
		eTIME_TO_SEC,
		eTIMEDIFF,
		eMultiply,
		eTIMESTAMP,
		eTIMESTAMPADD,
		eTIMESTAMPDIFF,
		eTO_BASE64,
		eTO_DAYS,
		eTO_SECONDS,
		eTouches,
		eTRIM,
		eTRUNCATE,
		eUCASE,
		esubtract,
		eUNCOMPRESS,
		eUNCOMPRESSED_LENGTH,
		eUNHEX,
		eUNIX_TIMESTAMP,
		eUpdateXML,
		eUPPER,
		eUSER,
		eUTC_DATE,
		eUTC_TIME,
		eUTC_TIMESTAMP,
		eUUID,
		eUUID_SHORT,
		eVALIDATE_PASSWORD_STRENGTH,
		eVALUES,
		eVAR_POP,
		eVAR_SAMP,
		eVARIANCE,
		eVERSION,
		eWAIT_FOR_EXECUTED_GTID_SET,
		eWAIT_UNTIL_SQL_THREAD_AFTER_GTIDS,
		eWEEK,
		eWEEKDAY,
		eWEEKOFYEAR,
		eWEIGHT_STRING,
		eWithin,
		eX,
		eXOR,
		eY,
		eYEAR,
		eYEARWEEK,

		eLAST
	};
	SQLExpression(const std::string &sVal);
	SQLExpression(const char *pc);
	SQLExpression(double dVal);
	SQLExpression(int iVal);
	SQLExpression(const SQLTable &pt, int iCol);
	SQLExpression(const SQLExpression &sqle);
	SQLExpression(const SQLTable &pt);
	std::string toString() const;
	SQLExpression &openParen(bool bNot);
	SQLExpression &closeParen();
	SQLExpression &enclose();
	static std::string getFunction(SQLExpression::Function e);
	static std::string buildFunctionString(SQLExpression::Function e, const SQLExpressionList &sqleList);
	static std::string buildFunctionString(SQLExpression::Function e, const SQLExpression &sqle, const SQLExpressionList &sqleList);
	SQLExpression &genericFunction(SQLExpression::Function e, const SQLExpressionList &sqleList);
	explicit operator bool() const;
	SQLExpression &singleQuotes();
	SQLExpression &doubleQuotes();
	void sqlFunction(SQLExpression::Function e, const SQLExpressionList &sqleList);
	void sqlFunction(SQLExpression::Function e);

	/* Comparison Operators */
	SQLExpression &equal(const SQLExpression &sqle);
	SQLExpression &equalNullSafe(const SQLExpression &sqle);
	SQLExpression &notEqual(const SQLExpression &sqle);
	SQLExpression &notEqualSQL(const SQLExpression &sqle);
	SQLExpression &lessThanEq(const SQLExpression &sqle);
	SQLExpression &lessThan(const SQLExpression &sqle);
	SQLExpression &greaterThanEq(const SQLExpression &sqle);
	SQLExpression &greaterThan(const SQLExpression &sqle);
	SQLExpression &IS(const SQLExpression &sqle);
	SQLExpression &IS_NOT(const SQLExpression &sqle);
	SQLExpression &IS_NULL();
	SQLExpression &IS_NOT_NULL();
	SQLExpression &BETWEEN(const SQLExpression &sqleMin, const SQLExpression &sqleMax);
	SQLExpression &NOT_BETWEEN(const SQLExpression &sqleMin, const SQLExpression &sqleMax);
	SQLExpression &GREATEST(const SQLExpressionList &sqleList);
	SQLExpression &IN(const SQLExpressionList &sqleList);
	SQLExpression &NOT_IN(const SQLExpressionList &sqleList);
	SQLExpression &ISNULL();
	SQLExpression &COALESCE(const SQLExpressionList &sqleList);
	SQLExpression &INTERVAL(const SQLExpressionList &sqleList);
	SQLExpression &LEAST(const SQLExpressionList &sqleList);
	SQLExpression &LIKE(const SQLExpression &sqle, const SQLExpression &sqleEscape = SQLExpression());
	SQLExpression &NOT_LIKE(const SQLExpression &sqle, const SQLExpression &sqleEscape = SQLExpression());
	SQLExpression &STRCMP(const SQLExpression &sqle);

	/* Arithmetic Operators */
	SQLExpression &DIV(const SQLExpression &sqle);
	SQLExpression &divide(const SQLExpression &sqle);
	SQLExpression &MOD(const SQLExpression &sqle);
	SQLExpression &add(const SQLExpression &sqle);
	SQLExpression &multiply(const SQLExpression &sqle);
	SQLExpression &subtract(const SQLExpression &sqle);

	/* Mathmatical Functions */
	SQLExpression &ABS();
	SQLExpression &ACOS();
	SQLExpression &ASIN();
	SQLExpression &ATAN();
	SQLExpression &ATAN(const SQLExpression &sqleY);
	SQLExpression &ATAN2(const SQLExpression &sqleY);
	SQLExpression &CEIL();
	SQLExpression &CONV(const SQLExpression &sqleFromBase, const SQLExpression &sqleToBase);
	SQLExpression &COS();
	SQLExpression &COT();
	SQLExpression &CRC32();
	SQLExpression &DEGREES();
	SQLExpression &EXP();
	SQLExpression &FLOOR();
	//SQLExpression &FORMAT(const SQLExpression &sqlePrecision);
	SQLExpression &HEX();
	SQLExpression &LN();
	SQLExpression &LOG();
	SQLExpression &LOG(const SQLExpression &sqleBase);
	SQLExpression &LOG2();
	SQLExpression &LOG10();
	SQLExpression &PI();
	SQLExpression &POW(const SQLExpression &sqleY);
	SQLExpression &POWER(const SQLExpression &sqleY);
	SQLExpression &RADIANS();
	SQLExpression &RAND();
	SQLExpression &RAND(const SQLExpression &sqleSeed);
	SQLExpression &ROUND();
	SQLExpression &ROUND(const SQLExpression &sqlePrecision);
	SQLExpression &SIGN();
	SQLExpression &SIN();
	SQLExpression &SQRT();
	SQLExpression &TAN();
	SQLExpression &TRUNCATE(const SQLExpression &sqlePrecision);

	/* String Functions */
	SQLExpression &ASCII();
	SQLExpression &BIN();
	SQLExpression &BIT_LENGTH();
	SQLExpression &CHAR(const SQLExpression &sqleCharSet);
	SQLExpression &CHAR_LENGTH();
	SQLExpression &CHARACTER_LENGTH();
	SQLExpression &CONCAT(const SQLExpression &sqleRight);
	SQLExpression &CONCAT(const SQLExpressionList &sqleRight);
	SQLExpression &CONCAT_WS(const SQLExpression &sqleSeparator, const SQLExpression &sqleRight);
	SQLExpression &CONCAT_WS(const SQLExpression &sqleSeparator, const SQLExpressionList &sqleRight);
	SQLExpression &ELT(const SQLExpressionList &sqleList);
	SQLExpression &EXPORT_SET(const SQLExpression &sqleON, const SQLExpression &sqleOFF,
		const SQLExpression &sqleSep = SQLExpression(), const SQLExpression &sqleBitNum = SQLExpression());
	SQLExpression &FIELD(const SQLExpressionList &sqleList);
	SQLExpression &FIND_IN_SET(const SQLExpressionList &sqleList);
	SQLExpression &FORMAT(const SQLExpression &sqlePrecision, const SQLExpression &sqleLocal = SQLExpression());
	SQLExpression &FROM_BASE64();
	SQLExpression &INSERT(const SQLExpression &sqlePos, const SQLExpression &sqleLen, const SQLExpression &sqleNewStr);
	SQLExpression &INSTR(const SQLExpression &sqleSubStr);
	SQLExpression &LCASE();
	SQLExpression &LEFT(const SQLExpression &sqleLen);
	SQLExpression &LENGTH();
	SQLExpression &LOAD_FILE();
	SQLExpression &LOCATE(const SQLExpression &sqleStr, const SQLExpression &sqlePos = SQLExpression());
	SQLExpression &LOWER();
	SQLExpression &LPAD(const SQLExpression &sqleLen, const SQLExpression &sqlePadStr);
	SQLExpression &LTRIM();
	SQLExpression &MAKE_SET(const SQLExpressionList &sqleList);
	SQLExpression &MID(const SQLExpression &sqlePos, const SQLExpression &sqleLen);
	SQLExpression &OCT();
	SQLExpression &OCTET_LENGTH();
	SQLExpression &ORD();
	SQLExpression &POSITION_IN(const SQLExpression &sqleStr);
	SQLExpression &QUOTE();
	SQLExpression &REPEAT(const SQLExpression &sqleCount);
	SQLExpression &REPLACE(const SQLExpression &sqleFromStr, const SQLExpression &sqleToStr);
	SQLExpression &REVERSE();
	SQLExpression &RIGHT(const SQLExpression &sqleLen);
	SQLExpression &RPAD(const SQLExpression &sqleLen, const SQLExpression &sqlePadStr);
	SQLExpression &RTRIM();
	SQLExpression &SOUNDEX();
	SQLExpression &SOUNDS_LIKE(const SQLExpression &sqleStr);
	SQLExpression &SPACE();
	SQLExpression &SUBSTR(const SQLExpression &sqlePos, const SQLExpression &sqleLen = SQLExpression());
	SQLExpression &SUBSTR_FROM_FOR(const SQLExpression &sqlePos, const SQLExpression &sqleLen = SQLExpression());
	SQLExpression &SUBSTRING_INDEX(const SQLExpression &sqleDelim, const SQLExpression &sqleCount);
	SQLExpression &TO_BASE64();
	enum TrimDir {
		eNONE = 0,
		eBOTH,
		eLEADING,
		eTRAILING,
	};
	SQLExpression &TRIM(TrimDir e = eNONE, const SQLExpression &sqleRemStr = SQLExpression());
	SQLExpression &UCASE();
	SQLExpression &UNHEX();
	SQLExpression &UPPER();
	enum WeightStringDir {
		eDirASC = 0x001,
		eDirDESC = 0x010,
		eDirREVERSE = 0x100
	};
	SQLExpression &WEIGHT_STRING(const std::vector<int> &vecLevel = std::vector<int>(), const std::vector<WeightStringDir> &vecDir = std::vector<WeightStringDir>());
	SQLExpression &WEIGHT_STRING_AS_CHAR(const SQLExpression &sqleNum,
		const std::vector<int> &vecLevel = std::vector<int>(), const std::vector<WeightStringDir> &vecDir = std::vector<WeightStringDir>());
	SQLExpression &WEIGHT_STRING_AS_BINARY(const SQLExpression &sqleNum,
		const std::vector<int> &vecLevel = std::vector<int>(), const std::vector<WeightStringDir> &vecDir = std::vector<WeightStringDir>());

	/* Date and Time Functions */
	enum TimeUnit {
		tuMICROSECOND,
		tuSECOND,
		tuMINUTE,
		tuHOUR,
		tuDAY,
		tuWEEK,
		tuMONTH,
		tuQUARTER,
		tuYEAR,
		tuSECOND_MICROSECOND,
		tuMINUTE_MICROSECOND,
		tuMINUTE_SECOND,
		tuHOUR_MICROSECOND,
		tuHOUR_SECOND,
		tuHOUR_MINUTE,
		tuDAY_MICROSECOND,
		tuDAY_SECOND,
		tuDAY_MINUTE,
		tuDAY_HOUR,
		tuYEAR_MONTH,
	};
	std::string getTimeUnit(TimeUnit e);
	SQLExpression &ADDDATE(const SQLExpression &sqle, TimeUnit e = TimeUnit::tuDAY);
	SQLExpression &ADDTIME(const SQLExpression &sqle);
	SQLExpression &CONVERT_TZ(const SQLExpression &sqleFromTZ, const SQLExpression &sqleToTZ);
	SQLExpression &CURDATE();
	SQLExpression &CURRENT_DATE();
	SQLExpression &CURRENT_TIME(const SQLExpression &sqleFSP = SQLExpression());
	SQLExpression &CURRENT_TIMESTAMP(const SQLExpression &sqleFSP = SQLExpression());
	SQLExpression &CURTIME(const SQLExpression &sqleFSP = SQLExpression());
	SQLExpression &DATE();
	SQLExpression &DATEDIFF(const SQLExpression &sqle);
	SQLExpression &DATE_ADD(const SQLExpression &sqle, TimeUnit e);
	SQLExpression &DATE_FORMAT(const SQLExpression &sqleFormat);
	SQLExpression &DATE_SUB(const SQLExpression &sqle, TimeUnit e);
	SQLExpression &DAY();
	SQLExpression &DAYNAME();
	SQLExpression &DAYOFMONTH();
	SQLExpression &DAYOFWEEK();
	SQLExpression &DAYOFYEAR();
	SQLExpression &EXTRACT(TimeUnit e);
	SQLExpression &FROM_DAYS();
	SQLExpression &FROM_UNIXTIME();
	SQLExpression &GET_FORMAT(Function e);
	SQLExpression &HOUR();
	SQLExpression &LAST_DAY();
	SQLExpression &LOCALTIME(const SQLExpression &sqleFSP = SQLExpression());
	SQLExpression &LOCALTIMESTAMP(const SQLExpression &sqleFSP = SQLExpression());
	SQLExpression &MAKEDATE(const SQLExpression &sqleDayOfYear);
	SQLExpression &MAKETIME(const SQLExpression &sqleMinute, const SQLExpression &sqleSecond);
	SQLExpression &MICROSECOND();
	SQLExpression &MINUTE();
	SQLExpression &MONTH();
	SQLExpression &MONTHNAME();
	SQLExpression &NOW(const SQLExpression &sqleFSP = SQLExpression());
	SQLExpression &PERIOD_ADD(const SQLExpression &sqle);
	SQLExpression &PERIOD_DIFF(const SQLExpression &sqle);
	SQLExpression &QUARTER();
	SQLExpression &SECOND();
	SQLExpression &SEC_TO_TIME();
	SQLExpression &STR_TO_DATE();
	SQLExpression &SUBDATE(const SQLExpression &sqle, TimeUnit e = TimeUnit::tuDAY);
	SQLExpression &SUBTIME(const SQLExpression &sqle);
	SQLExpression &SYSDATE(const SQLExpression &sqleFSP = SQLExpression());
	SQLExpression &TIME();
	SQLExpression &TIMEDIFF(const SQLExpression &sqle);
	SQLExpression &TIMESTAMP(const SQLExpression &sqle = SQLExpression());
	SQLExpression &TIMESTAMPADD(TimeUnit e, const SQLExpression &sqleInterval);
	SQLExpression &TIMESTAMPDIFF(TimeUnit e, const SQLExpression &sqle);
	SQLExpression &TIME_FORMAT(const SQLExpression &sqle);
	SQLExpression &TIME_TO_SEC();
	SQLExpression &TO_DAYS();
	SQLExpression &TO_SECONDS();
	SQLExpression &UNIX_TIMESTAMP(const SQLExpression &sqle = SQLExpression());
	SQLExpression &UTC_DATE();
	SQLExpression &UTC_TIME(const SQLExpression &sqleFSP = SQLExpression());
	SQLExpression &UTC_TIMESTAMP(const SQLExpression &sqleFSP = SQLExpression());
	SQLExpression &WEEK(const SQLExpression &sqleMode = SQLExpression());
	SQLExpression &WEEKDAY();
	SQLExpression &WEEKOFYEAR();
	SQLExpression &YEAR();
	SQLExpression &YEARWEEK();

	/* XML Functions */
	SQLExpression &EXTRACTVALUE(const SQLExpression &sqle);
	SQLExpression &UPDATEXML(const SQLExpression &sqle);

	/* Bitwise Functions */
	SQLExpression &BIT_COUNT();
	SQLExpression &BitwiseAnd(const SQLExpression &sqle);
	SQLExpression &BitwiseInvert();
	SQLExpression &BitwiseOr(const SQLExpression &sqle);
	SQLExpression &BitwiseXor(const SQLExpression &sqle);
	SQLExpression &LeftShift(const SQLExpression &sqle);
	SQLExpression &RightShift(const SQLExpression &sqle);

	/* Encryption and Compression Function */
	SQLExpression &AES_DECRYPT(const SQLExpression &sqleKey, const SQLExpression &sqleInitVec = SQLExpression());
	SQLExpression &AES_ENCRYPT(const SQLExpression &sqleKey, const SQLExpression &sqleInitVec = SQLExpression());
	SQLExpression &COMPRESS();
	SQLExpression &DECODE(const SQLExpression &sqlePass);
	SQLExpression &DES_DECRYPT(const SQLExpression &sqleKey = SQLExpression());
	SQLExpression &DES_ENCRYPT(const SQLExpression &sqleKey = SQLExpression());
	SQLExpression &ENCODE(const SQLExpression &sqlePass);
	SQLExpression &ENCRYPT(const SQLExpression &sqleSalt);
	SQLExpression &MD5();
	SQLExpression &OLD_PASSWORD();
	SQLExpression &PASSWORD();
	SQLExpression &RANDOM_BYTES();
	SQLExpression &SHA1();
	SQLExpression &SHA2(const SQLExpression &sqleHashLen);
	SQLExpression &UNCOMPRESS();
	SQLExpression &VALIDATE_PASSWORD_STRENGTH();

	/* Information Functions */
	SQLExpression &BENCHMARK(const SQLExpression &sqleCount);
	SQLExpression &CHARSET();
	SQLExpression &COERCIBILITY();
	SQLExpression &COLLATION();
	SQLExpression &CONNECTION_ID();
	SQLExpression &CURRENT_USER();
	SQLExpression &DATABASE();
	SQLExpression &FOUND_ROWS();
	SQLExpression &LAST_INSERT_ID(const SQLExpression &sqle = SQLExpression());
	SQLExpression &ROW_COUNT();
	SQLExpression &SCHEMA();
	SQLExpression &SESSION_USER();
	SQLExpression &SYSTEM_USER();
	SQLExpression &USER();
	SQLExpression &VERSION();

	/* JSON Functions */
	SQLExpression &JSON_ARRAY(const SQLExpressionList &sqleList);
	SQLExpression &JSON_OBJECT(const SQLExpressionList &sqleList);
	SQLExpression &JSON_QUOTE();
	SQLExpression &JSON_CONTAINS(const SQLExpression &sqleCandidate, const SQLExpression &sqlePath = SQLExpression());
	SQLExpression &JSON_EXTRACT(const SQLExpressionList &sqleList);
	SQLExpression &JSON_ExtractOp(const SQLExpression &sqle);
	SQLExpression &JSON_UnquoteExtractOp(const SQLExpression &sqle);
	SQLExpression &JSON_KEYS(const SQLExpression &sqlePath = SQLExpression());
	SQLExpression &JSON_SEARCH(const SQLExpression &sqleOneAll, const SQLExpression &sqlePath = SQLExpression());
	SQLExpression &JSON_APPEND(const SQLExpressionList &sqlelPathValPairs);
	SQLExpression &JSON_ARRAY_APPEND(const SQLExpressionList &sqlelPathValPairs);
	SQLExpression &JSON_ARRAY_INSERT(const SQLExpressionList &sqlelPathValPairs);
	SQLExpression &JSON_INSERT(const SQLExpressionList &sqlelPathValPairs);
	SQLExpression &JSON_MERGE(const SQLExpressionList &sqleDocs);
	SQLExpression &JSON_MERGE_PATCH(const SQLExpressionList &sqleDocs);
	SQLExpression &JSON_MERGE_PRESERVE(const SQLExpressionList &sqleDocs);
	SQLExpression &JSON_REMOVE(const SQLExpressionList &sqleDocs);
	SQLExpression &JSON_REPLACE(const SQLExpressionList &sqlelPathValPairs);
	SQLExpression &JSON_SET(const SQLExpressionList &sqlelPathValPairs);
	SQLExpression &JSON_UNQUOTE();
	SQLExpression &JSON_DEPTH();
	SQLExpression &JSON_LENGTH(const SQLExpression &sqlePath = SQLExpression());
	SQLExpression &JSON_TYPE();
	SQLExpression &JSON_VALID();
	SQLExpression &JSON_PRETTY();
	SQLExpression &JSON_STORAGE_SIZE();

	/* Global Transaction ID Functions */
	SQLExpression &GTID_SET(const SQLExpression &sqleSubSet);
	SQLExpression &GTID_SUBSET(const SQLExpression &sqleSet);
	SQLExpression &GTID_SUBTRACT(const SQLExpression &sqleSubSet);
	SQLExpression &WAIT_FOR_EXECUTED_GTID_SET(const SQLExpression &sqleTimeout = SQLExpression());
	SQLExpression &WAIT_UNTIL_SQL_THREAD_AFTER_GTIDS(const SQLExpression &sqleTimeout = SQLExpression(), const SQLExpression &sqleChannel = SQLExpression());

	/* Spatial Analysis Functions */
	SQLExpression &ST_GeomCollFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &ST_GeometryCollectionFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &ST_GeomCollFromTxt(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &GeomCollFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &GeometryCollectionFromText(const SQLExpression &sqleSrid = SQLExpression());

	SQLExpression &ST_GeomFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &ST_GeometryFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &GeomFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &GeometryFromText(const SQLExpression &sqleSrid = SQLExpression());

	SQLExpression &ST_LineFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &ST_LineStringFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &LineFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &LineStringFromText(const SQLExpression &sqleSrid = SQLExpression());

	SQLExpression &ST_MLineFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &ST_MultiLineStringFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &MLineFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &MultiLineStringFromText(const SQLExpression &sqleSrid = SQLExpression());

	SQLExpression &ST_MPointFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &ST_MultiPointFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &MPointFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &MultiPointFromText(const SQLExpression &sqleSrid = SQLExpression());

	SQLExpression &ST_MPolyFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &ST_MultiPolygonFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &MPolyFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &MultiPolygonFromText(const SQLExpression &sqleSrid = SQLExpression());

	SQLExpression &ST_PointFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &PointFromText(const SQLExpression &sqleSrid = SQLExpression());

	SQLExpression &ST_PolyFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &ST_PolygonFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &PolyFromText(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &PolygonFromText(const SQLExpression &sqleSrid = SQLExpression());

	SQLExpression &ST_GeomCollFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &ST_GeometryCollectionFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &GeomCollFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &GeometryCollectionFromWKB(const SQLExpression &sqleSrid = SQLExpression());

	SQLExpression &ST_GeomFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &ST_GeometryFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &GeomFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &GeometryFromWKB(const SQLExpression &sqleSrid = SQLExpression());

	SQLExpression &ST_LineFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &ST_LineStringFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &LineFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &LineStringFromWKB(const SQLExpression &sqleSrid = SQLExpression());

	SQLExpression &ST_MLineFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &ST_MultiLineStringFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &MLineFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &MultiLineStringFromWKB(const SQLExpression &sqleSrid = SQLExpression());

	SQLExpression &ST_MPointFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &ST_MultiPointFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &MPointFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &MultiPointFromWKB(const SQLExpression &sqleSrid = SQLExpression());

	SQLExpression &ST_MPolyFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &ST_MultiPolygonFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &MPolyFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &MultiPolygonFromWKB(const SQLExpression &sqleSrid = SQLExpression());

	SQLExpression &ST_PointFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &PointFromWKB(const SQLExpression &sqleSrid = SQLExpression());

	SQLExpression &ST_PolyFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &ST_PolygonFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &PolyFromWKB(const SQLExpression &sqleSrid = SQLExpression());
	SQLExpression &PolygonFromWKB(const SQLExpression &sqleSrid = SQLExpression());

	SQLExpression &GeometryCollection(const SQLExpressionList &sqlelGeoms);
	SQLExpression &LineString(const SQLExpressionList &sqlelPoints);
	SQLExpression &MultiLineString(const SQLExpressionList &sqlelLines);
	SQLExpression &MultiPoint(const SQLExpressionList &sqlelPoints);
	SQLExpression &MultiPolygon(const SQLExpressionList &sqlelPolygons);
	SQLExpression &Point(const SQLExpression &sqleY);
	SQLExpression &Polygon(const SQLExpressionList &sqlelLines);

	SQLExpression &ST_AsBinary();
	SQLExpression &ST_AsWKB();
	SQLExpression &AsBinary();
	SQLExpression &AsWKB();

	SQLExpression &ST_AsText();
	SQLExpression &ST_AsWKT();
	SQLExpression &AsText();
	SQLExpression &AsWKT();

	SQLExpression &Dimension();
	SQLExpression &ST_Dimension();
	
	SQLExpression &Envelope();
	SQLExpression &ST_Envelope();

	SQLExpression &GeometryType();
	SQLExpression &ST_GeometryType();

	SQLExpression &IsEmpty();
	SQLExpression &ST_IsEmpty();

	SQLExpression &IsSimple();
	SQLExpression &ST_IsSimple();

	SQLExpression &SRID();
	SQLExpression &ST_SRID();

	SQLExpression &ST_Y();
	SQLExpression &Y();

	SQLExpression &ST_X();
	SQLExpression &X();

	SQLExpression &ST_StartPoint();
	SQLExpression &StartPoint();

	SQLExpression &ST_EndPoint();
	SQLExpression &EndPoint();

	SQLExpression &ST_Length();
	SQLExpression &ST_GLength();
	SQLExpression &GLength();

	SQLExpression &ST_IsClosed();
	SQLExpression &IsClosed();

	SQLExpression &ST_NumPoints();
	SQLExpression &NumPoints();

	SQLExpression &ST_PointN(SQLExpression &sqleN);
	SQLExpression &PointN(SQLExpression &sqleN);

	SQLExpression &ST_Area();
	SQLExpression &Area();

	SQLExpression &ST_Centroid();
	SQLExpression &Centroid();

	SQLExpression &ST_ExteriorRing();
	SQLExpression &ExteriorRing();

	SQLExpression &ST_InteriorRingN(const SQLExpression &sqleN);
	SQLExpression &InteriorRingN(const SQLExpression &sqleN);

	SQLExpression &ST_NumInteriorRings();
	SQLExpression &NumInteriorRings();

	SQLExpression &ST_GeometryN(const SQLExpression &sqleN);
	SQLExpression &GeometryN(const SQLExpression &sqleN);

	SQLExpression &ST_NumGeometries();
	SQLExpression &NumGeometries();
	
	SQLExpression &ST_Buffer(const SQLExpression &sqleD, const SQLExpressionList &sqlelStrategies);
	SQLExpression &Buffer(const SQLExpression &sqleD, const SQLExpressionList &sqlelStrategies);

	SQLExpression &ST_ConvexHull();
	SQLExpression &ConvexHull();

	SQLExpression &ST_Buffer_Strategy(const SQLExpression &sqlePoints = SQLExpression());
	SQLExpression &ST_Difference(const SQLExpression &sqleG2);
	SQLExpression &ST_Intersection(const SQLExpression &sqleG2);
	SQLExpression &ST_SymDifference(const SQLExpression &sqleG2);
	SQLExpression &ST_Union(const SQLExpression &sqleG2);

	/* Spatial Relation Functions That Use Object Shapes */
	SQLExpression &ST_Crosses(const SQLExpression &sqleG2);
	SQLExpression &Crosses(const SQLExpression &sqleG2);

	SQLExpression &ST_Distance(const SQLExpression &sqleG2);
	SQLExpression &Distance(const SQLExpression &sqleG2);

	SQLExpression &ST_Contains(const SQLExpression &sqleG2);
	SQLExpression &Contains(const SQLExpression &sqleG2);

	SQLExpression &ST_Disjoint(const SQLExpression &sqleG2);
	SQLExpression &Disjoint(const SQLExpression &sqleG2);

	SQLExpression &ST_Equals(const SQLExpression &sqleG2);
	SQLExpression &Equals(const SQLExpression &sqleG2);

	SQLExpression &ST_Intersects(const SQLExpression &sqleG2);
	SQLExpression &Intersects(const SQLExpression &sqleG2);

	SQLExpression &ST_Overlaps(const SQLExpression &sqleG2);
	SQLExpression &Overlaps(const SQLExpression &sqleG2);

	SQLExpression &ST_Within(const SQLExpression &sqleG2);
	SQLExpression &Within(const SQLExpression &sqleG2);

	SQLExpression &ST_Touches(const SQLExpression &sqleG2);
	SQLExpression &Touches(const SQLExpression &sqleG2);

	/* Spatial Relation Functions That Use Minimum Bounding Rectangles */
	SQLExpression &MBRContains(const SQLExpression &sqleG2);
	SQLExpression &MBRCoveredBy(const SQLExpression &sqleG2);
	SQLExpression &MBRCovers(const SQLExpression &sqleG2);
	SQLExpression &MBRDisjoint(const SQLExpression &sqleG2);
	SQLExpression &MBREqual(const SQLExpression &sqleG2);
	SQLExpression &MBREquals(const SQLExpression &sqleG2);
	SQLExpression &MBRIntersects(const SQLExpression &sqleG2);
	SQLExpression &MBROverlaps(const SQLExpression &sqleG2);
	SQLExpression &MBRTouches(const SQLExpression &sqleG2);
	SQLExpression &MBRWithin(const SQLExpression &sqleG2);

	/* Spatial Geohash Functions */
	SQLExpression &ST_GeoHash(const SQLExpressionList &sqlel);
	SQLExpression &ST_LatFromGeoHash();
	SQLExpression &ST_LongFromGeoHash();
	SQLExpression &ST_PointFromGeoHash(const SQLExpression &sqle);

	/* Spatial GeoJSON Functions */
	SQLExpression &ST_AsGeoJSON(const SQLExpressionList &sqlel);
	SQLExpression &ST_GeomFromGeoJSON(const SQLExpressionList &sqlel);

	/* Spatial Convenience Functions */
	SQLExpression &ST_Distance_Sphere(const SQLExpressionList &sqlel);
	SQLExpression &ST_IsValid();
	SQLExpression &ST_MakeEnvelope(const SQLExpression &sqle);
	SQLExpression &ST_Simplify(const SQLExpression &sqleMaxDistance);
	SQLExpression &ST_Validate();



	/* Miscellaneous Functions */
	SQLExpression &ANY_VALUE();
	SQLExpression &DEFAULT();
	SQLExpression &GET_LOCK(const SQLExpression &sqleTimeout);
	SQLExpression &INET_ATON();
	SQLExpression &INET_NTOA();
	SQLExpression &INET6_ATON();
	SQLExpression &INET6_NTOA();
	SQLExpression &IS_FREE_LOCK();
	SQLExpression &IS_IPV4();
	SQLExpression &IS_IPV4_COMPAT();
	SQLExpression &IS_IPV4_MAPPED();
	SQLExpression &IS_IPV6();
	SQLExpression &IS_USED_LOCK();
	SQLExpression &MASTER_POS_WAIT(const SQLExpression &sqlePos, const SQLExpression &sqleTimeout = SQLExpression(), const SQLExpression &sqleChannel = SQLExpression());
	SQLExpression &NAME_CONST(const SQLExpression &sqleValue);
	SQLExpression &RELEASE_ALL_LOCKS();
	SQLExpression &RELEASE_LOCK();
	SQLExpression &SLEEP();
	SQLExpression &UUID();
	SQLExpression &UUID_SHORT();
	SQLExpression &VALUES(const SQLExpressionList &sqlel);



public:
	SQLExpression() {};
protected:
};

class SQLExpressionList : public std::list<SQLExpression>, public SQLExpression {
public:
	SQLExpressionList(std::initializer_list<SQLExpression> il) : std::list<SQLExpression>(il) { updateString(); }
	//SQLExpressionList(const SQLExpression &sqle);
	//SQLExpressionList(const SQLExpression sqleArray[], int i);
	SQLExpressionList(SQLExpression arg[], size_t size);
	SQLExpressionList &updateString();
	std::string getListString(bool bIncludeEmpty = false) const;
	int removeEmptyExpressions();

	SQLExpression &ELT(const SQLExpression &sqleIndex);
	using SQLExpression::ELT;
	SQLExpression &FIELD(const SQLExpression &sqle);

	friend SQLExpression;
protected:
	SQLExpressionList();

};

inline SQLExpression & SQLExpression::JSON_ARRAY(const SQLExpressionList & sqleList = SQLExpressionList())
{
	sqlFunction(eJSON_ARRAY, sqleList);
	return *this;
}

inline SQLExpression & SQLExpression::JSON_OBJECT(const SQLExpressionList & sqleList = SQLExpressionList())
{
	sqlFunction(eJSON_OBJECT, sqleList);
	return *this;
}


inline SQLExpression & SQLExpression::JSON_EXTRACT(const SQLExpressionList & sqleList = SQLExpressionList())
{
	sqlFunction(eJSON_EXTRACT, sqleList);
	return *this;
}
#endif