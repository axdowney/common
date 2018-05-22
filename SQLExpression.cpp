#include "SQLExpression.h"
#include "SQLTable.h"

SQLExpression::SQLExpression(const std::string & sVal) : Expression(SQLTable().quote(sVal))
{
}

SQLExpression::SQLExpression(const char * pc) : SQLExpression(pc ? std::string(pc) : std::string())
{
}

SQLExpression::SQLExpression(double dVal) : Expression(dVal)
{
}

SQLExpression::SQLExpression(int iVal) : Expression(iVal)
{
}

SQLExpression::SQLExpression(const SQLTable & pt, int iCol) {
	sCore = pt.getColumnName(iCol);
}

SQLExpression::SQLExpression(const SQLExpression & sqle)
{
	if (!sqle) {
		sCore = "''";
	}
	else {
		sCore = sqle.sCore;
		sLeft = sqle.sLeft;
		sRight = sqle.sRight;
	}
}

SQLExpression::SQLExpression(const SQLTable & pt) : Expression(pt.getSelectQuery())
{
}

std::string SQLExpression::toString() const
{
	return Expression::toString();
}

SQLExpression & SQLExpression::openParen(bool bNot)
{
	
	return *this;
}

SQLExpression & SQLExpression::closeParen()
{
	
	return *this;
}

SQLExpression & SQLExpression::enclose()
{
	surround("(", ")");
	return *this;
}

std::string SQLExpression::getFunction(SQLExpression::Function e)
{
	std::string sRet;
	switch (e) {
	case SQLExpression::eABS:
		sRet = "ABS";
		break;
	case SQLExpression::eACOS:
		sRet = "ACOS";
		break;
	case SQLExpression::eADDDATE:
		sRet = "ADDDATE";
		break;
	case SQLExpression::eADDTIME:
		sRet = "ADDTIME";
		break;
	case SQLExpression::eAES_DECRYPT:
		sRet = "AES_DECRYPT";
		break;
	case SQLExpression::eAES_ENCRYPT:
		sRet = "AES_ENCRYPT";
		break;
	case SQLExpression::eAND:
		sRet = "AND";
		break;
	case SQLExpression::eAndOp:
		sRet = "&&";
		break;
	case SQLExpression::eANY_VALUE:
		sRet = "ANY_VALUE";
		break;
	case SQLExpression::eArea:
		sRet = "Area";
		break;
	case SQLExpression::eAsBinary:
		sRet = "AsBinary";
		break;
	case SQLExpression::eAsWKB:
		sRet = "AsWKB";
		break;
	case SQLExpression::eASCII:
		sRet = "ASCII";
		break;
	case SQLExpression::eASIN:
		sRet = "ASIN";
		break;
	case SQLExpression::eEqual:
		sRet = "=";
		break;
	case SQLExpression::eAssign:
		sRet = ":=";
		break;
	case SQLExpression::eAsText:
		sRet = "AsText";
		break;
	case SQLExpression::eAsWKT:
		sRet = "AsWKT";
		break;
	case SQLExpression::eASYMMETRIC_DECRYPT:
		sRet = "ASYMMETRIC_DECRYPT";
		break;
	case SQLExpression::eASYMMETRIC_DERIVE:
		sRet = "ASYMMETRIC_DERIVE";
		break;
	case SQLExpression::eASYMMETRIC_ENCRYPT:
		sRet = "ASYMMETRIC_ENCRYPT";
		break;
	case SQLExpression::eASYMMETRIC_SIGN:
		sRet = "ASYMMETRIC_SIGN";
		break;
	case SQLExpression::eASYMMETRIC_VERIFY:
		sRet = "ASYMMETRIC_VERIFY";
		break;
	case SQLExpression::eATAN:
		sRet = "ATAN";
		break;
	case SQLExpression::eATAN2:
		sRet = "ATAN2";
		break;
	case SQLExpression::eAVG:
		sRet = "AVG";
		break;
	case SQLExpression::eBENCHMARK:
		sRet = "BENCHMARK";
		break;
	case SQLExpression::eBETWEEN:
		sRet = "BETWEEN";
		break;
	case SQLExpression::eBIN:
		sRet = "BIN";
		break;
	case SQLExpression::eBINARY:
		sRet = "BINARY";
		break;
	case SQLExpression::eBIT_AND:
		sRet = "BIT_AND";
		break;
	case SQLExpression::eBIT_COUNT:
		sRet = "BIT_COUNT";
		break;
	case SQLExpression::eBIT_LENGTH:
		sRet = "BIT_LENGTH";
		break;
	case SQLExpression::eBIT_OR:
		sRet = "BIT_OR";
		break;
	case SQLExpression::eBIT_XOR:
		sRet = "BIT_XOR";
		break;
	case SQLExpression::eBitwiseAnd:
		sRet = "&";
		break;
	case SQLExpression::eBitwiseInvert:
		sRet = "~";
		break;
	case SQLExpression::eBitwiseOr:
		sRet = "|";
		break;
	case SQLExpression::eBitwiseXor:
		sRet = "^";
		break;
	case SQLExpression::eBuffer:
		sRet = "Buffer";
		break;
	case SQLExpression::eCASE:
		sRet = "CASE";
		break;
	case SQLExpression::eCAST:
		sRet = "CAST";
		break;
	case SQLExpression::eCEIL:
		sRet = "CEIL";
		break;
	case SQLExpression::eCEILING:
		sRet = "CEILING";
		break;
	case SQLExpression::eCentroid:
		sRet = "Centroid";
		break;
	case SQLExpression::eCHAR:
		sRet = "CHAR";
		break;
	case SQLExpression::eCHAR_LENGTH:
		sRet = "CHAR_LENGTH";
		break;
	case SQLExpression::eCHARACTER_LENGTH:
		sRet = "CHARACTER_LENGTH";
		break;
	case SQLExpression::eCHARSET:
		sRet = "CHARSET";
		break;
	case SQLExpression::eCOALESCE:
		sRet = "COALESCE";
		break;
	case SQLExpression::eCOERCIBILITY:
		sRet = "COERCIBILITY";
		break;
	case SQLExpression::eCOLLATION:
		sRet = "COLLATION";
		break;
	case SQLExpression::eCOMPRESS:
		sRet = "COMPRESS";
		break;
	case SQLExpression::eCONCAT:
		sRet = "CONCAT";
		break;
	case SQLExpression::eCONCAT_WS:
		sRet = "CONCAT_WS";
		break;
	case SQLExpression::eCONNECTION_ID:
		sRet = "CONNECTION_ID";
		break;
	case SQLExpression::eContains:
		sRet = "Contains";
		break;
	case SQLExpression::eCONV:
		sRet = "CONV";
		break;
	case SQLExpression::eCONVERT:
		sRet = "CONVERT";
		break;
	case SQLExpression::eCONVERT_TZ:
		sRet = "CONVERT_TZ";
		break;
	case SQLExpression::eConvexHull:
		sRet = "ConvexHull";
		break;
	case SQLExpression::eCOS:
		sRet = "COS";
		break;
	case SQLExpression::eCOT:
		sRet = "COT";
		break;
	case SQLExpression::eCOUNT:
		sRet = "COUNT";
		break;

	case SQLExpression::eCRC32:
		sRet = "CRC32";
		break;
	case SQLExpression::eCREATE_ASYMMETRIC_PRIV_KEY:
		sRet = "CREATE_ASYMMETRIC_PRIV_KEY";
		break;
	case SQLExpression::eCREATE_ASYMMETRIC_PUB_KEY:
		sRet = "CREATE_ASYMMETRIC_PUB_KEY";
		break;
	case SQLExpression::eCREATE_DH_PARAMETERS:
		sRet = "CREATE_DH_PARAMETERS";
		break;
	case SQLExpression::eCREATE_DIGEST:
		sRet = "CREATE_DIGEST";
		break;
	case SQLExpression::eCrosses:
		sRet = "Crosses";
		break;
	case SQLExpression::eCURDATE:
		sRet = "CURDATE";
		break;
	case SQLExpression::eCURRENT_DATE:
		sRet = "CURRENT_DATE";
		break;
	case SQLExpression::eCURRENT_TIME:
		sRet = "CURRENT_TIME";
		break;
	case SQLExpression::eCURRENT_TIMESTAMP:
		sRet = "CURRENT_TIMESTAMP";
		break;
	case SQLExpression::eCURRENT_USER:
		sRet = "CURRENT_USER";
		break;
	case SQLExpression::eCURTIME:
		sRet = "CURTIME";
		break;
	case SQLExpression::eDATABASE:
		sRet = "DATABASE";
		break;
	case SQLExpression::eDATE:
		sRet = "DATE";
		break;
	case SQLExpression::eDATE_ADD:
		sRet = "DATE_ADD";
		break;
	case SQLExpression::eDATE_FORMAT:
		sRet = "DATE_FORMAT";
		break;
	case SQLExpression::eDATE_SUB:
		sRet = "DATE_SUB";
		break;
	case SQLExpression::eDATEDIFF:
		sRet = "DATEDIFF";
		break;
	case SQLExpression::eDAY:
		sRet = "DAY";
		break;
	case SQLExpression::eDAYNAME:
		sRet = "DAYNAME";
		break;
	case SQLExpression::eDAYOFMONTH:
		sRet = "DAYOFMONTH";
		break;
	case SQLExpression::eDAYOFWEEK:
		sRet = "DAYOFWEEK";
		break;
	case SQLExpression::eDAYOFYEAR:
		sRet = "DAYOFYEAR";
		break;
	case SQLExpression::eDECODE:
		sRet = "DECODE";
		break;
	case SQLExpression::eDEFAULT:
		sRet = "DEFAULT";
		break;
	case SQLExpression::eDEGREES:
		sRet = "DEGREES";
		break;
	case SQLExpression::eDES_DECRYPT:
		sRet = "DES_DECRYPT";
		break;
	case SQLExpression::eDES_ENCRYPT:
		sRet = "DES_ENCRYPT";
		break;
	case SQLExpression::eDimension:
		sRet = "Dimension";
		break;
	case SQLExpression::eDisjoint:
		sRet = "Disjoint";
		break;
	case SQLExpression::eDistance:
		sRet = "Distance";
		break;
	case SQLExpression::eDIV:
		sRet = "DIV";
		break;
	case SQLExpression::eDivide:
		sRet = "/";
		break;
	case SQLExpression::eELT:
		sRet = "ELT";
		break;
	case SQLExpression::eENCODE:
		sRet = "ENCODE";
		break;
	case SQLExpression::eENCRYPT:
		sRet = "ENCRYPT";
		break;
	case SQLExpression::eEndPoint:
		sRet = "EndPoint";
		break;
	case SQLExpression::eEnvelope:
		sRet = "Envelope";
		break;

	case SQLExpression::eEqualNullSafe:
		sRet = "<=>";
		break;
	case SQLExpression::eEquals:
		sRet = "Equals";
		break;
	case SQLExpression::eEXP:
		sRet = "EXP";
		break;
	case SQLExpression::eEXPORT_SET:
		sRet = "EXPORT_SET";
		break;
	case SQLExpression::eExteriorRing:
		sRet = "ExteriorRing";
		break;
	case SQLExpression::eEXTRACT:
		sRet = "EXTRACT";
		break;
	case SQLExpression::eExtractValue:
		sRet = "ExtractValue";
		break;
	case SQLExpression::eFIELD:
		sRet = "FIELD";
		break;
	case SQLExpression::eFIND_IN_SET:
		sRet = "FIND_IN_SET";
		break;
	case SQLExpression::eFLOOR:
		sRet = "FLOOR";
		break;
	case SQLExpression::eFORMAT:
		sRet = "FORMAT";
		break;
	case SQLExpression::eFOUND_ROWS:
		sRet = "FOUND_ROWS";
		break;
	case SQLExpression::eFROM_BASE64:
		sRet = "FROM_BASE64";
		break;
	case SQLExpression::eFROM_DAYS:
		sRet = "FROM_DAYS";
		break;
	case SQLExpression::eFROM_UNIXTIME:
		sRet = "FROM_UNIXTIME";
		break;
	case SQLExpression::eGeomCollFromText:
		sRet = "GeomCollFromText";
		break;
	case SQLExpression::eGeometryCollectionFromText:
		sRet = "GeometryCollectionFromText";
		break;
	case SQLExpression::eGeomCollFromWKB:
		sRet = "GeomCollFromWKB";
		break;
	case SQLExpression::eGeometryCollectionFromWKB:
		sRet = "GeometryCollectionFromWKB";
		break;
	case SQLExpression::eGeometryCollection:
		sRet = "GeometryCollection";
		break;
	case SQLExpression::eGeometryN:
		sRet = "GeometryN";
		break;
	case SQLExpression::eGeometryType:
		sRet = "GeometryType";
		break;
	case SQLExpression::eGeomFromText:
		sRet = "GeomFromText";
		break;
	case SQLExpression::eGeometryFromText:
		sRet = "GeometryFromText";
		break;
	case SQLExpression::eGeomFromWKB:
		sRet = "GeomFromWKB";
		break;
	case SQLExpression::eGeometryFromWKB:
		sRet = "GeometryFromWKB";
		break;
	case SQLExpression::eGET_FORMAT:
		sRet = "GET_FORMAT";
		break;
	case SQLExpression::eGET_LOCK:
		sRet = "GET_LOCK";
		break;
	case SQLExpression::eGLength:
		sRet = "GLength";
		break;
	case SQLExpression::eGreaterThan:
		sRet = ">";
		break;
	case SQLExpression::eGreaterThanEq:
		sRet = ">=";
		break;
	case SQLExpression::eGREATEST:
		sRet = "GREATEST";
		break;
	case SQLExpression::eGROUP_CONCAT:
		sRet = "GROUP_CONCAT";
		break;
	case SQLExpression::eGTID_SUBSET:
		sRet = "GTID_SUBSET";
		break;
	case SQLExpression::eGTID_SUBTRACT:
		sRet = "GTID_SUBTRACT";
		break;
	case SQLExpression::eHEX:
		sRet = "HEX";
		break;
	case SQLExpression::eHOUR:
		sRet = "HOUR";
		break;
	case SQLExpression::eIF:
		sRet = "IF";
		break;
	case SQLExpression::eIFNULL:
		sRet = "IFNULL";
		break;
	case SQLExpression::eIN:
		sRet = "IN";
		break;
	case SQLExpression::eINET_ATON:
		sRet = "INET_ATON";
		break;
	case SQLExpression::eINET_NTOA:
		sRet = "INET_NTOA";
		break;
	case SQLExpression::eINET6_ATON:
		sRet = "INET6_ATON";
		break;
	case SQLExpression::eINET6_NTOA:
		sRet = "INET6_NTOA";
		break;
	case SQLExpression::eINSERT:
		sRet = "INSERT";
		break;
	case SQLExpression::eINSTR:
		sRet = "INSTR";
		break;
	case SQLExpression::eInteriorRingN:
		sRet = "InteriorRingN";
		break;
	case SQLExpression::eIntersects:
		sRet = "Intersects";
		break;
	case SQLExpression::eINTERVAL:
		sRet = "INTERVAL";
		break;
	case SQLExpression::eIS:
		sRet = "IS";
		break;
	case SQLExpression::eIS_FREE_LOCK:
		sRet = "IS_FREE_LOCK";
		break;
	case SQLExpression::eIS_IPV4:
		sRet = "IS_IPV4";
		break;
	case SQLExpression::eIS_IPV4_COMPAT:
		sRet = "IS_IPV4_COMPAT";
		break;
	case SQLExpression::eIS_IPV4_MAPPED:
		sRet = "IS_IPV4_MAPPED";
		break;
	case SQLExpression::eIS_IPV6:
		sRet = "IS_IPV6";
		break;
	case SQLExpression::eIS_NOT:
		sRet = "IS NOT";
		break;
	case SQLExpression::eIS_NOT_NULL:
		sRet = "IS NOT NULL";
		break;
	case SQLExpression::eIS_NULL:
		sRet = "IS NULL";
		break;
	case SQLExpression::eIS_USED_LOCK:
		sRet = "IS_USED_LOCK";
		break;
	case SQLExpression::eIsClosed:
		sRet = "IsClosed";
		break;
	case SQLExpression::eIsEmpty:
		sRet = "IsEmpty";
		break;
	case SQLExpression::eISNULL:
		sRet = "ISNULL";
		break;
	case SQLExpression::eIsSimple:
		sRet = "IsSimple";
		break;
	case SQLExpression::eJSON_APPEND:
		sRet = "JSON_APPEND";
		break;
	case SQLExpression::eJSON_ARRAY:
		sRet = "JSON_ARRAY";
		break;
	case SQLExpression::eJSON_ARRAY_APPEND:
		sRet = "JSON_ARRAY_APPEND";
		break;
	case SQLExpression::eJSON_ARRAY_INSERT:
		sRet = "JSON_ARRAY_INSERT";
		break;
	case SQLExpression::eJSON_ARRAYAGG:
		sRet = "JSON_ARRAYAGG";
		break;
	case SQLExpression::eJSON_ExtractOp:
		sRet = "->";
		break;
	case SQLExpression::eJSON_CONTAINS:
		sRet = "JSON_CONTAINS";
		break;
	case SQLExpression::eJSON_CONTAINS_PATH:
		sRet = "JSON_CONTAINS_PATH";
		break;
	case SQLExpression::eJSON_DEPTH:
		sRet = "JSON_DEPTH";
		break;
	case SQLExpression::eJSON_EXTRACT:
		sRet = "JSON_EXTRACT";
		break;
	case SQLExpression::eJSON_UnquoteExtractOp:
		sRet = "->>";
		break;
	case SQLExpression::eJSON_INSERT:
		sRet = "JSON_INSERT";
		break;
	case SQLExpression::eJSON_KEYS:
		sRet = "JSON_KEYS";
		break;
	case SQLExpression::eJSON_LENGTH:
		sRet = "JSON_LENGTH";
		break;
	case SQLExpression::eJSON_MERGE:
		sRet = "JSON_MERGE";
		break;
	case SQLExpression::eJSON_MERGE_PATCH:
		sRet = "JSON_MERGE_PATCH";
		break;
	case SQLExpression::eJSON_MERGE_PRESERVE:
		sRet = "JSON_MERGE_PRESERVE";
		break;
	case SQLExpression::eJSON_OBJECT:
		sRet = "JSON_OBJECT";
		break;
	case SQLExpression::eJSON_OBJECTAGG:
		sRet = "JSON_OBJECTAGG";
		break;
	case SQLExpression::eJSON_PRETTY:
		sRet = "JSON_PRETTY";
		break;
	case SQLExpression::eJSON_QUOTE:
		sRet = "JSON_QUOTE";
		break;
	case SQLExpression::eJSON_REMOVE:
		sRet = "JSON_REMOVE";
		break;
	case SQLExpression::eJSON_REPLACE:
		sRet = "JSON_REPLACE";
		break;
	case SQLExpression::eJSON_SEARCH:
		sRet = "JSON_SEARCH";
		break;
	case SQLExpression::eJSON_SET:
		sRet = "JSON_SET";
		break;
	case SQLExpression::eJSON_STORAGE_SIZE:
		sRet = "JSON_STORAGE_SIZE";
		break;
	case SQLExpression::eJSON_TYPE:
		sRet = "JSON_TYPE";
		break;
	case SQLExpression::eJSON_UNQUOTE:
		sRet = "JSON_UNQUOTE";
		break;
	case SQLExpression::eJSON_VALID:
		sRet = "JSON_VALID";
		break;
	case SQLExpression::eLAST_DAY:
		sRet = "LAST_DAY";
		break;
	case SQLExpression::eLAST_INSERT_ID:
		sRet = "LAST_INSERT_ID";
		break;
	case SQLExpression::eLCASE:
		sRet = "LCASE";
		break;
	case SQLExpression::eLEAST:
		sRet = "LEAST";
		break;
	case SQLExpression::eLEFT:
		sRet = "LEFT";
		break;
	case SQLExpression::eLeftShift:
		sRet = "<<";
		break;
	case SQLExpression::eLENGTH:
		sRet = "LENGTH";
		break;
	case SQLExpression::eLessThan:
		sRet = "<";
		break;
	case SQLExpression::eLessThanEq:
		sRet = "<=";
		break;
	case SQLExpression::eLIKE:
		sRet = "LIKE";
		break;
	case SQLExpression::eLineFromText:
		sRet = "LineFromText";
		break;
	case SQLExpression::eLineStringFromText:
		sRet = "LineStringFromText";
		break;
	case SQLExpression::eLineFromWKB:
		sRet = "LineFromWKB";
		break;
	case SQLExpression::eLineStringFromWKB:
		sRet = "LineStringFromWKB";
		break;
	case SQLExpression::eLineString:
		sRet = "LineString";
		break;
	case SQLExpression::eLN:
		sRet = "LN";
		break;
	case SQLExpression::eLOAD_FILE:
		sRet = "LOAD_FILE";
		break;
	case SQLExpression::eLOCALTIME:
		sRet = "LOCALTIME";
		break;
	case SQLExpression::eLOCALTIMESTAMP:
		sRet = "LOCALTIMESTAMP";
		break;
	case SQLExpression::eLOCATE:
		sRet = "LOCATE";
		break;
	case SQLExpression::eLOG:
		sRet = "LOG";
		break;
	case SQLExpression::eLOG10:
		sRet = "LOG10";
		break;
	case SQLExpression::eLOG2:
		sRet = "LOG2";
		break;
	case SQLExpression::eLOWER:
		sRet = "LOWER";
		break;
	case SQLExpression::eLPAD:
		sRet = "LPAD";
		break;
	case SQLExpression::eLTRIM:
		sRet = "LTRIM";
		break;
	case SQLExpression::eMAKE_SET:
		sRet = "MAKE_SET";
		break;
	case SQLExpression::eMAKEDATE:
		sRet = "MAKEDATE";
		break;
	case SQLExpression::eMAKETIME:
		sRet = "MAKETIME";
		break;
	case SQLExpression::eMASTER_POS_WAIT:
		sRet = "MASTER_POS_WAIT";
		break;
	case SQLExpression::eMATCH:
		sRet = "MATCH";
		break;
	case SQLExpression::eMAX:
		sRet = "MAX";
		break;
	case SQLExpression::eMBRContains:
		sRet = "MBRContains";
		break;
	case SQLExpression::eMBRCoveredBy:
		sRet = "MBRCoveredBy";
		break;
	case SQLExpression::eMBRCovers:
		sRet = "MBRCovers";
		break;
	case SQLExpression::eMBRDisjoint:
		sRet = "MBRDisjoint";
		break;
	case SQLExpression::eMBREqual:
		sRet = "MBREqual";
		break;
	case SQLExpression::eMBREquals:
		sRet = "MBREquals";
		break;
	case SQLExpression::eMBRIntersects:
		sRet = "MBRIntersects";
		break;
	case SQLExpression::eMBROverlaps:
		sRet = "MBROverlaps";
		break;
	case SQLExpression::eMBRTouches:
		sRet = "MBRTouches";
		break;
	case SQLExpression::eMBRWithin:
		sRet = "MBRWithin";
		break;
	case SQLExpression::eMD5:
		sRet = "MD5";
		break;
	case SQLExpression::eMICROSECOND:
		sRet = "MICROSECOND";
		break;
	case SQLExpression::eMID:
		sRet = "MID";
		break;
	case SQLExpression::eMIN:
		sRet = "MIN";
		break;
	case SQLExpression::eSubtract:
		sRet = "-";
		break;
	case SQLExpression::eMINUTE:
		sRet = "MINUTE";
		break;
	case SQLExpression::eMLineFromText:
		sRet = "MLineFromText";
		break;
	case SQLExpression::eMultiLineStringFromText:
		sRet = "MultiLineStringFromText";
		break;
	case SQLExpression::eMLineFromWKB:
		sRet = "MLineFromWKB";
		break;
	case SQLExpression::eMultiLineStringFromWKB:
		sRet = "MultiLineStringFromWKB";
		break;
	case SQLExpression::eMOD:
		sRet = "MOD";
		break;

	case SQLExpression::eMONTH:
		sRet = "MONTH";
		break;
	case SQLExpression::eMONTHNAME:
		sRet = "MONTHNAME";
		break;
	case SQLExpression::eMPointFromText:
		sRet = "MPointFromText";
		break;
	case SQLExpression::eMultiPointFromText:
		sRet = "MultiPointFromText";
		break;
	case SQLExpression::eMPointFromWKB:
		sRet = "MPointFromWKB";
		break;
	case SQLExpression::eMultiPointFromWKB:
		sRet = "MultiPointFromWKB";
		break;
	case SQLExpression::eMPolyFromText:
		sRet = "MPolyFromText";
		break;
	case SQLExpression::eMultiPolygonFromText:
		sRet = "MultiPolygonFromText";
		break;
	case SQLExpression::eMPolyFromWKB:
		sRet = "MPolyFromWKB";
		break;
	case SQLExpression::eMultiPolygonFromWKB:
		sRet = "MultiPolygonFromWKB";
		break;
	case SQLExpression::eMultiLineString:
		sRet = "MultiLineString";
		break;
	case SQLExpression::eMultiPoint:
		sRet = "MultiPoint";
		break;
	case SQLExpression::eMultiPolygon:
		sRet = "MultiPolygon";
		break;
	case SQLExpression::eNAME_CONST:
		sRet = "NAME_CONST";
		break;
	case SQLExpression::eNOT:
		sRet = "NOT";
		break;
	case SQLExpression::eNotOp:
		sRet = "!";
		break;

	case SQLExpression::eNotEqSQL:
		sRet = "<>";
		break;
	case SQLExpression::eNotEq:
		sRet = "!=";
		break;


	case SQLExpression::eNOW:
		sRet = "NOW";
		break;
	case SQLExpression::eNULLIF:
		sRet = "NULLIF";
		break;
	case SQLExpression::eNumGeometries:
		sRet = "NumGeometries";
		break;
	case SQLExpression::eNumInteriorRings:
		sRet = "NumInteriorRings";
		break;
	case SQLExpression::eNumPoints:
		sRet = "NumPoints";
		break;
	case SQLExpression::eOCT:
		sRet = "OCT";
		break;
	case SQLExpression::eOCTET_LENGTH:
		sRet = "OCTET_LENGTH";
		break;
	case SQLExpression::eOLD_PASSWORD:
		sRet = "OLD_PASSWORD";
		break;
	case SQLExpression::eOR:
		sRet = "OR";
		break;
	case SQLExpression::eOrOp:
		sRet = "||";
		break;
	case SQLExpression::eORD:
		sRet = "ORD";
		break;
	case SQLExpression::eOverlaps:
		sRet = "Overlaps";
		break;
	case SQLExpression::ePASSWORD:
		sRet = "PASSWORD";
		break;
	case SQLExpression::ePERIOD_ADD:
		sRet = "PERIOD_ADD";
		break;
	case SQLExpression::ePERIOD_DIFF:
		sRet = "PERIOD_DIFF";
		break;
	case SQLExpression::ePI:
		sRet = "PI";
		break;
	case SQLExpression::eadd:
		sRet = "+";
		break;
	case SQLExpression::ePoint:
		sRet = "Point";
		break;
	case SQLExpression::ePointFromText:
		sRet = "PointFromText";
		break;
	case SQLExpression::ePointFromWKB:
		sRet = "PointFromWKB";
		break;
	case SQLExpression::ePointN:
		sRet = "PointN";
		break;
	case SQLExpression::ePolyFromText:
		sRet = "PolyFromText";
		break;
	case SQLExpression::ePolygonFromText:
		sRet = "PolygonFromText";
		break;
	case SQLExpression::ePolyFromWKB:
		sRet = "PolyFromWKB";
		break;
	case SQLExpression::ePolygonFromWKB:
		sRet = "PolygonFromWKB";
		break;
	case SQLExpression::ePolygon:
		sRet = "Polygon";
		break;
	case SQLExpression::ePOSITION:
		sRet = "POSITION";
		break;
	case SQLExpression::ePOW:
		sRet = "POW";
		break;
	case SQLExpression::ePOWER:
		sRet = "POWER";
		break;
	case SQLExpression::ePROCEDURE_ANALYSE:
		sRet = "PROCEDURE ANALYSE";
		break;
	case SQLExpression::eQUARTER:
		sRet = "QUARTER";
		break;
	case SQLExpression::eQUOTE:
		sRet = "QUOTE";
		break;
	case SQLExpression::eRADIANS:
		sRet = "RADIANS";
		break;
	case SQLExpression::eRAND:
		sRet = "RAND";
		break;
	case SQLExpression::eRANDOM_BYTES:
		sRet = "RANDOM_BYTES";
		break;
	case SQLExpression::eREGEXP:
		sRet = "REGEXP";
		break;
	case SQLExpression::eRELEASE_ALL_LOCKS:
		sRet = "RELEASE_ALL_LOCKS";
		break;
	case SQLExpression::eRELEASE_LOCK:
		sRet = "RELEASE_LOCK";
		break;
	case SQLExpression::eREPEAT:
		sRet = "REPEAT";
		break;
	case SQLExpression::eREPLACE:
		sRet = "REPLACE";
		break;
	case SQLExpression::Function::eREVERSE:
		sRet = "REVERSE";
		break;
	case SQLExpression::eRIGHT:
		sRet = "RIGHT";
		break;
	case SQLExpression::eRightShift:
		sRet = ">>";
		break;
	case SQLExpression::eRLIKE:
		sRet = "RLIKE";
		break;
	case SQLExpression::eROUND:
		sRet = "ROUND";
		break;
	case SQLExpression::eROW_COUNT:
		sRet = "ROW_COUNT";
		break;
	case SQLExpression::eRPAD:
		sRet = "RPAD";
		break;
	case SQLExpression::eRTRIM:
		sRet = "RTRIM";
		break;
	case SQLExpression::eSCHEMA:
		sRet = "SCHEMA";
		break;
	case SQLExpression::eSEC_TO_TIME:
		sRet = "SEC_TO_TIME";
		break;
	case SQLExpression::eSECOND:
		sRet = "SECOND";
		break;
	case SQLExpression::eSESSION_USER:
		sRet = "SESSION_USER";
		break;
	case SQLExpression::eSHA1:
		sRet = "SHA1";
		break;
	case SQLExpression::eSHA2:
		sRet = "SHA2";
		break;
	case SQLExpression::eSIGN:
		sRet = "SIGN";
		break;
	case SQLExpression::eSIN:
		sRet = "SIN";
		break;
	case SQLExpression::eSLEEP:
		sRet = "SLEEP";
		break;
	case SQLExpression::eSOUNDEX:
		sRet = "SOUNDEX";
		break;
	case SQLExpression::eSOUNDS_LIKE:
		sRet = "SOUNDS LIKE";
		break;
	case SQLExpression::eSPACE:
		sRet = "SPACE";
		break;
	case SQLExpression::eSQRT:
		sRet = "SQRT";
		break;
	case SQLExpression::eSRID:
		sRet = "SRID";
		break;
	case SQLExpression::eST_Area:
		sRet = "ST_Area";
		break;
	case SQLExpression::eST_AsBinary:
		sRet = "ST_AsBinary";
		break;
	case SQLExpression::eST_AsWKB:
		sRet = "ST_AsWKB";
		break;
	case SQLExpression::eST_AsGeoJSON:
		sRet = "ST_AsGeoJSON";
		break;
	case SQLExpression::eST_AsText:
		sRet = "ST_AsText";
		break;
	case SQLExpression::eST_AsWKT:
		sRet = "ST_AsWKT";
		break;
	case SQLExpression::eST_Buffer:
		sRet = "ST_Buffer";
		break;
	case SQLExpression::eST_Buffer_Strategy:
		sRet = "ST_Buffer_Strategy";
		break;
	case SQLExpression::eST_Centroid:
		sRet = "ST_Centroid";
		break;
	case SQLExpression::eST_Contains:
		sRet = "ST_Contains";
		break;
	case SQLExpression::eST_ConvexHull:
		sRet = "ST_ConvexHull";
		break;
	case SQLExpression::eST_Crosses:
		sRet = "ST_Crosses";
		break;
	case SQLExpression::eST_Difference:
		sRet = "ST_Difference";
		break;
	case SQLExpression::eST_Dimension:
		sRet = "ST_Dimension";
		break;
	case SQLExpression::eST_Disjoint:
		sRet = "ST_Disjoint";
		break;
	case SQLExpression::eST_Distance:
		sRet = "ST_Distance";
		break;
	case SQLExpression::eST_Distance_Sphere:
		sRet = "ST_Distance_Sphere";
		break;
	case SQLExpression::eST_EndPoint:
		sRet = "ST_EndPoint";
		break;
	case SQLExpression::eST_Envelope:
		sRet = "ST_Envelope";
		break;
	case SQLExpression::eST_Equals:
		sRet = "ST_Equals";
		break;
	case SQLExpression::eST_ExteriorRing:
		sRet = "ST_ExteriorRing";
		break;
	case SQLExpression::eST_GeoHash:
		sRet = "ST_GeoHash";
		break;
	case SQLExpression::eST_GeomCollFromText:
		sRet = "ST_GeomCollFromText";
		break;
	case SQLExpression::eST_GeometryCollectionFromText:
		sRet = "ST_GeometryCollectionFromText";
		break;
	case SQLExpression::eST_GeomCollFromTxt:
		sRet = "ST_GeomCollFromTxt";
		break;
	case SQLExpression::eST_GeomCollFromWKB:
		sRet = "ST_GeomCollFromWKB";
		break;
	case SQLExpression::eST_GeometryCollectionFromWKB:
		sRet = "ST_GeometryCollectionFromWKB";
		break;
	case SQLExpression::eST_GeometryN:
		sRet = "ST_GeometryN";
		break;
	case SQLExpression::eST_GeometryType:
		sRet = "ST_GeometryType";
		break;
	case SQLExpression::eST_GeomFromGeoJSON:
		sRet = "ST_GeomFromGeoJSON";
		break;
	case SQLExpression::eST_GeomFromText:
		sRet = "ST_GeomFromText";
		break;
	case SQLExpression::eST_GeometryFromText:
		sRet = "ST_GeometryFromText";
		break;
	case SQLExpression::eST_GeomFromWKB:
		sRet = "ST_GeomFromWKB";
		break;
	case SQLExpression::eST_GeometryFromWKB:
		sRet = "ST_GeometryFromWKB";
		break;
	case SQLExpression::eST_GLength:
		sRet = "ST_GLength";
		break;
	case SQLExpression::eST_InteriorRingN:
		sRet = "ST_InteriorRingN";
		break;
	case SQLExpression::eST_Intersection:
		sRet = "ST_Intersection";
		break;
	case SQLExpression::eST_Intersects:
		sRet = "ST_Intersects";
		break;
	case SQLExpression::eST_IsClosed:
		sRet = "ST_IsClosed";
		break;
	case SQLExpression::eST_IsEmpty:
		sRet = "ST_IsEmpty";
		break;
	case SQLExpression::eST_IsSimple:
		sRet = "ST_IsSimple";
		break;
	case SQLExpression::eST_IsValid:
		sRet = "ST_IsValid";
		break;
	case SQLExpression::eST_LatFromGeoHash:
		sRet = "ST_LatFromGeoHash";
		break;
	case SQLExpression::eST_Length:
		sRet = "ST_Length";
		break;
	case SQLExpression::eST_LineFromText:
		sRet = "ST_LineFromText";
		break;
	case SQLExpression::eST_LineStringFromText:
		sRet = "ST_LineStringFromText";
		break;
	case SQLExpression::eST_LineFromWKB:
		sRet = "ST_LineFromWKB";
		break;
	case SQLExpression::eST_LineStringFromWKB:
		sRet = "ST_LineStringFromWKB";
		break;
	case SQLExpression::eST_LongFromGeoHash:
		sRet = "ST_LongFromGeoHash";
		break;
	case SQLExpression::eST_MakeEnvelope:
		sRet = "ST_MakeEnvelope";
		break;
	case SQLExpression::eST_MLineFromText:
		sRet = "ST_MLineFromText";
		break;
	case SQLExpression::eST_MultiLineStringFromText:
		sRet = "ST_MultiLineStringFromText";
		break;
	case SQLExpression::eST_MLineFromWKB:
		sRet = "ST_MLineFromWKB";
		break;
	case SQLExpression::eST_MultiLineStringFromWKB:
		sRet = "ST_MultiLineStringFromWKB";
		break;
	case SQLExpression::eST_MPointFromText:
		sRet = "ST_MPointFromText";
		break;
	case SQLExpression::eST_MultiPointFromWKB:
		sRet = "ST_MultiPointFromWKB";
		break;
	case SQLExpression::eST_MPointFromWKB:
		sRet = "ST_MPointFromWKB";
		break;
	case SQLExpression::eST_MPolyFromText:
		sRet = "ST_MPolyFromText";
		break;
	case SQLExpression::eST_MultiPolygonFromText:
		sRet = "ST_MulitPolygonFromText";
		break;
	case SQLExpression::eST_MPolyFromWKB:
		sRet = "ST_MPolyFromWKB";
		break;
	case SQLExpression::eST_MultiPolygonFromWKB:
		sRet = "ST_MultiPolygonFromWKB";
		break;
	case SQLExpression::eST_NumGeometries:
		sRet = "ST_NumGeometries";
		break;
	case SQLExpression::eST_NumInteriorRing:
		sRet = "ST_NumInteriorRing";
		break;
	case SQLExpression::eST_NumPoints:
		sRet = "ST_NumPoints";
		break;
	case SQLExpression::eST_Overlaps:
		sRet = "ST_Overlaps";
		break;
	case SQLExpression::eST_PointFromGeoHash:
		sRet = "ST_PointFromGeoHash";
		break;
	case SQLExpression::eST_PointFromText:
		sRet = "ST_PointFromText";
		break;
	case SQLExpression::eST_PointFromWKB:
		sRet = "ST_PointFromWKB";
		break;
	case SQLExpression::eST_PointN:
		sRet = "ST_PointN";
		break;
	case SQLExpression::eST_PolyFromText:
		sRet = "ST_PolyFromText";
		break;
	case SQLExpression::eST_PolygonFromText:
		sRet = "ST_PolygonFromText";
		break;
	case SQLExpression::eST_PolyFromWKB:
		sRet = "ST_PolyFromWKB";
		break;
	case SQLExpression::eST_PolygonFromWKB:
		sRet = "ST_PolygonFromWKB";
		break;
	case SQLExpression::eST_Simplify:
		sRet = "ST_Simplify";
		break;
	case SQLExpression::eST_SRID:
		sRet = "ST_SRID";
		break;
	case SQLExpression::eST_StartPoint:
		sRet = "ST_StartPoint";
		break;
	case SQLExpression::eST_SymDifference:
		sRet = "ST_SymDifference";
		break;
	case SQLExpression::eST_Touches:
		sRet = "ST_Touches";
		break;
	case SQLExpression::eST_Union:
		sRet = "ST_Union";
		break;
	case SQLExpression::eST_Validate:
		sRet = "ST_Validate";
		break;
	case SQLExpression::eST_Within:
		sRet = "ST_Within";
		break;
	case SQLExpression::eST_X:
		sRet = "ST_X";
		break;
	case SQLExpression::eST_Y:
		sRet = "ST_Y";
		break;
	case SQLExpression::eStartPoint:
		sRet = "StartPoint";
		break;
	case SQLExpression::eSTD:
		sRet = "STD";
		break;
	case SQLExpression::eSTDDEV:
		sRet = "STDDEV";
		break;
	case SQLExpression::eSTDDEV_POP:
		sRet = "STDDEV_POP";
		break;
	case SQLExpression::eSTDDEV_SAMP:
		sRet = "STDDEV_SAMP";
		break;
	case SQLExpression::eSTR_TO_DATE:
		sRet = "STR_TO_DATE";
		break;
	case SQLExpression::eSTRCMP:
		sRet = "STRCMP";
		break;
	case SQLExpression::eSUBDATE:
		sRet = "SUBDATE";
		break;
	case SQLExpression::eSUBSTR:
		sRet = "SUBSTR";
		break;
	case SQLExpression::eSUBSTRING:
		sRet = "SUBSTRING";
		break;
	case SQLExpression::eSUBSTRING_INDEX:
		sRet = "SUBSTRING_INDEX";
		break;
	case SQLExpression::eSUBTIME:
		sRet = "SUBTIME";
		break;
	case SQLExpression::eSUM:
		sRet = "SUM";
		break;
	case SQLExpression::eSYSDATE:
		sRet = "SYSDATE";
		break;
	case SQLExpression::eSYSTEM_USER:
		sRet = "SYSTEM_USER";
		break;
	case SQLExpression::eTAN:
		sRet = "TAN";
		break;
	case SQLExpression::eTIME:
		sRet = "TIME";
		break;
	case SQLExpression::eTIME_FORMAT:
		sRet = "TIME_FORMAT";
		break;
	case SQLExpression::eTIME_TO_SEC:
		sRet = "TIME_TO_SEC";
		break;
	case SQLExpression::eTIMEDIFF:
		sRet = "TIMEDIFF";
		break;
	case SQLExpression::eMultiply:
		sRet = "*";
		break;
	case SQLExpression::eTIMESTAMP:
		sRet = "TIMESTAMP";
		break;
	case SQLExpression::eTIMESTAMPADD:
		sRet = "TIMESTAMPADD";
		break;
	case SQLExpression::eTIMESTAMPDIFF:
		sRet = "TIMESTAMPDIFF";
		break;
	case SQLExpression::eTO_BASE64:
		sRet = "TO_BASE64";
		break;
	case SQLExpression::eTO_DAYS:
		sRet = "TO_DAYS";
		break;
	case SQLExpression::eTO_SECONDS:
		sRet = "TO_SECONDS";
		break;
	case SQLExpression::eTouches:
		sRet = "Touches";
		break;
	case SQLExpression::eTRIM:
		sRet = "TRIM";
		break;
	case SQLExpression::eTRUNCATE:
		sRet = "TRUNCATE";
		break;
	case SQLExpression::eUCASE:
		sRet = "UCASE";
		break;
	case SQLExpression::esubtract:
		sRet = "-";
		break;
	case SQLExpression::eUNCOMPRESS:
		sRet = "UNCOMPRESS";
		break;
	case SQLExpression::eUNCOMPRESSED_LENGTH:
		sRet = "UNCOMPRESSED_LENGTH";
		break;
	case SQLExpression::eUNHEX:
		sRet = "UNHEX";
		break;
	case SQLExpression::eUNIX_TIMESTAMP:
		sRet = "UNIX_TIMESTAMP";
		break;
	case SQLExpression::eUpdateXML:
		sRet = "UpdateXML";
		break;
	case SQLExpression::eUPPER:
		sRet = "UPPER";
		break;
	case SQLExpression::eUSER:
		sRet = "USER";
		break;
	case SQLExpression::eUTC_DATE:
		sRet = "UTC_DATE";
		break;
	case SQLExpression::eUTC_TIME:
		sRet = "UTC_TIME";
		break;
	case SQLExpression::eUTC_TIMESTAMP:
		sRet = "UTC_TIMESTAMP";
		break;
	case SQLExpression::eUUID:
		sRet = "UUID";
		break;
	case SQLExpression::eUUID_SHORT:
		sRet = "UUID_SHORT";
		break;
	case SQLExpression::eVALIDATE_PASSWORD_STRENGTH:
		sRet = "VALIDATE_PASSWORD_STRENGTH";
		break;
	case SQLExpression::eVALUES:
		sRet = "VALUES";
		break;
	case SQLExpression::eVAR_POP:
		sRet = "VAR_POP";
		break;
	case SQLExpression::eVAR_SAMP:
		sRet = "VAR_SAMP";
		break;
	case SQLExpression::eVARIANCE:
		sRet = "VARIANCE";
		break;
	case SQLExpression::eVERSION:
		sRet = "VERSION";
		break;
	case SQLExpression::eWAIT_FOR_EXECUTED_GTID_SET:
		sRet = "WAIT_FOR_EXECUTED_GTID_SET";
		break;
	case SQLExpression::eWAIT_UNTIL_SQL_THREAD_AFTER_GTIDS:
		sRet = "WAIT_UNTIL_SQL_THREAD_AFTER_GTIDS";
		break;
	case SQLExpression::eWEEK:
		sRet = "WEEK";
		break;
	case SQLExpression::eWEEKDAY:
		sRet = "WEEKDAY";
		break;
	case SQLExpression::eWEEKOFYEAR:
		sRet = "WEEKOFYEAR";
		break;
	case SQLExpression::eWEIGHT_STRING:
		sRet = "WEIGHT_STRING";
		break;
	case SQLExpression::eWithin:
		sRet = "Within";
		break;
	case SQLExpression::eX:
		sRet = "X";
		break;
	case SQLExpression::eXOR:
		sRet = "XOR";
		break;
	case SQLExpression::eY:
		sRet = "Y";
		break;
	case SQLExpression::eYEAR:
		sRet = "YEAR";
		break;
	case SQLExpression::eYEARWEEK:
		sRet = "YEARWEEK";
		break;

	default:
		break;
	}
	return sRet;
}

std::string SQLExpression::buildFunctionString(SQLExpression::Function e, const SQLExpressionList & sqleList)
{
	std::string sRet = getFunction(e) + "(" + sqleList.getListString(false) + ")";
	return sRet;
}

std::string SQLExpression::buildFunctionString(SQLExpression::Function e, const SQLExpression & sqle, const SQLExpressionList & sqleList)
{
	SQLExpressionList sqlelTmp = sqleList;
	sqlelTmp.push_front(sqle);
	return buildFunctionString(e, sqlelTmp);
}

SQLExpression & SQLExpression::genericFunction(SQLExpression::Function e, const SQLExpressionList & sqleList)
{
	SQLExpressionList sqlel = sqleList;
	sqlel.push_front(*this);
	sqlel.removeEmptyExpressions();
	sqlel.updateString();
	sqlFunction(e, sqlel);
	return *this;
}

SQLExpression::operator bool() const
{
	return !toString().empty();
}

SQLExpression & SQLExpression::singleQuotes()
{
	sCore = "'" + SQLTable::escapeStringStatic(toString()) + "'";
	clearEdges();
	return *this;
}

SQLExpression & SQLExpression::doubleQuotes()
{
	sCore = "\"" + SQLTable::escapeStringStatic(toString()) + "\"";
	clearEdges();
	return *this;
}

void SQLExpression::sqlFunction(SQLExpression::Function e, const SQLExpressionList & sqleList)
{
	sLeft = getFunction(e) + "(";
	std::string sTmp = sqleList.getListString(false);
	if (!sTmp.empty()) {
		if (!sCore.empty() || !sRight.empty()) {
			sRight += ",";
		}
		sRight += sTmp;
	}
	sRight += ")";
}

void SQLExpression::sqlFunction(SQLExpression::Function e)
{
	sCore = getFunction(e) + "()";
	sLeft = "";
	sRight = "";
}

SQLExpression & SQLExpression::equal(const SQLExpression & sqle)
{
	generalOperation(getFunction(eEqual), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::equalNullSafe(const SQLExpression & sqle)
{
	generalOperation(getFunction(eEqualNullSafe), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::notEqual(const SQLExpression & sqle)
{
	generalOperation(getFunction(eNotEq), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::notEqualSQL(const SQLExpression & sqle)
{
	generalOperation(getFunction(eNotEqSQL), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::lessThanEq(const SQLExpression & sqle)
{
	generalOperation(getFunction(eLessThanEq), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::lessThan(const SQLExpression & sqle)
{
	generalOperation(getFunction(eLessThan), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::greaterThanEq(const SQLExpression & sqle)
{
	generalOperation(getFunction(eGreaterThanEq), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::greaterThan(const SQLExpression & sqle)
{
	generalOperation(getFunction(eGreaterThan), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::IS(const SQLExpression & sqle)
{
	generalOperation(getFunction(eIS), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::IS_NOT(const SQLExpression & sqle)
{
	generalOperation(getFunction(eIS_NOT), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::IS_NULL()
{
	generalOperation(getFunction(eIS_NULL), false);
	return *this;
}

SQLExpression & SQLExpression::IS_NOT_NULL()
{
	sRight += " " + getFunction(eIS_NOT_NULL);
	return *this;
}

SQLExpression & SQLExpression::BETWEEN(const SQLExpression & sqleMin, const SQLExpression & sqleMax)
{
	sRight += " " + getFunction(eBETWEEN) + " " + sqleMin.toString() + " "
		+ getFunction(eAND) + " " + sqleMax.toString();
	return *this;
}

SQLExpression & SQLExpression::NOT_BETWEEN(const SQLExpression & sqleMin, const SQLExpression & sqleMax)
{
	sRight += " " + getFunction(eNOT) + " " + getFunction(eBETWEEN) + " " + sqleMin.toString() + " "
		+ getFunction(eAND) + " " + sqleMax.toString();
	return *this;
}

SQLExpression & SQLExpression::GREATEST(const SQLExpressionList & sqleList)
{
	sqlFunction(eGREATEST, sqleList);
	return *this;
}

SQLExpression & SQLExpression::IN(const SQLExpressionList & sqleList)
{
	sRight += " " + buildFunctionString(eIN, sqleList);
	return *this;
}

SQLExpression & SQLExpression::NOT_IN(const SQLExpressionList & sqleList)
{
	sRight += " " + getFunction(eNOT) + " " + buildFunctionString(eIN, sqleList);
	return *this;
}

SQLExpression & SQLExpression::ISNULL()
{
	sRight += " " + getFunction(eISNULL);
	return *this;
}

SQLExpression & SQLExpression::COALESCE(const SQLExpressionList & sqleList)
{
	sqlFunction(eCOALESCE, sqleList);
	return *this;
}

SQLExpression & SQLExpression::INTERVAL(const SQLExpressionList & sqleList)
{
	sqlFunction(eINTERVAL, sqleList);
	return *this;
}

SQLExpression & SQLExpression::LEAST(const SQLExpressionList & sqleList)
{
	sqlFunction(eLEAST, sqleList);
	return *this;
}

SQLExpression & SQLExpression::LIKE(const SQLExpression & sqle, const SQLExpression & sqleEscape)
{
	sRight += " " + getFunction(eLIKE) + " " + sqle.toString();
	if (sqleEscape) {
		sRight += " ESCAPE " + sqleEscape.toString();
	}
	return *this;
}

SQLExpression & SQLExpression::NOT_LIKE(const SQLExpression & sqle, const SQLExpression & sqleEscape)
{
	sRight += " " + getFunction(eNOT) + " " + getFunction(eLIKE) + " " + sqle.toString();
	if (sqleEscape) {
		sRight += " ESCAPE " + sqleEscape.toString();
	}
	return *this;
}

SQLExpression & SQLExpression::STRCMP(const SQLExpression & sqle)
{
	sqlFunction(eSTRCMP, { sqle });
	return *this;
}

SQLExpression & SQLExpression::DIV(const SQLExpression & sqle)
{
	generalOperation(getFunction(eDIV), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::divide(const SQLExpression & sqle)
{
	generalOperation(getFunction(eDivide), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::MOD(const SQLExpression & sqle)
{
	generalOperation(getFunction(eMOD), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::add(const SQLExpression & sqle)
{
	generalOperation(getFunction(eadd), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::multiply(const SQLExpression & sqle)
{
	generalOperation(getFunction(eMultiply), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::subtract(const SQLExpression & sqle)
{
	generalOperation(getFunction(eSubtract), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::ABS()
{
	sqlFunction(eABS, {});
	return *this;
}

SQLExpression & SQLExpression::ACOS()
{
	sqlFunction(eACOS, {});
	return *this;
}

SQLExpression & SQLExpression::ASIN()
{
	sqlFunction(eASIN, {});
	return *this;
}

SQLExpression & SQLExpression::ATAN()
{
	sqlFunction(eATAN, {});
	return *this;
}

SQLExpression & SQLExpression::ATAN(const SQLExpression & sqleY)
{
	//sExpr = "ATAN(" + sqleY.toString() + "," + sExpr + ")";
	sqlFunction(eATAN, {sqleY});
	return *this;
}

SQLExpression & SQLExpression::ATAN2(const SQLExpression & sqleY)
{
	//sExpr = "ATAN2(" + sqleY.toString() + "," + sExpr + ")";
	sqlFunction(eATAN, {sqleY});
	return *this;
}

SQLExpression & SQLExpression::CEIL()
{
	sqlFunction(eCEIL, {});
	return *this;
}

SQLExpression & SQLExpression::CONV(const SQLExpression & sqleFromBase, const SQLExpression & sqleToBase)
{
	sqlFunction(eCONV, { sqleFromBase, sqleToBase });
	return *this;
}

SQLExpression & SQLExpression::COS()
{
	sqlFunction(eCOS, {});
	return *this;
}

SQLExpression & SQLExpression::COT()
{
	sqlFunction(eCOT, {});
	return *this;
}

SQLExpression & SQLExpression::CRC32()
{
	sqlFunction(eCRC32, {});
	return *this;
}

SQLExpression & SQLExpression::DEGREES()
{
	sqlFunction(eDEGREES, {});
	return *this;
}

SQLExpression & SQLExpression::EXP()
{
	sqlFunction(eEXP, {});
	return *this;
}

SQLExpression & SQLExpression::FLOOR()
{
	sqlFunction(eFLOOR, {});
	return *this;
}

/*SQLExpression & SQLExpression::FORMAT(const SQLExpression & sqlePrecision)
{
	sqlFunction(eFORMAT, { sqlePrecision });
	return *this;
}*/

SQLExpression & SQLExpression::HEX()
{
	sqlFunction(eHEX, {});
	return *this;
}

SQLExpression & SQLExpression::LN()
{
	sqlFunction(eLN, {});
	return *this;
}

SQLExpression & SQLExpression::LOG()
{
	sqlFunction(eLOG, {});
	return *this;
}

SQLExpression & SQLExpression::LOG(const SQLExpression & sqleBase)
{
	sqlFunction(eLOG, { sqleBase });
	return *this;
}

SQLExpression & SQLExpression::LOG2()
{
	sqlFunction(eLOG2, {});
	return *this;
}

SQLExpression & SQLExpression::LOG10()
{
	sqlFunction(eLOG10, {});
	return *this;
}

SQLExpression & SQLExpression::PI()
{
	sCore = "PI()";
	clearEdges();
	return *this;
}

SQLExpression & SQLExpression::POW(const SQLExpression & sqleY)
{
	sqlFunction(ePOW, { sqleY });
	return *this;
}

SQLExpression & SQLExpression::POWER(const SQLExpression & sqleY)
{
	sqlFunction(ePOWER, { sqleY });
	return *this;
}

SQLExpression & SQLExpression::RADIANS()
{
	sqlFunction(eRADIANS, {});
	return *this;
}

/* TODO make this better */
SQLExpression & SQLExpression::RAND()
{
	sCore = buildFunctionString(eRAND, {});
	return *this;
}

SQLExpression & SQLExpression::RAND(const SQLExpression & sqleSeed)
{
	sCore = buildFunctionString(eRAND, { sqleSeed });
	return *this;
}

SQLExpression & SQLExpression::ROUND()
{
	sqlFunction(eROUND, {});
	return *this;
}

SQLExpression & SQLExpression::ROUND(const SQLExpression & sqlePrecision)
{
	sqlFunction(eROUND, { sqlePrecision });
	return *this;
}

SQLExpression & SQLExpression::SIGN()
{
	sqlFunction(eSIGN, {});
	return *this;
}
SQLExpression & SQLExpression::SIN()
{
	sqlFunction(eSIN, {});
	return *this;
}

SQLExpression & SQLExpression::SQRT()
{
	sqlFunction(eSQRT, {});
	return *this;
}

SQLExpression & SQLExpression::TAN()
{
	sqlFunction(eTAN, {});
	return *this;
}

SQLExpression & SQLExpression::TRUNCATE(const SQLExpression & sqlePrecision)
{
	sqlFunction(eTRUNCATE, {});
	return *this;
}

SQLExpression & SQLExpression::ASCII()
{
	sqlFunction(eASCII, {});
	return *this;
}

SQLExpression & SQLExpression::BIN()
{
	sqlFunction(eBIN, {});
	return *this;
}

SQLExpression & SQLExpression::BIT_LENGTH()
{
	sqlFunction(eBIT_LENGTH, {});
	return *this;
}

SQLExpression & SQLExpression::CHAR(const SQLExpression & sqleCharSet)
{
	surround(getFunction(eCHAR) + "(", " USING " + sqleCharSet.toString() + ")");
	return *this;
}

SQLExpression & SQLExpression::CHAR_LENGTH()
{
	sqlFunction(eCHAR_LENGTH, {});
	return *this;
}

SQLExpression & SQLExpression::CHARACTER_LENGTH()
{
	sqlFunction(eCHARACTER_LENGTH, {});
	return *this;
}

SQLExpression & SQLExpression::CONCAT(const SQLExpression & sqleRight)
{
	sqlFunction(eCONCAT, { sqleRight });
	return *this;
}

/*SQLExpressionList::SQLExpressionList(const SQLExpression & sqle)
{
	if (sqle) {
		push_back(sqle);
	}
}*/

SQLExpressionList::SQLExpressionList(SQLExpression params[], size_t i) : std::list<SQLExpression>(params, params + i)
{
	updateString();
}

SQLExpressionList & SQLExpressionList::updateString()
{
	sCore = "";
	size_t t = this->size();

	for (auto iter : static_cast<std::list<SQLExpression> >(*this)) {
		if (!sCore.empty()) {
			sCore += ",";
		}
		std::string sTmp = iter.toString();
		//sExpr += iter.toString();
		sCore += sTmp;
	}

	if (sCore.empty()) {
		sCore = "''";
	}
	else {
		//sExpr = "(" + sExpr + ")";
	}

	return *this;
}

std::string SQLExpressionList::getListString(bool bIncludeEmpty) const
{
	std::string sRet;
	for (auto iter : static_cast<std::list<SQLExpression> >(*this)) {
		if (iter || bIncludeEmpty) {
			if (!sRet.empty()) {
				sRet += ",";
			}
			sRet += iter.toString();
		}
	}
	return sRet;
}

int SQLExpressionList::removeEmptyExpressions()
{
	int iRet = 0;
	auto iter = begin();
	while (iter != end()) {
		if (iter->toString().empty()) {
			erase(iter++);
		}
		else {
			++iter;
		}
	}
	return 0;
}

SQLExpression & SQLExpressionList::ELT(const SQLExpression & sqleIndex)
{
	surround(getFunction(eELT) + "(" + sqleIndex.toString() + ",", ")");
	return *this;
}

SQLExpression & SQLExpressionList::FIELD(const SQLExpression & sqle)
{
	surround(getFunction(eFIELD) + "(" + sqle.toString() + ",", ")");
	return *this;
}

SQLExpressionList::SQLExpressionList() : std::list<SQLExpression>(), SQLExpression()
{
}


SQLExpression & SQLExpression::CONCAT(const SQLExpressionList & sqleRight)
{
	return CONCAT((SQLExpression)sqleRight);
}

SQLExpression & SQLExpression::CONCAT_WS(const SQLExpression & sqleSeparator, const SQLExpression & sqleRight)
{
	surround(getFunction(eCONCAT_WS) + "(" + sqleSeparator.toString() + ",", "," + sqleRight.toString() + ")");
	return *this;
}

SQLExpression & SQLExpression::CONCAT_WS(const SQLExpression & sqleSeparator, const SQLExpressionList & sqleRight)
{
	return SQLExpression::CONCAT_WS(sqleSeparator, static_cast<SQLExpression>(sqleRight));
}

SQLExpression & SQLExpression::ELT(const SQLExpressionList & sqleList)
{
	sqlFunction(eELT, sqleList);
	return *this;
}

SQLExpression &SQLExpression::EXPORT_SET(const SQLExpression & sqleON, const SQLExpression & sqleOFF, const SQLExpression & sqleSep, const SQLExpression & sqleBitNum)
{
	sqlFunction(eEXPORT_SET, { sqleON, sqleOFF, sqleSep, sqleBitNum });
	return *this;
}

SQLExpression & SQLExpression::FIELD(const SQLExpressionList & sqleList)
{
	sqlFunction(eFIELD, sqleList);
	return *this;
}

SQLExpression & SQLExpression::FIND_IN_SET(const SQLExpressionList & sqleList)
{
	sqlFunction(eFIND_IN_SET, sqleList);
	return *this;
}

SQLExpression & SQLExpression::FORMAT(const SQLExpression & sqlePrecision, const SQLExpression & sqleLocal)
{
	sqlFunction(eFORMAT, { sqlePrecision, sqleLocal });
	return *this;
}

SQLExpression & SQLExpression::FROM_BASE64()
{
	sqlFunction(eFROM_BASE64, {});
	return *this;
}

SQLExpression & SQLExpression::INSERT(const SQLExpression & sqlePos, const SQLExpression & sqleLen, const SQLExpression & sqleNewStr)
{
	sqlFunction(eINSERT, { sqlePos, sqleLen, sqleNewStr });
	return *this;
}

SQLExpression & SQLExpression::INSTR(const SQLExpression & sqleSubStr)
{
	sqlFunction(eINSTR, { sqleSubStr });
	return *this;
}

SQLExpression & SQLExpression::LCASE()
{
	sqlFunction(eLCASE, { });
	return *this;
}

SQLExpression & SQLExpression::LEFT(const SQLExpression & sqleLen)
{
	sqlFunction(eLEFT, { sqleLen });
	return *this;
}

SQLExpression & SQLExpression::LENGTH()
{
	sqlFunction(eLENGTH, { });
	return *this;
}

SQLExpression & SQLExpression::LOAD_FILE()
{
	sqlFunction(eLOAD_FILE, { });
	return *this;
}

SQLExpression & SQLExpression::LOCATE(const SQLExpression & sqleStr, const SQLExpression & sqlePos)
{
	if (sqlePos.toString().empty()) {
		sqlFunction(eLOCATE, { sqleStr });
	}
	else {
		sqlFunction(eLOCATE, { sqleStr, sqlePos });
	}

	return *this;
}

SQLExpression & SQLExpression::LOWER()
{
	sqlFunction(eLOWER, { });
	return *this;
}

SQLExpression & SQLExpression::LPAD(const SQLExpression & sqleLen, const SQLExpression & sqlePadStr)
{
	sqlFunction(eLPAD, { sqleLen, sqlePadStr });
	return *this;
}

SQLExpression & SQLExpression::LTRIM()
{
	sqlFunction(eLTRIM, { });
	return *this;
}

SQLExpression & SQLExpression::MAKE_SET(const SQLExpressionList & sqleList)
{
	SQLExpressionList sqlelTmp = sqleList;
	sqlelTmp.push_front(*this);
	sqlelTmp.updateString();
	sqlFunction(eMAKE_SET, sqlelTmp);
	return *this;
}

SQLExpression & SQLExpression::MID(const SQLExpression & sqlePos, const SQLExpression & sqleLen)
{
	sqlFunction(eMID, { sqlePos, sqleLen });
	return *this;
}

SQLExpression & SQLExpression::OCT()
{
	sqlFunction(eOCT, { });
	return *this;
}

SQLExpression & SQLExpression::OCTET_LENGTH()
{
	sqlFunction(eOCTET_LENGTH, { });
	return *this;
}

SQLExpression & SQLExpression::ORD()
{
	sqlFunction(eORD, { });
	return *this;
}

SQLExpression & SQLExpression::POSITION_IN(const SQLExpression & sqleStr)
{
	surround(getFunction(ePOSITION) + "(", " " + getFunction(eIN) + " " + sqleStr.toString() + ")");
	return *this;
}

SQLExpression & SQLExpression::QUOTE()
{
	sqlFunction(eQUOTE, { });
	return *this;
}

SQLExpression & SQLExpression::REPEAT(const SQLExpression & sqleCount)
{
	sqlFunction(eLOWER, { sqleCount });
	return *this;
}

SQLExpression & SQLExpression::REPLACE(const SQLExpression & sqleFromStr, const SQLExpression & sqleToStr)
{
	sqlFunction(eREPLACE, { sqleFromStr, sqleToStr });
	return *this;
}

SQLExpression & SQLExpression::REVERSE()
{
	sqlFunction(eREVERSE, { });
	return *this;
}

SQLExpression & SQLExpression::RIGHT(const SQLExpression & sqleLen)
{
	sqlFunction(eRIGHT, { sqleLen });
	return *this;
}

SQLExpression & SQLExpression::RPAD(const SQLExpression & sqleLen, const SQLExpression & sqlePadStr)
{
	sqlFunction(eRPAD, { sqleLen, sqlePadStr });
	return *this;
}

SQLExpression & SQLExpression::RTRIM()
{
	sqlFunction(eRTRIM, { });
	return *this;
}

SQLExpression & SQLExpression::SOUNDEX()
{
	sqlFunction(eSOUNDEX, { });
	return *this;
}

SQLExpression & SQLExpression::SOUNDS_LIKE(const SQLExpression & sqleStr)
{
	surround(getFunction(eSOUNDS_LIKE) + "("," LIKE " + sqleStr.toString() + ")");
	return *this;
}

SQLExpression & SQLExpression::SPACE()
{
	sqlFunction(eSPACE, { });
	return *this;
}

SQLExpression & SQLExpression::SUBSTR(const SQLExpression & sqlePos, const SQLExpression & sqleLen)
{
	if (sqleLen.toString().empty()) {
		sqlFunction(eSUBSTR, { sqlePos });
	}
	else {
		sqlFunction(eSUBSTR, { sqlePos, sqleLen });
	}
	return *this;
}

SQLExpression & SQLExpression::SUBSTR_FROM_FOR(const SQLExpression & sqlePos, const SQLExpression & sqleLen)
{
	if (sqleLen.toString().empty()) {
		surround(getFunction(eSUBSTR) + "(", " FROM " + sqlePos.toString() + ")");
	}
	else {
		surround(getFunction(eSUBSTR) + "(", " FROM " + sqlePos.toString() + " FOR " + sqleLen.toString() + ")");
	}
	return *this;
}

SQLExpression & SQLExpression::SUBSTRING_INDEX(const SQLExpression & sqleDelim, const SQLExpression & sqleCount)
{
	sqlFunction(eSUBSTRING_INDEX, { sqleDelim, sqleCount });
	return *this;
}

SQLExpression & SQLExpression::TO_BASE64()
{
	sqlFunction(eTO_BASE64, { });
	return *this;
}

SQLExpression & SQLExpression::TRIM(TrimDir e, const SQLExpression & sqleRemStr)
{
	std::string sTmp = getFunction(eTRIM) + "(";
	bool bFrom = true;
	switch (e) {
	case eLEADING:
		sTmp += "LEADING ";
		bFrom = true;
		break;
	case eTRAILING:
		sTmp += "TRAILING ";
		break;
	case eBOTH:
		sTmp += "BOTH ";
		break;
	case eNONE:
	default:
		bFrom = false;
		break;
	}

	if (!sqleRemStr.toString().empty()) {
		bFrom = true;
		sTmp += sqleRemStr.toString() + " ";
	}

	if (bFrom) {
		sTmp += "FROM ";
	}

	surround(sTmp, ")");
	return *this;
}

SQLExpression & SQLExpression::UCASE()
{
	sqlFunction(eUCASE, { });
	return *this;
}

SQLExpression & SQLExpression::UNHEX()
{
	sqlFunction(eUNHEX, { });
	return *this;
}

SQLExpression & SQLExpression::UPPER()
{
	sqlFunction(eUPPER, { });
	return *this;
}

SQLExpression & SQLExpression::WEIGHT_STRING(const std::vector<int>& vecLevel, const std::vector<WeightStringDir>& vecDir)
{
	sLeft = getFunction(eWEIGHT_STRING) + "(" + sLeft;
	if (!vecLevel.empty()) {
		sRight += " LEVEL ";
		for (int i = 0; i < vecLevel.size(); ++i) {
			if (i > 0) {
				sRight += ", ";
			}

			sRight += std::to_string(vecLevel[i]);
			if (i < vecDir.size()) {
				if (vecDir[i] & WeightStringDir::eDirASC) {
					sRight += " ASC ";
				}
				if (vecDir[i] & WeightStringDir::eDirDESC) {
					sRight += " DESC ";
				}
				if (vecDir[i] & WeightStringDir::eDirREVERSE) {
					sRight += " REVERSE ";
				}
			}
		}
	}

	sRight += ")";
	return *this;
}

SQLExpression & SQLExpression::WEIGHT_STRING_AS_CHAR(const SQLExpression & sqleNum, const std::vector<int>& vecLevel, const std::vector<WeightStringDir>& vecDir)
{
	sRight += " AS CHAR(" + sqleNum.toString() + ")";
	return WEIGHT_STRING(vecLevel, vecDir);
}

SQLExpression & SQLExpression::WEIGHT_STRING_AS_BINARY(const SQLExpression & sqleNum, const std::vector<int>& vecLevel, const std::vector<WeightStringDir>& vecDir)
{
	sRight += " AS BINARY(" + sqleNum.toString() + ")";
	return WEIGHT_STRING(vecLevel, vecDir);
}

std::string SQLExpression::getTimeUnit(TimeUnit e)
{
	std::string sRet;
	switch (e) {
	case SQLExpression::tuMICROSECOND:
		sRet = "MICROSECOND";
		break;
	case SQLExpression::tuSECOND:
		sRet = "SECOND";
		break;
	case SQLExpression::tuMINUTE:
		sRet = "MINUTE";
		break;
	case SQLExpression::tuHOUR:
		sRet = "HOUR";
		break;
	case SQLExpression::tuDAY:
		sRet = "DAY";
		break;
	case SQLExpression::tuWEEK:
		sRet = "WEEK";
		break;
	case SQLExpression::tuMONTH:
		sRet = "MONTH";
		break;
	case SQLExpression::tuQUARTER:
		sRet = "QUARTER";
		break;
	case SQLExpression::tuYEAR:
		sRet = "YEAR";
		break;
	case SQLExpression::tuSECOND_MICROSECOND:
		sRet = "SECOND_MICROSECOND";
		break;
	case SQLExpression::tuMINUTE_MICROSECOND:
		sRet = "MINUTE_MICROSECOND";
		break;
	case SQLExpression::tuMINUTE_SECOND:
		sRet = "MINUTE_SECOND";
		break;
	case SQLExpression::tuHOUR_MICROSECOND:
		sRet = "HOUR_MICROSECOND";
		break;
	case SQLExpression::tuHOUR_SECOND:
		sRet = "HOUR_SECOND";
		break;
	case SQLExpression::tuHOUR_MINUTE:
		sRet = "HOUR_MINUTE";
		break;
	case SQLExpression::tuDAY_MICROSECOND:
		sRet = "DAY_MICROSECOND";
		break;
	case SQLExpression::tuDAY_SECOND:
		sRet = "DAY_SECOND";
		break;
	case SQLExpression::tuDAY_MINUTE:
		sRet = "DAY_MINUTE";
		break;
	case SQLExpression::tuDAY_HOUR:
		sRet = "DAY_HOUR";
		break;
	case SQLExpression::tuYEAR_MONTH:
		sRet = "YEAR_MONTH";
		break;
	default:
		break;
	}
	return sRet;
}

SQLExpression & SQLExpression::ADDDATE(const SQLExpression & sqle, TimeUnit e)
{
	surround(getFunction(eADDDATE) + "(", " INTERVAL " + sqle.toString() + " " + getTimeUnit(e) + ")");
	return *this;
}

SQLExpression & SQLExpression::ADDTIME(const SQLExpression & sqle)
{
	sqlFunction(eADDTIME, { sqle });
	return *this;
}

SQLExpression & SQLExpression::CONVERT_TZ(const SQLExpression & sqleFromTZ, const SQLExpression & sqleToTZ)
{
	sqlFunction(eCONVERT_TZ, { sqleFromTZ, sqleToTZ });
	return *this;
}

SQLExpression & SQLExpression::CURDATE()
{
	sqlFunction(eCURDATE);
	return *this;
}

SQLExpression & SQLExpression::CURRENT_DATE()
{
	sqlFunction(eCURRENT_DATE);
	return *this;
}

SQLExpression & SQLExpression::CURRENT_TIME(const SQLExpression & sqleFSP)
{
	if (sqleFSP.toString().empty()) {
		sqlFunction(eCURRENT_TIME);
	}
	else {
		sqlFunction(eCURRENT_TIME, { sqleFSP });
	}
	return *this;
}

SQLExpression & SQLExpression::CURRENT_TIMESTAMP(const SQLExpression & sqleFSP)
{
	if (sqleFSP.toString().empty()) {
		sqlFunction(eCURRENT_TIMESTAMP);
	}
	else {
		sqlFunction(eCURRENT_TIMESTAMP, { sqleFSP });
	}
	return *this;
}

SQLExpression & SQLExpression::CURTIME(const SQLExpression & sqleFSP)
{
	if (sqleFSP.toString().empty()) {
		sqlFunction(eCURTIME);
	}
	else {
		sqlFunction(eCURTIME, { sqleFSP });
	}
	return *this;
}

SQLExpression & SQLExpression::DATE()
{
	sqlFunction(eDATE, { });
	return *this;
}

SQLExpression & SQLExpression::DATEDIFF(const SQLExpression & sqle)
{
	sqlFunction(eDATEDIFF, { sqle });
	return *this;
}

SQLExpression & SQLExpression::DATE_ADD(const SQLExpression & sqle, TimeUnit e)
{
	surround(getFunction(eDATE_ADD) + "("," " + getFunction(eINTERVAL) + " " + sqle.toString() + " " + getTimeUnit(e) + ")");
	return *this;
}

SQLExpression & SQLExpression::DATE_FORMAT(const SQLExpression & sqleFormat)
{
	sqlFunction(eDATE_FORMAT, { sqleFormat });
	return *this;
}

SQLExpression & SQLExpression::DATE_SUB(const SQLExpression & sqle, TimeUnit e)
{
	surround(getFunction(eDATE_SUB) + "(", " INTERVAL " + sqle.toString() + " " + getTimeUnit(e) + ")");
	return *this;
}

SQLExpression & SQLExpression::DAY()
{
	sqlFunction(eDAY, { });
	return *this;
}

SQLExpression & SQLExpression::DAYNAME()
{
	sqlFunction(eDAYNAME, { });
	return *this;
}

SQLExpression & SQLExpression::DAYOFMONTH()
{
	sqlFunction(eDAYOFMONTH, { });
	return *this;
}

SQLExpression & SQLExpression::DAYOFWEEK()
{
	sqlFunction(eDAYOFWEEK, { });
	return *this;
}

SQLExpression & SQLExpression::DAYOFYEAR()
{
	sqlFunction(eDAYOFYEAR, { });
	return *this;
}

SQLExpression & SQLExpression::EXTRACT(TimeUnit e)
{
	surround(getFunction(eEXTRACT) + "(" + getTimeUnit(e) + " FROM ", ")");
	return *this;
}

SQLExpression & SQLExpression::FROM_DAYS()
{
	sqlFunction(eFROM_DAYS, { });
	return *this;
}

SQLExpression & SQLExpression::FROM_UNIXTIME()
{
	sqlFunction(eFROM_UNIXTIME, { });
	return *this;
}

SQLExpression & SQLExpression::GET_FORMAT(Function e)
{
	surround(getFunction(eGET_FORMAT) + "(" + getFunction(e) + ", ", ")");
	return *this;
}

SQLExpression & SQLExpression::HOUR()
{
	sqlFunction(eHOUR, { });
	return *this;
}

SQLExpression & SQLExpression::LAST_DAY()
{
	sqlFunction(eLAST_DAY, { });
	return *this;
}

SQLExpression & SQLExpression::LOCALTIME(const SQLExpression & sqleFSP)
{
	if (sqleFSP.toString().empty()) {
		sqlFunction(eLOCALTIME);
	}
	else {
		sqlFunction(eLOCALTIME, { sqleFSP });
	}
	return *this;
}

SQLExpression & SQLExpression::LOCALTIMESTAMP(const SQLExpression & sqleFSP)
{
	if (sqleFSP.toString().empty()) {
		sqlFunction(eLOCALTIMESTAMP);
	}
	else {
		sqlFunction(eLOCALTIMESTAMP, { sqleFSP });
	}
	return *this;
}

SQLExpression & SQLExpression::MAKEDATE(const SQLExpression & sqleDayOfYear)
{
	sqlFunction(eMAKEDATE, { sqleDayOfYear });
	return *this;
}

SQLExpression & SQLExpression::MAKETIME(const SQLExpression & sqleMinute, const SQLExpression & sqleSecond)
{
	sqlFunction(eMAKETIME, { sqleMinute, sqleSecond });
	return *this;
}

SQLExpression & SQLExpression::MICROSECOND()
{
	sqlFunction(eMICROSECOND, { });
	return *this;
}

SQLExpression & SQLExpression::MINUTE()
{
	sqlFunction(eMINUTE, { });
	return *this;
}

SQLExpression & SQLExpression::MONTH()
{
	sqlFunction(eMONTH, { });
	return *this;
}

SQLExpression & SQLExpression::MONTHNAME()
{
	sqlFunction(eMONTHNAME, { });
	return *this;
}

SQLExpression & SQLExpression::NOW(const SQLExpression & sqleFSP)
{
	if (sqleFSP.toString().empty()) {
		sqlFunction(eNOW);
	}
	else {
		sqlFunction(eNOW, { sqleFSP });
	}
	return *this;
}

SQLExpression & SQLExpression::PERIOD_ADD(const SQLExpression & sqle)
{
	sqlFunction(ePERIOD_ADD, { sqle });
	return *this;
}

SQLExpression & SQLExpression::PERIOD_DIFF(const SQLExpression & sqle)
{
	sqlFunction(ePERIOD_DIFF, { });
	return *this;
}

SQLExpression & SQLExpression::QUARTER()
{
	sqlFunction(eQUARTER, { });
	return *this;
}

SQLExpression & SQLExpression::SECOND()
{
	sqlFunction(eSECOND, { });
	return *this;
}

SQLExpression & SQLExpression::SEC_TO_TIME()
{
	sqlFunction(eSEC_TO_TIME, { });
	return *this;
}

SQLExpression & SQLExpression::STR_TO_DATE()
{
	sqlFunction(eSTR_TO_DATE, { });
	return *this;
}

SQLExpression & SQLExpression::SUBDATE(const SQLExpression & sqle, TimeUnit e)
{
	surround(getFunction(eSUBDATE) + "(", " INTERVAL " + sqle.toString() + " " + getTimeUnit(e) + ")");
	return *this;
}

SQLExpression & SQLExpression::SUBTIME(const SQLExpression & sqle)
{
	sqlFunction(eSUBTIME, { sqle });
	return *this;
}

SQLExpression & SQLExpression::SYSDATE(const SQLExpression & sqleFSP)
{
	if (sqleFSP.toString().empty()) {
		sqlFunction(eSYSDATE);
	}
	else {
		sqlFunction(eSYSDATE, { sqleFSP });
	}
	return *this;
}

SQLExpression & SQLExpression::TIME()
{
	sqlFunction(eTIME, { });
	return *this;
}

SQLExpression & SQLExpression::TIMEDIFF(const SQLExpression & sqle)
{
	sqlFunction(eTIMEDIFF, { sqle });
	return *this;
}

SQLExpression & SQLExpression::TIMESTAMP(const SQLExpression & sqle)
{
	if (sqle) {
		sqlFunction(eTIMESTAMP, { sqle });
	}
	else {
		sqlFunction(eTIMESTAMP, { });
	}
	return *this;
}

SQLExpression & SQLExpression::TIMESTAMPADD(TimeUnit e, const SQLExpression & sqleInterval)
{
	surround(getFunction(eTIMESTAMPADD) + "(" + getTimeUnit(e) + ", ", ", " + sqleInterval.toString() + ")");
	return *this;
}

SQLExpression & SQLExpression::TIMESTAMPDIFF(TimeUnit e, const SQLExpression & sqle)
{
	surround(getFunction(eTIMESTAMPDIFF) + "(" + getTimeUnit(e) + ", ", ", " + sqle.toString() + ")");
	return *this;
}

SQLExpression & SQLExpression::TIME_FORMAT(const SQLExpression & sqle)
{
	sqlFunction(eTIME_FORMAT, { sqle });
	return *this;
}

SQLExpression & SQLExpression::TIME_TO_SEC()
{
	sqlFunction(eTIME_TO_SEC, { });
	return *this;
}

SQLExpression & SQLExpression::TO_DAYS()
{
	sqlFunction(eTO_DAYS, { });
	return *this;
}

SQLExpression & SQLExpression::TO_SECONDS()
{
	sqlFunction(eTO_SECONDS, { });
	return *this;
}

SQLExpression & SQLExpression::UNIX_TIMESTAMP(const SQLExpression & sqle)
{
	if (sqle) {
		sqlFunction(eUNIX_TIMESTAMP, { sqle });
	}
	else {
		sqlFunction(eUNIX_TIMESTAMP, { });
	}
	return *this;
}

SQLExpression & SQLExpression::UTC_DATE()
{
	sqlFunction(eUTC_DATE);
	return *this;
}

SQLExpression & SQLExpression::UTC_TIME(const SQLExpression & sqleFSP)
{
	if (sqleFSP) {
		sqlFunction(eUTC_TIME, { sqleFSP });
	}
	else {
		sqlFunction(eUTC_TIME, { });
	}
	return *this;
}

SQLExpression & SQLExpression::UTC_TIMESTAMP(const SQLExpression & sqleFSP)
{
	if (sqleFSP) {
		sqlFunction(eUTC_TIMESTAMP, { sqleFSP });
	}
	else {
		sqlFunction(eUTC_TIMESTAMP, { });
	}
	return *this;
}

SQLExpression & SQLExpression::WEEK(const SQLExpression & sqleMode)
{
	if (sqleMode) {
		sqlFunction(eWEEK, { sqleMode });
	}
	else {
		sqlFunction(eWEEK, { });
	}
	return *this;
}

SQLExpression & SQLExpression::WEEKDAY()
{
	sqlFunction(eWEEKDAY, { });
	return *this;
}

SQLExpression & SQLExpression::WEEKOFYEAR()
{
	sqlFunction(eWEEKOFYEAR, { });
	return *this;
}

SQLExpression & SQLExpression::YEAR()
{
	sqlFunction(eYEAR, { });
	return *this;
}

SQLExpression & SQLExpression::YEARWEEK()
{
	sqlFunction(eYEARWEEK, { });
	return *this;
}

SQLExpression & SQLExpression::EXTRACTVALUE(const SQLExpression & sqle)
{
	sqlFunction(eExtractValue, { });
	return *this;
}

SQLExpression & SQLExpression::UPDATEXML(const SQLExpression & sqle)
{
	sqlFunction(eUpdateXML, { });
	return *this;
}

SQLExpression & SQLExpression::BIT_COUNT()
{
	sqlFunction(eBIT_COUNT, { });
	return *this;
}

SQLExpression & SQLExpression::BitwiseAnd(const SQLExpression &sqle)
{
	generalOperation(getFunction(eBitwiseAnd), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::BitwiseInvert()
{
	generalOperation(getFunction(eBitwiseInvert), true);
	return *this;
}

SQLExpression & SQLExpression::BitwiseOr(const SQLExpression & sqle)
{
	generalOperation(getFunction(eBitwiseOr), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::BitwiseXor(const SQLExpression & sqle)
{
	generalOperation(getFunction(eBitwiseXor), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::LeftShift(const SQLExpression & sqle)
{
	generalOperation(getFunction(eLeftShift), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::RightShift(const SQLExpression & sqle)
{
	generalOperation(getFunction(eRightShift), sqle.toString());
	return *this;
}

SQLExpression & SQLExpression::AES_DECRYPT(const SQLExpression & sqleKey, const SQLExpression & sqleInitVec)
{
	if (sqleInitVec) {
		sqlFunction(eAES_DECRYPT, { sqleKey, sqleInitVec });
	}
	else {
		sqlFunction(eAES_DECRYPT, { sqleKey });
	}
	return *this;
}

SQLExpression & SQLExpression::AES_ENCRYPT(const SQLExpression & sqleKey, const SQLExpression & sqleInitVec)
{
	if (sqleInitVec) {
		sqlFunction(eAES_ENCRYPT, { sqleKey, sqleInitVec });
	}
	else {
		sqlFunction(eAES_ENCRYPT, { sqleKey });
	}
	return *this;
}

SQLExpression & SQLExpression::COMPRESS()
{
	sqlFunction(eCOMPRESS, { });
	return *this;
}

SQLExpression & SQLExpression::DECODE(const SQLExpression &sqlePass)
{
	if (sqlePass) {
		sqlFunction(eAES_ENCRYPT, { sqlePass });
	}
	else {
		sqlFunction(eAES_ENCRYPT, { });
	}
	return *this;
}

SQLExpression & SQLExpression::DES_DECRYPT(const SQLExpression & sqleKey)
{
	if (sqleKey) {
		sqlFunction(eAES_ENCRYPT, { sqleKey });
	}
	else {
		sqlFunction(eAES_ENCRYPT, { });
	}
	return *this;
}

SQLExpression & SQLExpression::DES_ENCRYPT(const SQLExpression & sqleKey)
{
	if (sqleKey) {
		sqlFunction(eAES_DECRYPT, { sqleKey });
	}
	else {
		sqlFunction(eAES_DECRYPT, { });
	}
	return *this;
}

SQLExpression & SQLExpression::ENCODE(const SQLExpression & sqlePass)
{
	if (sqlePass) {
		sqlFunction(eENCODE, { sqlePass });
	}
	else {
		sqlFunction(eENCODE, { });
	}
	return *this;
}

SQLExpression & SQLExpression::ENCRYPT(const SQLExpression & sqleSalt)
{
	if (sqleSalt) {
		sqlFunction(eENCRYPT, { sqleSalt });
	}
	else {
		sqlFunction(eENCRYPT, { });
	}
	return *this;
}

SQLExpression & SQLExpression::MD5()
{
	sqlFunction(eMD5, { });
	return *this;
}

SQLExpression & SQLExpression::OLD_PASSWORD()
{
	sqlFunction(eOLD_PASSWORD, { });
	return *this;
}

SQLExpression & SQLExpression::PASSWORD()
{
	sqlFunction(ePASSWORD, { });
	return *this;
}

SQLExpression & SQLExpression::RANDOM_BYTES()
{
	sqlFunction(eRANDOM_BYTES, { });
	return *this;
}

SQLExpression & SQLExpression::SHA1()
{
	sqlFunction(eSHA1, { });
	return *this;
}

SQLExpression & SQLExpression::SHA2(const SQLExpression & sqleHashLen)
{
	sqlFunction(eSHA2, { sqleHashLen });
	return *this;
}

SQLExpression & SQLExpression::UNCOMPRESS()
{
	sqlFunction(eUNCOMPRESS, { });
	return *this;
}

SQLExpression & SQLExpression::VALIDATE_PASSWORD_STRENGTH()
{
	sqlFunction(eVALIDATE_PASSWORD_STRENGTH, { });
	return *this;
}

SQLExpression & SQLExpression::BENCHMARK(const SQLExpression & sqleCount)
{
	sqlFunction(eBENCHMARK, { sqleCount });
	return *this;
}

SQLExpression & SQLExpression::CHARSET()
{
	sqlFunction(eCHARSET, { });
	return *this;
}

SQLExpression & SQLExpression::COERCIBILITY()
{
	sqlFunction(eCOERCIBILITY, { });
	return *this;
}

SQLExpression & SQLExpression::COLLATION()
{
	sqlFunction(eCOLLATION, { });
	return *this;
}

SQLExpression & SQLExpression::CONNECTION_ID()
{
	sqlFunction(eCONNECTION_ID);
	return *this;
}

SQLExpression & SQLExpression::CURRENT_USER()
{
	sqlFunction(eCURRENT_USER);
	return *this;
}

SQLExpression & SQLExpression::DATABASE()
{
	sqlFunction(eDATABASE);
	return *this;
}

SQLExpression & SQLExpression::FOUND_ROWS()
{
	sqlFunction(eFOUND_ROWS);
	return *this;
}

SQLExpression & SQLExpression::LAST_INSERT_ID(const SQLExpression & sqle)
{
	if (sqle) {
		sqlFunction(eLAST_INSERT_ID, { sqle });
	}
	else {
		sqlFunction(eLAST_INSERT_ID);
	}
	return *this;
}

SQLExpression & SQLExpression::ROW_COUNT()
{
	sqlFunction(eROW_COUNT);
	return *this;
}

SQLExpression & SQLExpression::SCHEMA()
{
	sqlFunction(eSCHEMA);
	return *this;
}

SQLExpression & SQLExpression::SESSION_USER()
{
	sqlFunction(eSESSION_USER);
	return *this;
}

SQLExpression & SQLExpression::SYSTEM_USER()
{
	sqlFunction(eSYSTEM_USER);
	return *this;
}

SQLExpression & SQLExpression::USER()
{
	sqlFunction(eUSER);
	return *this;
}

SQLExpression & SQLExpression::VERSION()
{
	sqlFunction(eVERSION);
	return *this;
}

SQLExpression & SQLExpression::JSON_QUOTE()
{
	sqlFunction(eJSON_QUOTE, { });
	return *this;
}

SQLExpression & SQLExpression::JSON_CONTAINS(const SQLExpression & sqleCandidate, const SQLExpression & sqlePath)
{
	if (sqlePath) {
		sqlFunction(eJSON_QUOTE, { sqleCandidate, sqlePath });
	}
	else {
		sqlFunction(eJSON_CONTAINS, { sqleCandidate });
	}
	return *this;
}



SQLExpression & SQLExpression::JSON_ExtractOp(const SQLExpression & sqle)
{
	sLeft += getFunction(eJSON_ExtractOp) + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::JSON_UnquoteExtractOp(const SQLExpression & sqle)
{
	sLeft += getFunction(eJSON_UnquoteExtractOp) + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::JSON_KEYS(const SQLExpression & sqlePath)
{
	if (sqlePath) {
		sqlFunction(eJSON_KEYS, { sqlePath });
	}
	else {
		sqlFunction(eJSON_KEYS, { });
	}
	return *this;
}

SQLExpression & SQLExpression::JSON_SEARCH(const SQLExpression & sqleOneAll, const SQLExpression & sqlePath)
{
	if (sqlePath) {
		sqlFunction(eJSON_SEARCH, { sqleOneAll, sqlePath });
	}
	else {
		sqlFunction(eJSON_SEARCH, { sqleOneAll });
	}
	return *this;
}

SQLExpression & SQLExpression::JSON_APPEND(const SQLExpressionList & sqlelPathValPairs)
{
	sqlFunction(eJSON_APPEND, sqlelPathValPairs);
	return *this;
}

SQLExpression & SQLExpression::JSON_ARRAY_APPEND(const SQLExpressionList & sqlelPathValPairs)
{
	sqlFunction(eJSON_ARRAY_APPEND, sqlelPathValPairs);
	return *this;
}

SQLExpression & SQLExpression::JSON_ARRAY_INSERT(const SQLExpressionList & sqlelPathValPairs)
{
	sqlFunction(eJSON_ARRAY_INSERT, sqlelPathValPairs);
	return *this;
}

SQLExpression & SQLExpression::JSON_INSERT(const SQLExpressionList & sqlelPathValPairs)
{
	sqlFunction(eJSON_INSERT, sqlelPathValPairs);
	return *this;
}

SQLExpression & SQLExpression::JSON_MERGE(const SQLExpressionList & sqleDocs)
{
	sqlFunction(eJSON_MERGE, sqleDocs);
	return *this;
}

SQLExpression & SQLExpression::JSON_MERGE_PATCH(const SQLExpressionList & sqleDocs)
{
	sqlFunction(eJSON_MERGE_PATCH, sqleDocs);
	return *this;
}

SQLExpression & SQLExpression::JSON_MERGE_PRESERVE(const SQLExpressionList & sqleDocs)
{
	sqlFunction(eJSON_MERGE_PRESERVE, sqleDocs);
	return *this;
}

SQLExpression & SQLExpression::JSON_REMOVE(const SQLExpressionList & sqleDocs)
{
	sqlFunction(eJSON_REMOVE, sqleDocs);
	return *this;
}

SQLExpression & SQLExpression::JSON_REPLACE(const SQLExpressionList & sqlelPathValPairs)
{
	sqlFunction(eJSON_REPLACE, sqlelPathValPairs);
	return *this;
}

SQLExpression & SQLExpression::JSON_SET(const SQLExpressionList & sqlelPathValPairs)
{
	sqlFunction(eJSON_SET, sqlelPathValPairs);
	return *this;
}

SQLExpression & SQLExpression::JSON_UNQUOTE()
{
	sqlFunction(eJSON_UNQUOTE, { });
	return *this;
}

SQLExpression & SQLExpression::JSON_DEPTH()
{
	sqlFunction(eJSON_DEPTH, { });
	return *this;
}

SQLExpression & SQLExpression::JSON_LENGTH(const SQLExpression & sqlePath)
{
	if (sqlePath) {
		sqlFunction(eJSON_LENGTH, { sqlePath });
	}
	else {
		sqlFunction(eJSON_LENGTH, { });
	}
	return *this;
}

SQLExpression & SQLExpression::JSON_TYPE()
{
	sqlFunction(eJSON_TYPE, { });
	return *this;
}

SQLExpression & SQLExpression::JSON_VALID()
{
	sqlFunction(eJSON_VALID, { });
	return *this;
}

SQLExpression & SQLExpression::JSON_PRETTY()
{
	sqlFunction(eJSON_PRETTY, { });
	return *this;
}

SQLExpression & SQLExpression::JSON_STORAGE_SIZE()
{
	sqlFunction(eJSON_STORAGE_SIZE, { });
	return *this;
}

SQLExpression & SQLExpression::GTID_SET(const SQLExpression & sqleSubSet)
{
	sqlFunction(eGTID_SUBSET, { sqleSubSet });
	return *this;
}

SQLExpression & SQLExpression::GTID_SUBSET(const SQLExpression & sqleSet)
{
	sqlFunction(eGTID_SUBSET, { sqleSet });
	return *this;
}

SQLExpression & SQLExpression::GTID_SUBTRACT(const SQLExpression & sqleSubSet)
{
	sqlFunction(eGTID_SUBTRACT, { sqleSubSet });
	return *this;
}

SQLExpression & SQLExpression::WAIT_FOR_EXECUTED_GTID_SET(const SQLExpression & sqleTimeout)
{
	if (sqleTimeout) {
		sqlFunction(eWAIT_FOR_EXECUTED_GTID_SET, { sqleTimeout });
	}
	else {
		sqlFunction(eWAIT_FOR_EXECUTED_GTID_SET, { });
	}

	return *this;
}

SQLExpression & SQLExpression::WAIT_UNTIL_SQL_THREAD_AFTER_GTIDS(const SQLExpression & sqleTimeout, const SQLExpression & sqleChannel)
{
	SQLExpressionList sqlelTmp = { };
	if (sqleTimeout) {
		sqlelTmp.push_back(sqleTimeout);
	}

	if (sqleChannel) {
		sqlelTmp.push_back(sqleChannel);
	}
	
	sqlelTmp.updateString();
	sqlFunction(eWAIT_UNTIL_SQL_THREAD_AFTER_GTIDS, sqlelTmp);
	return *this;
}

SQLExpression & SQLExpression::ST_GeomCollFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_GeomCollFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_GeometryCollectionFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_GeometryCollectionFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_GeomCollFromTxt(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_GeomCollFromTxt, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::GeomCollFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eGeomCollFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::GeometryCollectionFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eGeometryCollectionFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_GeomFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_GeomFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_GeometryFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_GeometryFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::GeomFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eGeomFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::GeometryFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eGeometryFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_LineFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_LineFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_LineStringFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_LineStringFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::LineFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eLineFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::LineStringFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eLineStringFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_MLineFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_MLineFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_MultiLineStringFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_MultiLineStringFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::MLineFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eMLineFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::MultiLineStringFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eMultiLineStringFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_MPointFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_MPointFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_MultiPointFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_MultiPointFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::MPointFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eMPointFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::MultiPointFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eMultiPointFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_MPolyFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_MPolyFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_MultiPolygonFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_MultiPolygonFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::MPolyFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eMPolyFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::MultiPolygonFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eMultiPolygonFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_PointFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_PointFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::PointFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(ePointFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_PolyFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_PolyFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_PolygonFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_PolygonFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::PolyFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(ePolyFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::PolygonFromText(const SQLExpression & sqleSrid)
{
	sqlFunction(ePolygonFromText, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_GeomCollFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_GeomCollFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_GeometryCollectionFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_GeometryCollectionFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::GeomCollFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eGeomCollFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::GeometryCollectionFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eGeometryCollectionFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_GeomFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_GeomFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_GeometryFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_GeometryFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::GeomFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eGeomFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::GeometryFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eGeometryFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_LineFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_LineFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_LineStringFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_LineStringFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::LineFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eLineFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::LineStringFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eLineStringFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_MLineFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_MLineFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_MultiLineStringFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_MultiLineStringFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::MLineFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eMLineFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::MultiLineStringFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eMultiLineStringFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_MPointFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_MPointFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_MultiPointFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_MultiPointFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::MPointFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eMPointFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::MultiPointFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eMultiPointFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_MPolyFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_MPolyFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_MultiPolygonFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_MultiPolygonFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::MPolyFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eMPolyFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::MultiPolygonFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eMultiPolygonFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_PointFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_PointFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::PointFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(ePointFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_PolyFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_PolyFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::ST_PolygonFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(eST_PolygonFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::PolyFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(ePolyFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::PolygonFromWKB(const SQLExpression & sqleSrid)
{
	sqlFunction(ePolygonFromWKB, { sqleSrid });
	return *this;
}

SQLExpression & SQLExpression::GeometryCollection(const SQLExpressionList & sqlelGeoms)
{
	sqlFunction(eGeometryCollection, sqlelGeoms);
	return *this;
}

SQLExpression & SQLExpression::LineString(const SQLExpressionList & sqlelPoints)
{
	sqlFunction(eLineString, sqlelPoints);
	return *this;
}

SQLExpression & SQLExpression::MultiLineString(const SQLExpressionList & sqlelLines)
{
	sqlFunction(eMultiLineString, sqlelLines);
	return *this;
}

SQLExpression & SQLExpression::MultiPoint(const SQLExpressionList & sqlelPoints)
{
	sqlFunction(eMultiPoint, sqlelPoints);
	return *this;
}

SQLExpression & SQLExpression::MultiPolygon(const SQLExpressionList & sqlelPolygons)
{
	sqlFunction(eMultiPolygon, sqlelPolygons);
	return *this;
}

SQLExpression & SQLExpression::Point(const SQLExpression & sqleY)
{
	sqlFunction(ePoint, { sqleY });
	return *this;
}

SQLExpression & SQLExpression::Polygon(const SQLExpressionList & sqlelLines)
{
	sqlFunction(ePolygon, sqlelLines);
	return *this;
}

SQLExpression & SQLExpression::ST_AsBinary()
{
	sqlFunction(eST_AsBinary, {});
	return *this;
}

SQLExpression & SQLExpression::ST_AsWKB()
{
	sqlFunction(eST_AsWKB, {});
	return *this;
}

SQLExpression & SQLExpression::AsBinary()
{
	sqlFunction(eAsBinary, {});
	return *this;
}

SQLExpression & SQLExpression::AsWKB()
{
	sqlFunction(eAsWKB, {});
	return *this;
}

SQLExpression & SQLExpression::ST_AsText()
{
	sqlFunction(eST_AsText, {});
	return *this;
}

SQLExpression & SQLExpression::ST_AsWKT()
{
	sqlFunction(eST_AsWKT, {});
	return *this;
}

SQLExpression & SQLExpression::AsText()
{
	sqlFunction(eAsText, {});
	return *this;
}

SQLExpression & SQLExpression::AsWKT()
{
	sqlFunction(eAsWKT, {});
	return *this;
}

SQLExpression & SQLExpression::Dimension()
{
	sqlFunction(eDimension, {});
	return *this;
}

SQLExpression & SQLExpression::ST_Dimension()
{
	sqlFunction(eST_Dimension, {});
	return *this;
}

SQLExpression & SQLExpression::Envelope()
{
	sqlFunction(eEnvelope, {});
	return *this;
}

SQLExpression & SQLExpression::ST_Envelope()
{
	sqlFunction(eST_Envelope, {});
	return *this;
}

SQLExpression & SQLExpression::GeometryType()
{
	sqlFunction(eGeometryType, {});
	return *this;
}

SQLExpression & SQLExpression::ST_GeometryType()
{
	sqlFunction(eST_GeometryType, {});
	return *this;
}

SQLExpression & SQLExpression::IsEmpty()
{
	sqlFunction(eIsEmpty, {});
	return *this;
}

SQLExpression & SQLExpression::ST_IsEmpty()
{
	sqlFunction(eST_IsEmpty, {});
	return *this;
}

SQLExpression & SQLExpression::IsSimple()
{
	sqlFunction(eIsSimple, {});
	return *this;
}

SQLExpression & SQLExpression::ST_IsSimple()
{
	sqlFunction(eST_IsSimple, {});
	return *this;
}

SQLExpression & SQLExpression::SRID()
{
	sqlFunction(eSRID, {});
	return *this;
}

SQLExpression & SQLExpression::ST_SRID()
{
	sqlFunction(eST_SRID, {});
	return *this;
}

SQLExpression & SQLExpression::ST_Y()
{
	sqlFunction(eST_Y, {});
	return *this;
}

SQLExpression & SQLExpression::Y()
{
	sqlFunction(eY, {});
	return *this;
}

SQLExpression & SQLExpression::ST_X()
{
	sqlFunction(eST_X, {});
	return *this;
}

SQLExpression & SQLExpression::X()
{
	sqlFunction(eX, {});
	return *this;
}

SQLExpression & SQLExpression::ST_StartPoint()
{
	sqlFunction(eST_StartPoint, {});
	return *this;
}

SQLExpression & SQLExpression::StartPoint()
{
	sqlFunction(eStartPoint, {});
	return *this;
}

SQLExpression & SQLExpression::ST_EndPoint()
{
	sqlFunction(eST_EndPoint, {});
	return *this;
}

SQLExpression & SQLExpression::EndPoint()
{
	sqlFunction(eEndPoint, {});
	return *this;
}

SQLExpression & SQLExpression::ST_Length()
{
	sqlFunction(eST_Length, {});
	return *this;
}

SQLExpression & SQLExpression::ST_GLength()
{
	sqlFunction(eST_GLength, {});
	return *this;
}

SQLExpression & SQLExpression::GLength()
{
	sqlFunction(eGLength, {});
	return *this;
}

SQLExpression & SQLExpression::ST_IsClosed()
{
	sqlFunction(eST_IsClosed, {});
	return *this;
}

SQLExpression & SQLExpression::IsClosed()
{
	sqlFunction(eIsClosed, {});
	return *this;
}

SQLExpression & SQLExpression::ST_NumPoints()
{
	sqlFunction(eST_NumPoints, {});
	return *this;
}

SQLExpression & SQLExpression::NumPoints()
{
	sqlFunction(eNumPoints, {});
	return *this;
}

SQLExpression & SQLExpression::ST_PointN(SQLExpression & sqleN)
{
	sqlFunction(eST_PointN, { sqleN });
	return *this;
}

SQLExpression & SQLExpression::PointN(SQLExpression & sqleN)
{
	sqlFunction(ePointN, { sqleN });
	return *this;
}

SQLExpression & SQLExpression::ST_Area()
{
	sqlFunction(eST_Area, {});
	return *this;
}

SQLExpression & SQLExpression::Area()
{
	sqlFunction(eArea, {});
	return *this;
}

SQLExpression & SQLExpression::ST_Centroid()
{
	sqlFunction(eST_Centroid, {});
	return *this;
}

SQLExpression & SQLExpression::Centroid()
{
	sqlFunction(eCentroid, {});
	return *this;
}

SQLExpression & SQLExpression::ST_ExteriorRing()
{
	sqlFunction(eST_ExteriorRing, {});
	return *this;
}

SQLExpression & SQLExpression::ExteriorRing()
{
	sqlFunction(eExteriorRing, {});
	return *this;
}

SQLExpression & SQLExpression::ST_InteriorRingN(const SQLExpression & sqleN)
{
	sqlFunction(eST_InteriorRingN, { sqleN });
	return *this;
}

SQLExpression & SQLExpression::InteriorRingN(const SQLExpression & sqleN)
{
	sqlFunction(eInteriorRingN, { sqleN });
	return *this;
}

SQLExpression & SQLExpression::ST_NumInteriorRings()
{
	sqlFunction(eNumInteriorRings, {});
	return *this;
}

SQLExpression & SQLExpression::NumInteriorRings()
{
	sqlFunction(eNumInteriorRings, {});
	return *this;
}

SQLExpression & SQLExpression::ST_GeometryN(const SQLExpression & sqleN)
{
	sqlFunction(eST_GeometryN, { sqleN });
	return *this;
}

SQLExpression & SQLExpression::GeometryN(const SQLExpression & sqleN)
{
	sqlFunction(eGeometryN, { sqleN });
	return *this;
}

SQLExpression & SQLExpression::ST_NumGeometries()
{
	sqlFunction(eST_NumGeometries, {});
	return *this;
}

SQLExpression & SQLExpression::NumGeometries()
{
	sqlFunction(eNumGeometries, {});
	return *this;
}

SQLExpression & SQLExpression::ST_Buffer(const SQLExpression & sqleD, const SQLExpressionList & sqlelStrategies)
{
	sqlFunction(eST_Buffer, {sqleD, sqlelStrategies});
	return *this;
}

SQLExpression & SQLExpression::Buffer(const SQLExpression & sqleD, const SQLExpressionList & sqlelStrategies)
{
	sqlFunction(eBuffer, {sqleD, sqlelStrategies});
	return *this;
}

SQLExpression & SQLExpression::ST_ConvexHull()
{
	sqlFunction(eST_ConvexHull, {});
	return *this;
}

SQLExpression & SQLExpression::ConvexHull()
{
	sqlFunction(eConvexHull, {});
	return *this;
}

SQLExpression & SQLExpression::ST_Buffer_Strategy(const SQLExpression & sqlePoints)
{
	sqlFunction(eST_Buffer_Strategy, { sqlePoints });
	return *this;
}

SQLExpression & SQLExpression::ST_Difference(const SQLExpression & sqleG2)
{
	sqlFunction(eST_Difference, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::ST_Intersection(const SQLExpression & sqleG2)
{
	sqlFunction(eST_Intersection, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::ST_SymDifference(const SQLExpression & sqleG2)
{
	sqlFunction(eST_SymDifference, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::ST_Union(const SQLExpression & sqleG2)
{
	sqlFunction(eST_Union, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::ST_Crosses(const SQLExpression & sqleG2)
{
	sqlFunction(eST_Crosses, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::Crosses(const SQLExpression & sqleG2)
{
	sqlFunction(eCrosses, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::ST_Distance(const SQLExpression & sqleG2)
{
	sqlFunction(eST_Distance, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::Distance(const SQLExpression & sqleG2)
{
	sqlFunction(eDistance, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::ST_Contains(const SQLExpression & sqleG2)
{
	sqlFunction(eST_Contains, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::Contains(const SQLExpression & sqleG2)
{
	sqlFunction(eContains, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::ST_Disjoint(const SQLExpression & sqleG2)
{
	sqlFunction(eST_Disjoint, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::Disjoint(const SQLExpression & sqleG2)
{
	sqlFunction(eDisjoint, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::ST_Equals(const SQLExpression & sqleG2)
{
	sqlFunction(eST_Equals, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::Equals(const SQLExpression & sqleG2)
{
	sqlFunction(eEquals, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::ST_Intersects(const SQLExpression & sqleG2)
{
	sqlFunction(eST_Intersects, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::Intersects(const SQLExpression & sqleG2)
{
	sqlFunction(eIntersects, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::ST_Overlaps(const SQLExpression & sqleG2)
{
	sqlFunction(eST_Overlaps, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::Overlaps(const SQLExpression & sqleG2)
{
	sqlFunction(eOverlaps, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::ST_Within(const SQLExpression & sqleG2)
{
	sqlFunction(eST_Within, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::Within(const SQLExpression & sqleG2)
{
	sqlFunction(eWithin, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::ST_Touches(const SQLExpression & sqleG2)
{
	sqlFunction(eST_Touches, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::Touches(const SQLExpression & sqleG2)
{
	sqlFunction(eST_Touches, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::MBRContains(const SQLExpression & sqleG2)
{
	sqlFunction(eMBRContains, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::MBRCoveredBy(const SQLExpression & sqleG2)
{
	sqlFunction(eMBRCoveredBy, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::MBRCovers(const SQLExpression & sqleG2)
{
	sqlFunction(eMBRCovers, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::MBRDisjoint(const SQLExpression & sqleG2)
{
	sqlFunction(eMBRDisjoint, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::MBREqual(const SQLExpression & sqleG2)
{
	sqlFunction(eMBREqual, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::MBREquals(const SQLExpression & sqleG2)
{
	sqlFunction(eMBREquals, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::MBRIntersects(const SQLExpression & sqleG2)
{
	sqlFunction(eMBRIntersects, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::MBROverlaps(const SQLExpression & sqleG2)
{
	sqlFunction(eMBROverlaps, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::MBRTouches(const SQLExpression & sqleG2)
{
	sqlFunction(eMBRTouches, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::MBRWithin(const SQLExpression & sqleG2)
{
	sqlFunction(eMBRWithin, { sqleG2 });
	return *this;
}

SQLExpression & SQLExpression::ST_GeoHash(const SQLExpressionList & sqlel)
{
	sqlFunction(eST_GeoHash, sqlel );
	return *this;
}

SQLExpression & SQLExpression::ST_LatFromGeoHash()
{
	sqlFunction(eST_LatFromGeoHash, {});
	return *this;
}

SQLExpression & SQLExpression::ST_LongFromGeoHash()
{
	sqlFunction(eST_LongFromGeoHash, {});
	return *this;
}

SQLExpression & SQLExpression::ST_PointFromGeoHash(const SQLExpression & sqle)
{
	sqlFunction(eST_PointFromGeoHash, {});
	return *this;
}

SQLExpression & SQLExpression::ST_AsGeoJSON(const SQLExpressionList & sqlel)
{
	sqlFunction(eST_AsGeoJSON, sqlel);
	return *this;
}

SQLExpression & SQLExpression::ST_GeomFromGeoJSON(const SQLExpressionList & sqlel)
{
	sqlFunction(eST_GeomFromGeoJSON, sqlel);
	return *this;
}

SQLExpression & SQLExpression::ST_Distance_Sphere(const SQLExpressionList & sqlel)
{
	sqlFunction(eST_Distance_Sphere, sqlel);
	return *this;
}

SQLExpression & SQLExpression::ST_IsValid()
{
	sqlFunction(eST_IsValid, {});
	return *this;
}

SQLExpression & SQLExpression::ST_MakeEnvelope(const SQLExpression & sqle)
{
	sqlFunction(eST_MakeEnvelope, { sqle });
	return *this;
}

SQLExpression & SQLExpression::ST_Simplify(const SQLExpression & sqleMaxDistance)
{
	sqlFunction(eST_Simplify, { sqleMaxDistance });
	return *this;
}

SQLExpression & SQLExpression::ST_Validate()
{
	sqlFunction(eST_Validate, {});
	return *this;
}

SQLExpression & SQLExpression::ANY_VALUE()
{
	sqlFunction(eANY_VALUE, { });
	return *this;
}

SQLExpression & SQLExpression::DEFAULT()
{
	sqlFunction(eDEFAULT, { });
	return *this;
}

SQLExpression & SQLExpression::GET_LOCK(const SQLExpression & sqleTimeout)
{
	sqlFunction(eGET_LOCK, { sqleTimeout });
	return *this;
}

SQLExpression & SQLExpression::INET_ATON()
{
	sqlFunction(eINET_ATON, { });
	return *this;
}

SQLExpression & SQLExpression::INET_NTOA()
{
	sqlFunction(eINET_NTOA, { });
	return *this;
}

SQLExpression & SQLExpression::INET6_ATON()
{
	sqlFunction(eINET6_ATON, { });
	return *this;
}

SQLExpression & SQLExpression::INET6_NTOA()
{
	sqlFunction(eINET6_NTOA, { });
	return *this;
}

SQLExpression & SQLExpression::IS_FREE_LOCK()
{
	sqlFunction(eIS_FREE_LOCK, { });
	return *this;
}

SQLExpression & SQLExpression::IS_IPV4()
{
	sqlFunction(eIS_IPV4, { });
	return *this;
}

SQLExpression & SQLExpression::IS_IPV4_COMPAT()
{
	sqlFunction(eIS_IPV4_COMPAT, { });
	return *this;
}

SQLExpression & SQLExpression::IS_IPV4_MAPPED()
{
	sqlFunction(eIS_IPV4_MAPPED, { });
	return *this;
}

SQLExpression & SQLExpression::IS_IPV6()
{
	sqlFunction(eIS_IPV6, { });
	return *this;
}

SQLExpression & SQLExpression::IS_USED_LOCK()
{
	sqlFunction(eIS_USED_LOCK, { });
	return *this;
}

SQLExpression & SQLExpression::MASTER_POS_WAIT(const SQLExpression & sqlePos, const SQLExpression & sqleTimeout, const SQLExpression & sqleChannel)
{
	sqlFunction(eMASTER_POS_WAIT, { sqlePos, sqleTimeout, sqleChannel });
	return *this;
}

SQLExpression & SQLExpression::NAME_CONST(const SQLExpression & sqleValue)
{
	sqlFunction(eNAME_CONST, { sqleValue });
	return *this;
}

SQLExpression & SQLExpression::RELEASE_ALL_LOCKS()
{
	sqlFunction(eRELEASE_ALL_LOCKS);
	return *this;
}

SQLExpression & SQLExpression::RELEASE_LOCK()
{
	sqlFunction(eRELEASE_LOCK, { });
	return *this;
}

SQLExpression & SQLExpression::SLEEP()
{
	sqlFunction(eSLEEP, { });
	return *this;
}

SQLExpression & SQLExpression::UUID()
{
	sqlFunction(eUUID);
	return *this;
}

SQLExpression & SQLExpression::UUID_SHORT()
{
	sqlFunction(eUUID_SHORT);
	return *this;
}

SQLExpression & SQLExpression::VALUES(const SQLExpressionList & sqlel)
{
	sqlFunction(eVALUES, sqlel);
	return *this;
}


