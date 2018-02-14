#include "SQLExpression.h"
#include "PireTables.h"

SQLExpression::SQLExpression(const std::string & sVal)
{
	sExpr = PireTable().quote(sVal);
}

SQLExpression::SQLExpression(const char * pc) : SQLExpression(pc ? std::string(pc) : std::string())
{
}

SQLExpression::SQLExpression(double dVal)
{
	sExpr = std::to_string(dVal);
}

SQLExpression::SQLExpression(const PireTable & pt, int iCol) : sExpr(pt.getColumnName(iCol))
{
}

SQLExpression::SQLExpression(const SQLExpression & sqle) : sExpr(sqle.sExpr), iNestLevel(sqle.iNestLevel)
{
	if (sExpr.empty()) {
		sExpr = "''";
	}
}

std::string SQLExpression::toString() const
{
	std::string sRet = sExpr;
	for (int i = iNestLevel; i > 0; ++i) {
		sRet += ")";
	}
	return sRet;
}

SQLExpression & SQLExpression::openParen(bool bNot)
{
	if (bNot) {
		sExpr + " " + PireTable::getOperation(PireTable::NOT);
	}

	sExpr += " (";
	++iNestLevel;
	return *this;
}

SQLExpression & SQLExpression::closeParen()
{
	if (iNestLevel > 0) {
		sExpr += ")";
		--iNestLevel;
	}

	return *this;
}

SQLExpression & SQLExpression::enclose()
{
	sExpr = "(" + sExpr + ")";
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
	case SQLExpression::eeDivide:
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
	case SQLExpression::eGeomCollFromWKB:
		sRet = "GeomCollFromWKB";
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
	case SQLExpression::eGeomFromWKB:
		sRet = "GeomFromWKB";
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
	case SQLExpression::eLineFromWKB:
		sRet = "LineFromWKB";
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
	case SQLExpression::eMLineFromWKB:
		sRet = "MLineFromWKB";
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
	case SQLExpression::eMPointFromWKB:
		sRet = "MPointFromWKB";
		break;
	case SQLExpression::eMPolyFromText:
		sRet = "MPolyFromText";
		break;
	case SQLExpression::eMPolyFromWKB:
		sRet = "MPolyFromWKB";
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
	case SQLExpression::ePolyFromWKB:
		sRet = "PolyFromWKB";
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
	case SQLExpression::eST_AsGeoJSON:
		sRet = "ST_AsGeoJSON";
		break;
	case SQLExpression::eST_AsText:
		sRet = "ST_AsText";
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
	case SQLExpression::eST_GeomCollFromWKB:
		sRet = "ST_GeomCollFromWKB";
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
	case SQLExpression::eST_GeomFromWKB:
		sRet = "ST_GeomFromWKB";
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
	case SQLExpression::eST_LineFromWKB:
		sRet = "ST_LineFromWKB";
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
	case SQLExpression::eST_MLineFromWKB:
		sRet = "ST_MLineFromWKB";
		break;
	case SQLExpression::eST_MPointFromText:
		sRet = "ST_MPointFromText";
		break;
	case SQLExpression::eST_MPointFromWKB:
		sRet = "ST_MPointFromWKB";
		break;
	case SQLExpression::eST_MPolyFromText:
		sRet = "ST_MPolyFromText";
		break;
	case SQLExpression::eST_MPolyFromWKB:
		sRet = "ST_MPolyFromWKB";
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
	case SQLExpression::eST_PolyFromWKB:
		sRet = "ST_PolyFromWKB";
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
	std::string sRet = getFunction(e) + "(" + sqleList.getListString() + ")";
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
	sqlel.updateString();
	sExpr = buildFunctionString(e, sqlel);
	return *this;
}

SQLExpression::operator bool() const
{
	return !sExpr.empty();
}

SQLExpression & SQLExpression::equal(const SQLExpression & sqle)
{
	sExpr += " " + getFunction(eEqual) + " " + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::equalNullSafe(const SQLExpression & sqle)
{
	sExpr += " " + getFunction(eEqualNullSafe) + " " + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::notEqual(const SQLExpression & sqle)
{
	sExpr += " " + getFunction(eNotEq) + " " + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::notEqualSQL(const SQLExpression & sqle)
{
	sExpr += " " + getFunction(eNotEqSQL) + " " + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::lessThanEq(const SQLExpression & sqle)
{
	sExpr += " " + getFunction(eLessThanEq) + " " + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::lessThan(const SQLExpression & sqle)
{
	sExpr += " " + getFunction(eLessThan) + " " + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::greaterThanEq(const SQLExpression & sqle)
{
	sExpr += " " + getFunction(eGreaterThanEq) + " " + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::greaterThan(const SQLExpression & sqle)
{
	sExpr += " " + getFunction(eGreaterThan) + " " + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::IS(const SQLExpression & sqle)
{
	sExpr += " " + getFunction(eIS) + " " + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::IS_NOT(const SQLExpression & sqle)
{
	sExpr += " " + getFunction(eIS_NOT) + " " + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::IS_NULL()
{
	sExpr += " " + getFunction(eIS_NULL);
	return *this;
}

SQLExpression & SQLExpression::IS_NOT_NULL()
{
	sExpr += " " + getFunction(eIS_NOT_NULL);
	return *this;
}

SQLExpression & SQLExpression::BETWEEN(const SQLExpression & sqleMin, const SQLExpression & sqleMax)
{
	sExpr += " " + getFunction(eBETWEEN) + " " + sqleMin.toString() + " "
		+ getFunction(eAND) + " " + sqleMax.toString();
	return *this;
}

SQLExpression & SQLExpression::NOT_BETWEEN(const SQLExpression & sqleMin, const SQLExpression & sqleMax)
{
	sExpr += " " + getFunction(eNOT) + " " + getFunction(eBETWEEN) + " " + sqleMin.toString() + " "
		+ getFunction(eAND) + " " + sqleMax.toString();
	return *this;
}

SQLExpression & SQLExpression::GREATEST(const SQLExpressionList & sqleList)
{
	sExpr = buildFunctionString(eGREATEST, *this, sqleList);
	return *this;
}

SQLExpression & SQLExpression::IN(const SQLExpressionList & sqleList)
{
	sExpr += " " + buildFunctionString(eIN, sqleList);
	return *this;
}

SQLExpression & SQLExpression::NOT_IN(const SQLExpressionList & sqleList)
{
	sExpr += " " + getFunction(eNOT) + " " + buildFunctionString(eIN, sqleList);
	return *this;
}

SQLExpression & SQLExpression::ISNULL()
{
	sExpr += " " + getFunction(eISNULL);
	return *this;
}

SQLExpression & SQLExpression::COALESCE(const SQLExpressionList & sqleList)
{
	sExpr = buildFunctionString(eCOALESCE, *this, sqleList);
	return *this;
}

SQLExpression & SQLExpression::INTERVAL(const SQLExpressionList & sqleList)
{
	sExpr = buildFunctionString(eINTERVAL, *this, sqleList);
	return *this;
}

SQLExpression & SQLExpression::LEAST(const SQLExpressionList & sqleList)
{
	sExpr = buildFunctionString(eLEAST, *this, sqleList);
	return *this;
}

SQLExpression & SQLExpression::LIKE(const SQLExpression & sqle, const SQLExpression & sqleEscape)
{
	sExpr += " " + getFunction(eLIKE) + " " + sqle.toString();
	if (sqleEscape) {
		sExpr += " ESCAPE " + sqleEscape.toString();
	}
	return *this;
}

SQLExpression & SQLExpression::NOT_LIKE(const SQLExpression & sqle, const SQLExpression & sqleEscape)
{
	sExpr += " " + getFunction(eNOT) + " " + getFunction(eLIKE) + " " + sqle.toString();
	if (sqleEscape) {
		sExpr += " ESCAPE " + sqleEscape.toString();
	}
	return *this;
}

SQLExpression & SQLExpression::STRCMP(const SQLExpression & sqle)
{
	sExpr = buildFunctionString(eSTRCMP, { *this, sqle });
	return *this;
}

SQLExpression & SQLExpression::DIV(const SQLExpression & sqle)
{
	sExpr += " DIV " + sqle.sExpr;
	return *this;
}

SQLExpression & SQLExpression::divide(const SQLExpression & sqle)
{
	sExpr += " / " + sqle.sExpr;
	return *this;
}

SQLExpression & SQLExpression::MOD(const SQLExpression & sqle)
{
	sExpr += " % " + sqle.sExpr;
	return *this;
}

SQLExpression & SQLExpression::add(const SQLExpression & sqle)
{
	sExpr += " + " + sqle.sExpr;
	return *this;
}

SQLExpression & SQLExpression::multiply(const SQLExpression & sqle)
{
	sExpr += " * " + sqle.sExpr;
	return *this;
}

SQLExpression & SQLExpression::subtract(const SQLExpression & sqle)
{
	sExpr += " - " + sqle.sExpr;
	return *this;
}

SQLExpression & SQLExpression::ABS()
{
	sExpr = "ABS(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::ACOS()
{
	sExpr = "ACOS(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::ASIN()
{
	sExpr = "ASIN(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::ATAN()
{
	sExpr = "ATAN(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::ATAN(const SQLExpression & sqleY)
{
	sExpr = "ATAN(" + sqleY.toString() + "," + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::ATAN2(const SQLExpression & sqleY)
{
	sExpr = "ATAN2(" + sqleY.toString() + "," + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::CEIL()
{
	sExpr = "CEIL(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::CONV(const SQLExpression & sqleFromBase, const SQLExpression & sqleToBase)
{
	sExpr = "CONV(" + sExpr + "," + sqleFromBase.toString() + "," + sqleToBase.toString() + ")";
	return *this;
}

SQLExpression & SQLExpression::COS()
{
	sExpr = "COS(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::COT()
{
	sExpr = "COT(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::CRC32()
{
	sExpr = "CRC32(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::DEGREES()
{
	sExpr = "DEGREES(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::EXP()
{
	sExpr = "EXP(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::FLOOR()
{
	sExpr = "FLOOR(" + sExpr + ")";
	return *this;
}

/*SQLExpression & SQLExpression::FORMAT(const SQLExpression & sqlePrecision)
{
	sExpr = "FORMAT(" + sExpr + "," + sqlePrecision.toString() + ")";
	return *this;
}*/

SQLExpression & SQLExpression::HEX()
{
	sExpr = "HEX(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::LN()
{
	sExpr = "LN(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::LOG()
{
	sExpr = "LOG(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::LOG(const SQLExpression & sqleBase)
{
	sExpr = "LOG(" + sExpr + "," + sqleBase.toString() + ")";
	return *this;
}

SQLExpression & SQLExpression::LOG2()
{
	sExpr = "LOG2(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::LOG10()
{
	sExpr = "LOG10(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::PI()
{
	sExpr = "PI()";
	return *this;
}

SQLExpression & SQLExpression::POW(const SQLExpression & sqleY)
{
	sExpr = "POW(" + sExpr + "," + sqleY.toString() + ")";
	return *this;
}

SQLExpression & SQLExpression::POWER(const SQLExpression & sqleY)
{
	sExpr = "POWER(" + sExpr + "," + sqleY.toString() + ")";
	return *this;
}

SQLExpression & SQLExpression::RADIANS()
{
	sExpr = "RADIANS(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::RAND()
{
	sExpr = "RAND()";
	return *this;
}

SQLExpression & SQLExpression::RAND(const SQLExpression & sqleSeed)
{
	sExpr = "ROUND(" + sqleSeed.toString() + ")";
	return *this;
}

SQLExpression & SQLExpression::ROUND()
{
	sExpr = "ROUND()";
	return *this;
}

SQLExpression & SQLExpression::ROUND(const SQLExpression & sqlePrecision)
{
	sExpr = "(" + sExpr + "," + sqlePrecision.toString() + ")";
	return *this;
}

SQLExpression & SQLExpression::SIGN()
{
	sExpr = "SIGN(" + sExpr + ")";
	return *this;
}
SQLExpression & SQLExpression::SIN()
{
	sExpr = "SIN(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::SQRT()
{
	sExpr = "SQRT(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::TAN()
{
	sExpr = "TAN(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::TRUNCATE(const SQLExpression & sqlePrecision)
{
	sExpr = "TRUNCATE(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::ASCII()
{
	sExpr = "ASCII(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::BIN()
{
	sExpr = "BIN(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::BIT_LENGTH()
{
	sExpr = "BIT_LENGTH(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::CHAR(const SQLExpression & sqleCharSet)
{
	sExpr = "CHAR(" + sExpr + " USING " + sqleCharSet.toString() + ")";
	return *this;
}

SQLExpression & SQLExpression::CHAR_LENGTH()
{
	sExpr = "CHAR_LENGTH(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::CHARACTER_LENGTH()
{
	sExpr = "CHARACTER_LENGTH(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::CONCAT(const SQLExpression & sqleRight)
{
	sExpr = "CONCAT(" + sExpr + "," + sqleRight.toString() + ")";
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
	sExpr = "";
	size_t t = this->size();

	for (auto iter : static_cast<std::list<SQLExpression> >(*this)) {
		if (!sExpr.empty()) {
			sExpr += ",";
		}
		std::string sTmp = iter.toString();
		//sExpr += iter.toString();
		sExpr += sTmp;
	}

	if (sExpr.empty()) {
		sExpr = "''";
	}
	else {
		//sExpr = "(" + sExpr + ")";
	}

	return *this;
}

std::string SQLExpressionList::getListString() const
{
	std::string sRet;
	for (auto iter : static_cast<std::list<SQLExpression> >(*this)) {
		if (!sRet.empty()) {
			sRet += ",";
		}
		sRet = iter.toString();
	}
	return sRet;
}

SQLExpression & SQLExpressionList::ELT(const SQLExpression & sqleIndex)
{
	return SQLExpressionList::ELT(sqleIndex, *this);
}

SQLExpression & SQLExpressionList::FIELD(const SQLExpression & sqle)
{
	sExpr = "FIELD(" + sqle.toString() + "," + sExpr + ")";
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
	sExpr = "CONCAT_WS(" + sqleSeparator.toString() + "," + sExpr + "," + sqleRight.toString() + ")";
	return *this;
}

SQLExpression & SQLExpression::CONCAT_WS(const SQLExpression & sqleSeparator, const SQLExpressionList & sqleRight)
{
	return SQLExpression::CONCAT_WS(sqleSeparator, static_cast<SQLExpression>(sqleRight));
}

SQLExpression & SQLExpression::ELT(const SQLExpression & sqleIndex, const SQLExpressionList & sqleList)
{
	sExpr = "ELT(" + sqleIndex.toString() + "," + sqleList.toString() + ")";
	return *this;
}

SQLExpression &SQLExpression::EXPORT_SET(const SQLExpression & sqleON, const SQLExpression & sqleOFF, const SQLExpression & sqleSep, const SQLExpression & sqleBitNum)
{
	sExpr = "EXPORT_SET(" + sExpr + "," + sqleON.toString() + "," + sqleOFF.toString();
	if (!sqleSep.toString().empty()) {
		sExpr += "," + sqleSep.toString();
		if (!sqleBitNum.toString().empty()) {
			sExpr += "," + sqleBitNum.toString();
		}
	}

	sExpr += ")";
	return *this;
}

SQLExpression & SQLExpression::FIELD(const SQLExpressionList & sqleList)
{
	sExpr = "FIELD(" + sExpr + "," + sqleList.toString() + ")";
	return *this;
}

SQLExpression & SQLExpression::FIND_IN_SET(const SQLExpression & sqleList)
{
	sExpr = "FIND_IN_SET(" + sExpr + "," + sqleList.toString() + ")";
	return *this;
}

SQLExpression & SQLExpression::FORMAT(const SQLExpression & sqlePrecision, const SQLExpression & sqleLocal)
{
	sExpr = "FORMAT(" + sExpr + "," + sqlePrecision.toString();
	if (!sqleLocal.toString().empty()) {
		sExpr += "," + sqleLocal.toString();
	}

	sExpr += ")";
	return *this;
}

SQLExpression & SQLExpression::FROM_BASE64()
{
	sExpr = "FROM_BASE64(" + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::INSERT(const SQLExpression & sqlePos, const SQLExpression & sqleLen, const SQLExpression & sqleNewStr)
{
	sExpr = "INSERT(" + sExpr + "," + sqlePos.toString() + "," + sqleLen.toString() + "," + sqleNewStr.toString() + ")";
	return *this;
}

SQLExpression & SQLExpression::INSTR(const SQLExpression & sqleSubStr)
{
	sExpr = "INSTR(" + sExpr + "," + sqleSubStr.toString() + ")";
	return *this;
}

SQLExpression & SQLExpression::LCASE()
{
	sExpr = buildFunctionString(eLCASE, { *this });
	return *this;
}

SQLExpression & SQLExpression::LEFT(const SQLExpression & sqleLen)
{
	sExpr = buildFunctionString(eLEFT, { *this, sqleLen });
	return *this;
}

SQLExpression & SQLExpression::LENGTH()
{
	sExpr = buildFunctionString(eLENGTH, { *this });
	return *this;
}

SQLExpression & SQLExpression::LOAD_FILE()
{
	sExpr = buildFunctionString(eLOAD_FILE, { *this });
	return *this;
}

SQLExpression & SQLExpression::LOCATE(const SQLExpression & sqleStr, const SQLExpression & sqlePos)
{
	if (sqlePos.toString().empty()) {
		sExpr = buildFunctionString(eLOCATE, { *this, sqleStr });
	}
	else {
		sExpr = buildFunctionString(eLOCATE, { *this, sqleStr, sqlePos });
	}

	return *this;
}

SQLExpression & SQLExpression::LOWER()
{
	sExpr = buildFunctionString(eLOWER, { *this });
	return *this;
}

SQLExpression & SQLExpression::LPAD(const SQLExpression & sqleLen, const SQLExpression & sqlePadStr)
{
	sExpr = buildFunctionString(eLPAD, { *this, sqleLen, sqlePadStr });
	return *this;
}

SQLExpression & SQLExpression::LTRIM()
{
	sExpr = buildFunctionString(eLTRIM, { *this });
	return *this;
}

SQLExpression & SQLExpression::MAKE_SET(const SQLExpressionList & sqleList)
{
	SQLExpressionList sqlelTmp = sqleList;
	sqlelTmp.push_front(*this);
	sqlelTmp.updateString();
	sExpr = buildFunctionString(eMAKE_SET, sqlelTmp);
	return *this;
}

SQLExpression & SQLExpression::MID(const SQLExpression & sqlePos, const SQLExpression & sqleLen)
{
	sExpr = buildFunctionString(eMID, { *this, sqlePos, sqleLen });
	return *this;
}

SQLExpression & SQLExpression::OCT()
{
	sExpr = buildFunctionString(eOCT, { *this });
	return *this;
}

SQLExpression & SQLExpression::OCTET_LENGTH()
{
	sExpr = buildFunctionString(eOCTET_LENGTH, { *this });
	return *this;
}

SQLExpression & SQLExpression::ORD()
{
	sExpr = buildFunctionString(eORD, { *this });
	return *this;
}

SQLExpression & SQLExpression::POSITION_IN(const SQLExpression & sqleStr)
{
	sExpr = "POSITION(" + sExpr + " IN " + sqleStr.toString() + ")";
	return *this;
}

SQLExpression & SQLExpression::QUOTE()
{
	sExpr = buildFunctionString(eQUOTE, { *this });
	return *this;
}

SQLExpression & SQLExpression::REPEAT(const SQLExpression & sqleCount)
{
	sExpr = buildFunctionString(eLOWER, { *this, sqleCount });
	return *this;
}

SQLExpression & SQLExpression::REPLACE(const SQLExpression & sqleFromStr, const SQLExpression & sqleToStr)
{
	sExpr = buildFunctionString(eREPLACE, { *this, sqleFromStr, sqleToStr });
	return *this;
}

SQLExpression & SQLExpression::REVERSE()
{
	sExpr = buildFunctionString(eREVERSE, { *this });
	return *this;
}

SQLExpression & SQLExpression::RIGHT(const SQLExpression & sqleLen)
{
	sExpr = buildFunctionString(eRIGHT, { *this, sqleLen });
	return *this;
}

SQLExpression & SQLExpression::RPAD(const SQLExpression & sqleLen, const SQLExpression & sqlePadStr)
{
	sExpr = buildFunctionString(eRPAD, { *this, sqleLen, sqlePadStr });
	return *this;
}

SQLExpression & SQLExpression::RTRIM()
{
	sExpr = buildFunctionString(eRTRIM, { *this });
	return *this;
}

SQLExpression & SQLExpression::SOUNDEX()
{
	sExpr = buildFunctionString(eSOUNDEX, { *this });
	return *this;
}

SQLExpression & SQLExpression::SOUNDS_LIKE(const SQLExpression & sqleStr)
{
	sExpr = getFunction(eSOUNDS_LIKE) + "(" + sExpr + " LIKE " + sqleStr.toString() + ")";
	return *this;
}

SQLExpression & SQLExpression::SPACE()
{
	sExpr = buildFunctionString(eSPACE, { *this });
	return *this;
}

SQLExpression & SQLExpression::SUBSTR(const SQLExpression & sqlePos, const SQLExpression & sqleLen)
{
	if (sqleLen.toString().empty()) {
		sExpr = buildFunctionString(eSUBSTR, { *this, sqlePos });
	}
	else {
		sExpr = buildFunctionString(eSUBSTR, { *this, sqlePos, sqleLen });
	}
	return *this;
}

SQLExpression & SQLExpression::SUBSTR_FROM_FOR(const SQLExpression & sqlePos, const SQLExpression & sqleLen)
{
	if (sqleLen.toString().empty()) {
		sExpr = getFunction(eSUBSTR) + "(" + sExpr + " FROM " + sqlePos.toString() + ")";
	}
	else {
		sExpr = getFunction(eSUBSTR) + "(" + sExpr + " FROM " + sqlePos.toString() + " FOR " + sqleLen.toString() + ")";
	}
	return *this;
}

SQLExpression & SQLExpression::SUBSTRING_INDEX(const SQLExpression & sqleDelim, const SQLExpression & sqleCount)
{
	sExpr = buildFunctionString(eSUBSTRING_INDEX, { *this, sqleDelim, sqleCount });
	return *this;
}

SQLExpression & SQLExpression::TO_BASE64()
{
	sExpr = buildFunctionString(eTO_BASE64, { *this });
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

	sExpr = sTmp + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::UCASE()
{
	sExpr = buildFunctionString(eUCASE, { *this });
	return *this;
}

SQLExpression & SQLExpression::UNHEX()
{
	sExpr = buildFunctionString(eUNHEX, { *this });
	return *this;
}

SQLExpression & SQLExpression::UPPER()
{
	sExpr = buildFunctionString(eUPPER, { *this });
	return *this;
}

SQLExpression & SQLExpression::WEIGHT_STRING(const std::vector<int>& vecLevel, const std::vector<WeightStringDir>& vecDir)
{
	sExpr = getFunction(eWEIGHT_STRING) + "(" + sExpr;
	if (!vecLevel.empty()) {
		sExpr += " LEVEL ";
		for (int i = 0; i < vecLevel.size(); ++i) {
			if (i > 0) {
				sExpr += ", ";
			}

			sExpr += std::to_string(vecLevel[i]);
			if (i < vecDir.size()) {
				if (vecDir[i] & WeightStringDir::eDirASC) {
					sExpr += " ASC ";
				}
				if (vecDir[i] & WeightStringDir::eDirDESC) {
					sExpr += " DESC ";
				}
				if (vecDir[i] & WeightStringDir::eDirREVERSE) {
					sExpr += " REVERSE ";
				}
			}
		}
	}

	sExpr += ")";
	return *this;
}

SQLExpression & SQLExpression::WEIGHT_STRING_AS_CHAR(const SQLExpression & sqleNum, const std::vector<int>& vecLevel, const std::vector<WeightStringDir>& vecDir)
{
	sExpr += " AS CHAR(" + sqleNum.toString() + ")";
	return WEIGHT_STRING(vecLevel, vecDir);
}

SQLExpression & SQLExpression::WEIGHT_STRING_AS_BINARY(const SQLExpression & sqleNum, const std::vector<int>& vecLevel, const std::vector<WeightStringDir>& vecDir)
{
	sExpr += " AS BINARY(" + sqleNum.toString() + ")";
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
	sExpr = "ADDDATE(" + sExpr + " INTERVAL " + sqle.toString() + " " + getTimeUnit(e) + ")";
	return *this;
}

SQLExpression & SQLExpression::ADDTIME(const SQLExpression & sqle)
{
	sExpr = buildFunctionString(eADDTIME, { *this, sqle });
	return *this;
}

SQLExpression & SQLExpression::CONVERT_TZ(const SQLExpression & sqleFromTZ, const SQLExpression & sqleToTZ)
{
	sExpr = buildFunctionString(eCONVERT_TZ, { *this, sqleFromTZ, sqleToTZ });
	return *this;
}

SQLExpression & SQLExpression::CURDATE()
{
	sExpr = buildFunctionString(eCURDATE, {});
	return *this;
}

SQLExpression & SQLExpression::CURRENT_DATE()
{
	sExpr = buildFunctionString(eCURRENT_DATE, {});
	return *this;
}

SQLExpression & SQLExpression::CURRENT_TIME(const SQLExpression & sqleFSP)
{
	if (sqleFSP.toString().empty()) {
		sExpr = buildFunctionString(eCURRENT_TIME, {});
	}
	else {
		sExpr = buildFunctionString(eCURRENT_TIME, { sqleFSP });
	}
	return *this;
}

SQLExpression & SQLExpression::CURRENT_TIMESTAMP(const SQLExpression & sqleFSP)
{
	if (sqleFSP.toString().empty()) {
		sExpr = buildFunctionString(eCURRENT_TIMESTAMP, {});
	}
	else {
		sExpr = buildFunctionString(eCURRENT_TIMESTAMP, { sqleFSP });
	}
	return *this;
}

SQLExpression & SQLExpression::CURTIME(const SQLExpression & sqleFSP)
{
	if (sqleFSP.toString().empty()) {
		sExpr = buildFunctionString(eCURTIME, {});
	}
	else {
		sExpr = buildFunctionString(eCURTIME, { sqleFSP });
	}
	return *this;
}

SQLExpression & SQLExpression::DATE()
{
	sExpr = buildFunctionString(eDATE, { *this });
	return *this;
}

SQLExpression & SQLExpression::DATEDIFF(const SQLExpression & sqle)
{
	sExpr = buildFunctionString(eDATEDIFF, { *this, sqle });
	return *this;
}

SQLExpression & SQLExpression::DATE_ADD(const SQLExpression & sqle, TimeUnit e)
{
	sExpr = getFunction(eDATE_ADD) + "(" + sExpr + " INTERVAL " + sqle.toString() + " " + getTimeUnit(e) + ")";
	return *this;
}

SQLExpression & SQLExpression::DATE_FORMAT(const SQLExpression & sqleFormat)
{
	sExpr = buildFunctionString(eDATE_FORMAT, { *this, sqleFormat });
	return *this;
}

SQLExpression & SQLExpression::DATE_SUB(const SQLExpression & sqle, TimeUnit e)
{
	sExpr = getFunction(eDATE_SUB) + "(" + sExpr + " INTERVAL " + sqle.toString() + " " + getTimeUnit(e) + ")";
	return *this;
}

SQLExpression & SQLExpression::DAY()
{
	sExpr = buildFunctionString(eDAY, { *this });
	return *this;
}

SQLExpression & SQLExpression::DAYNAME()
{
	sExpr = buildFunctionString(eDAYNAME, { *this });
	return *this;
}

SQLExpression & SQLExpression::DAYOFMONTH()
{
	sExpr = buildFunctionString(eDAYOFMONTH, { *this });
	return *this;
}

SQLExpression & SQLExpression::DAYOFWEEK()
{
	sExpr = buildFunctionString(eDAYOFWEEK, { *this });
	return *this;
}

SQLExpression & SQLExpression::DAYOFYEAR()
{
	sExpr = buildFunctionString(eDAYOFYEAR, { *this });
	return *this;
}

SQLExpression & SQLExpression::EXTRACT(TimeUnit e)
{
	sExpr = getFunction(eEXTRACT) + "(" + getTimeUnit(e) + " FROM " + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::FROM_DAYS()
{
	sExpr = buildFunctionString(eFROM_DAYS, { *this });
	return *this;
}

SQLExpression & SQLExpression::FROM_UNIXTIME()
{
	sExpr = buildFunctionString(eFROM_UNIXTIME, { *this });
	return *this;
}

SQLExpression & SQLExpression::GET_FORMAT(Function e)
{
	sExpr = getFunction(eGET_FORMAT) + "(" + getFunction(e) + ", " + sExpr + ")";
	return *this;
}

SQLExpression & SQLExpression::HOUR()
{
	sExpr = buildFunctionString(eHOUR, { *this });
	return *this;
}

SQLExpression & SQLExpression::LAST_DAY()
{
	sExpr = buildFunctionString(eLAST_DAY, { *this });
	return *this;
}

SQLExpression & SQLExpression::LOCALTIME(const SQLExpression & sqleFSP)
{
	if (sqleFSP.toString().empty()) {
		sExpr = buildFunctionString(eLOCALTIME, {});
	}
	else {
		sExpr = buildFunctionString(eLOCALTIME, { sqleFSP });
	}
	return *this;
}

SQLExpression & SQLExpression::LOCALTIMESTAMP(const SQLExpression & sqleFSP)
{
	if (sqleFSP.toString().empty()) {
		sExpr = buildFunctionString(eLOCALTIMESTAMP, {});
	}
	else {
		sExpr = buildFunctionString(eLOCALTIMESTAMP, { sqleFSP });
	}
	return *this;
}

SQLExpression & SQLExpression::MAKEDATE(const SQLExpression & sqleDayOfYear)
{
	sExpr = buildFunctionString(eMAKEDATE, { *this, sqleDayOfYear });
	return *this;
}

SQLExpression & SQLExpression::MAKETIME(const SQLExpression & sqleMinute, const SQLExpression & sqleSecond)
{
	sExpr = buildFunctionString(eMAKETIME, { *this, sqleMinute, sqleSecond });
	return *this;
}

SQLExpression & SQLExpression::MICROSECOND()
{
	sExpr = buildFunctionString(eMICROSECOND, { *this });
	return *this;
}

SQLExpression & SQLExpression::MINUTE()
{
	sExpr = buildFunctionString(eMINUTE, { *this });
	return *this;
}

SQLExpression & SQLExpression::MONTH()
{
	sExpr = buildFunctionString(eMONTH, { *this });
	return *this;
}

SQLExpression & SQLExpression::MONTHNAME()
{
	sExpr = buildFunctionString(eMONTHNAME, { *this });
	return *this;
}

SQLExpression & SQLExpression::NOW(const SQLExpression & sqleFSP)
{
	if (sqleFSP.toString().empty()) {
		sExpr = buildFunctionString(eNOW, {});
	}
	else {
		sExpr = buildFunctionString(eNOW, { sqleFSP });
	}
	return *this;
}

SQLExpression & SQLExpression::PERIOD_ADD(const SQLExpression & sqle)
{
	sExpr = buildFunctionString(ePERIOD_ADD, { *this, sqle });
	return *this;
}

SQLExpression & SQLExpression::PERIOD_DIFF(const SQLExpression & sqle)
{
	sExpr = buildFunctionString(ePERIOD_DIFF, { *this });
	return *this;
}

SQLExpression & SQLExpression::QUARTER()
{
	sExpr = buildFunctionString(eQUARTER, { *this });
	return *this;
}

SQLExpression & SQLExpression::SECOND()
{
	sExpr = buildFunctionString(eSECOND, { *this });
	return *this;
}

SQLExpression & SQLExpression::SEC_TO_TIME()
{
	sExpr = buildFunctionString(eSEC_TO_TIME, { *this });
	return *this;
}

SQLExpression & SQLExpression::STR_TO_DATE()
{
	sExpr = buildFunctionString(eSTR_TO_DATE, { *this });
	return *this;
}

SQLExpression & SQLExpression::SUBDATE(const SQLExpression & sqle, TimeUnit e)
{
	sExpr = getFunction(eSUBDATE) + "(" + sExpr + " INTERVAL " + sqle.toString() + " " + getTimeUnit(e) + ")";
	return *this;
}

SQLExpression & SQLExpression::SUBTIME(const SQLExpression & sqle)
{
	sExpr = buildFunctionString(eSUBTIME, { *this, sqle });
	return *this;
}

SQLExpression & SQLExpression::SYSDATE(const SQLExpression & sqleFSP)
{
	if (sqleFSP.toString().empty()) {
		sExpr = buildFunctionString(eSYSDATE, {});
	}
	else {
		sExpr = buildFunctionString(eSYSDATE, { sqleFSP });
	}
	return *this;
}

SQLExpression & SQLExpression::TIME()
{
	sExpr = buildFunctionString(eTIME, { *this });
	return *this;
}

SQLExpression & SQLExpression::TIMEDIFF(const SQLExpression & sqle)
{
	sExpr = buildFunctionString(eTIMEDIFF, { *this, sqle });
	return *this;
}

SQLExpression & SQLExpression::TIMESTAMP(const SQLExpression & sqle)
{
	if (sqle) {
		sExpr = buildFunctionString(eTIMESTAMP, { *this, sqle });
	}
	else {
		sExpr = buildFunctionString(eTIMESTAMP, { *this });
	}
	return *this;
}

SQLExpression & SQLExpression::TIMESTAMPADD(TimeUnit e, const SQLExpression & sqleInterval)
{
	sExpr = getFunction(eTIMESTAMPADD) + "(" + getTimeUnit(e) + ", " + sExpr + ", " + sqleInterval.toString() + ")";
	return *this;
}

SQLExpression & SQLExpression::TIMESTAMPDIFF(TimeUnit e, const SQLExpression & sqle)
{
	sExpr = getFunction(eTIMESTAMPDIFF) + "(" + getTimeUnit(e) + ", " + sExpr + ", " + sqle.toString() + ")";
	return *this;
}

SQLExpression & SQLExpression::TIME_FORMAT(const SQLExpression & sqle)
{
	sExpr = buildFunctionString(eTIME_FORMAT, { *this, sqle });
	return *this;
}

SQLExpression & SQLExpression::TIME_TO_SEC()
{
	sExpr = buildFunctionString(eTIME_TO_SEC, { *this });
	return *this;
}

SQLExpression & SQLExpression::TO_DAYS()
{
	sExpr = buildFunctionString(eTO_DAYS, { *this });
	return *this;
}

SQLExpression & SQLExpression::TO_SECONDS()
{
	sExpr = buildFunctionString(eTO_SECONDS, { *this });
	return *this;
}

SQLExpression & SQLExpression::UNIX_TIMESTAMP(const SQLExpression & sqle)
{
	if (sqle) {
		sExpr = buildFunctionString(eUNIX_TIMESTAMP, { *this, sqle });
	}
	else {
		sExpr = buildFunctionString(eUNIX_TIMESTAMP, { *this });
	}
	return *this;
}

SQLExpression & SQLExpression::UTC_DATE()
{
	sExpr = buildFunctionString(eUTC_DATE, {});
	return *this;
}

SQLExpression & SQLExpression::UTC_TIME(const SQLExpression & sqleFSP)
{
	if (sqleFSP) {
		sExpr = buildFunctionString(eUTC_TIME, { *this, sqleFSP });
	}
	else {
		sExpr = buildFunctionString(eUTC_TIME, { *this });
	}
	return *this;
}

SQLExpression & SQLExpression::UTC_TIMESTAMP(const SQLExpression & sqleFSP)
{
	if (sqleFSP) {
		sExpr = buildFunctionString(eUTC_TIMESTAMP, { *this, sqleFSP });
	}
	else {
		sExpr = buildFunctionString(eUTC_TIMESTAMP, { *this });
	}
	return *this;
}

SQLExpression & SQLExpression::WEEK(const SQLExpression & sqleMode)
{
	if (sqleMode) {
		sExpr = buildFunctionString(eWEEK, { *this, sqleMode });
	}
	else {
		sExpr = buildFunctionString(eWEEK, { *this });
	}
	return *this;
}

SQLExpression & SQLExpression::WEEKDAY()
{
	sExpr = buildFunctionString(eWEEKDAY, { *this });
	return *this;
}

SQLExpression & SQLExpression::WEEKOFYEAR()
{
	sExpr = buildFunctionString(eWEEKOFYEAR, { *this });
	return *this;
}

SQLExpression & SQLExpression::YEAR()
{
	sExpr = buildFunctionString(eYEAR, { *this });
	return *this;
}

SQLExpression & SQLExpression::YEARWEEK()
{
	sExpr = buildFunctionString(eYEARWEEK, { *this });
	return *this;
}

SQLExpression & SQLExpression::EXTRACTVALUE(const SQLExpression & sqle)
{
	sExpr = buildFunctionString(eExtractValue, { *this });
	return *this;
}

SQLExpression & SQLExpression::UPDATEXML(const SQLExpression & sqle)
{
	sExpr = buildFunctionString(eUpdateXML, { *this });
	return *this;
}

SQLExpression & SQLExpression::BIT_COUNT()
{
	sExpr = buildFunctionString(eBIT_COUNT, { *this });
	return *this;
}

SQLExpression & SQLExpression::BitwiseAnd(const SQLExpression &sqle)
{
	sExpr = sExpr + " " + getFunction(eBitwiseAnd) + " " + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::BitwiseInvert()
{
	sExpr = getFunction(eBitwiseInvert) + " " + sExpr;
	return *this;
}

SQLExpression & SQLExpression::BitwiseOr(const SQLExpression & sqle)
{
	sExpr = sExpr + " " + getFunction(eBitwiseOr) + " " + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::BitwiseXor(const SQLExpression & sqle)
{
	sExpr = sExpr + " " + getFunction(eBitwiseXor) + " " + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::LeftShift(const SQLExpression & sqle)
{
	sExpr = sExpr + " " + getFunction(eLeftShift) + " " + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::RightShift(const SQLExpression & sqle)
{
	sExpr = sExpr + " " + getFunction(eRightShift) + " " + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::AES_DECRYPT(const SQLExpression & sqleKey, const SQLExpression & sqleInitVec)
{
	if (sqleInitVec) {
		sExpr = buildFunctionString(eAES_DECRYPT, { *this, sqleKey, sqleInitVec });
	}
	else {
		sExpr = buildFunctionString(eAES_DECRYPT, { *this, sqleKey });
	}
	return *this;
}

SQLExpression & SQLExpression::AES_ENCRYPT(const SQLExpression & sqleKey, const SQLExpression & sqleInitVec)
{
	if (sqleInitVec) {
		sExpr = buildFunctionString(eAES_ENCRYPT, { *this, sqleKey, sqleInitVec });
	}
	else {
		sExpr = buildFunctionString(eAES_ENCRYPT, { *this, sqleKey });
	}
	return *this;
}

SQLExpression & SQLExpression::COMPRESS()
{
	sExpr = buildFunctionString(eCOMPRESS, { *this });
	return *this;
}

SQLExpression & SQLExpression::DECODE(const SQLExpression &sqlePass)
{
	if (sqlePass) {
		sExpr = buildFunctionString(eAES_ENCRYPT, { *this, sqlePass });
	}
	else {
		sExpr = buildFunctionString(eAES_ENCRYPT, { *this });
	}
	return *this;
}

SQLExpression & SQLExpression::DES_DECRYPT(const SQLExpression & sqleKey)
{
	if (sqleKey) {
		sExpr = buildFunctionString(eAES_ENCRYPT, { *this, sqleKey });
	}
	else {
		sExpr = buildFunctionString(eAES_ENCRYPT, { *this });
	}
	return *this;
}

SQLExpression & SQLExpression::DES_ENCRYPT(const SQLExpression & sqleKey)
{
	if (sqleKey) {
		sExpr = buildFunctionString(eAES_DECRYPT, { *this, sqleKey });
	}
	else {
		sExpr = buildFunctionString(eAES_DECRYPT, { *this });
	}
	return *this;
}

SQLExpression & SQLExpression::ENCODE(const SQLExpression & sqlePass)
{
	if (sqlePass) {
		sExpr = buildFunctionString(eENCODE, { *this, sqlePass });
	}
	else {
		sExpr = buildFunctionString(eENCODE, { *this });
	}
	return *this;
}

SQLExpression & SQLExpression::ENCRYPT(const SQLExpression & sqleSalt)
{
	if (sqleSalt) {
		sExpr = buildFunctionString(eENCRYPT, { *this, sqleSalt });
	}
	else {
		sExpr = buildFunctionString(eENCRYPT, { *this });
	}
	return *this;
}

SQLExpression & SQLExpression::MD5()
{
	sExpr = buildFunctionString(eMD5, { *this });
	return *this;
}

SQLExpression & SQLExpression::OLD_PASSWORD()
{
	sExpr = buildFunctionString(eOLD_PASSWORD, { *this });
	return *this;
}

SQLExpression & SQLExpression::PASSWORD()
{
	sExpr = buildFunctionString(ePASSWORD, { *this });
	return *this;
}

SQLExpression & SQLExpression::RANDOM_BYTES()
{
	sExpr = buildFunctionString(eRANDOM_BYTES, { *this });
	return *this;
}

SQLExpression & SQLExpression::SHA1()
{
	sExpr = buildFunctionString(eSHA1, { *this });
	return *this;
}

SQLExpression & SQLExpression::SHA2(const SQLExpression & sqleHashLen)
{
	sExpr = buildFunctionString(eSHA2, { *this, sqleHashLen });
	return *this;
}

SQLExpression & SQLExpression::UNCOMPRESS()
{
	sExpr = buildFunctionString(eUNCOMPRESS, { *this });
	return *this;
}

SQLExpression & SQLExpression::VALIDATE_PASSWORD_STRENGTH()
{
	sExpr = buildFunctionString(eVALIDATE_PASSWORD_STRENGTH, { *this });
	return *this;
}

SQLExpression & SQLExpression::BENCHMARK(const SQLExpression & sqleCount)
{
	sExpr = buildFunctionString(eBENCHMARK, { sqleCount, *this });
	return *this;
}

SQLExpression & SQLExpression::CHARSET()
{
	sExpr = buildFunctionString(eCHARSET, { *this });
	return *this;
}

SQLExpression & SQLExpression::COERCIBILITY()
{
	sExpr = buildFunctionString(eCOERCIBILITY, { *this });
	return *this;
}

SQLExpression & SQLExpression::COLLATION()
{
	sExpr = buildFunctionString(eCOLLATION, { *this });
	return *this;
}

SQLExpression & SQLExpression::CONNECTION_ID()
{
	sExpr = buildFunctionString(eCONNECTION_ID, {});
	return *this;
}

SQLExpression & SQLExpression::CURRENT_USER()
{
	sExpr = buildFunctionString(eCURRENT_USER, {});
	return *this;
}

SQLExpression & SQLExpression::DATABASE()
{
	sExpr = buildFunctionString(eDATABASE, {});
	return *this;
}

SQLExpression & SQLExpression::FOUND_ROWS()
{
	sExpr = buildFunctionString(eFOUND_ROWS, {});
	return *this;
}

SQLExpression & SQLExpression::LAST_INSERT_ID(const SQLExpression & sqle)
{
	if (sqle) {
		sExpr = buildFunctionString(eLAST_INSERT_ID, { sqle });
	}
	else {
		sExpr = buildFunctionString(eLAST_INSERT_ID, {});
	}
	return *this;
}

SQLExpression & SQLExpression::ROW_COUNT()
{
	sExpr = buildFunctionString(eROW_COUNT, {});
	return *this;
}

SQLExpression & SQLExpression::SCHEMA()
{
	sExpr = buildFunctionString(eSCHEMA, {});
	return *this;
}

SQLExpression & SQLExpression::SESSION_USER()
{
	sExpr = buildFunctionString(eSESSION_USER, {});
	return *this;
}

SQLExpression & SQLExpression::SYSTEM_USER()
{
	sExpr = buildFunctionString(eSYSTEM_USER, {});
	return *this;
}

SQLExpression & SQLExpression::USER()
{
	sExpr = buildFunctionString(eUSER, {});
	return *this;
}

SQLExpression & SQLExpression::VERSION()
{
	sExpr = buildFunctionString(eVERSION, {});
	return *this;
}

SQLExpression & SQLExpression::JSON_QUOTE()
{
	sExpr = buildFunctionString(eJSON_QUOTE, { *this });
	return *this;
}

SQLExpression & SQLExpression::JSON_CONTAINS(const SQLExpression & sqleCandidate, const SQLExpression & sqlePath)
{
	if (sqlePath) {
		sExpr = buildFunctionString(eJSON_QUOTE, { *this, sqleCandidate, sqlePath });
	}
	else {
		sExpr = buildFunctionString(eJSON_CONTAINS, { *this, sqleCandidate });
	}
	return *this;
}



SQLExpression & SQLExpression::JSON_ExtractOp(const SQLExpression & sqle)
{
	sExpr += getFunction(eJSON_ExtractOp) + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::JSON_UnquoteExtractOp(const SQLExpression & sqle)
{
	sExpr += getFunction(eJSON_UnquoteExtractOp) + sqle.toString();
	return *this;
}

SQLExpression & SQLExpression::JSON_KEYS(const SQLExpression & sqlePath)
{
	if (sqlePath) {
		sExpr = buildFunctionString(eJSON_KEYS, { *this, sqlePath });
	}
	else {
		sExpr = buildFunctionString(eJSON_KEYS, { *this });
	}
	return *this;
}

SQLExpression & SQLExpression::JSON_SEARCH(const SQLExpression & sqleOneAll, const SQLExpression & sqlePath)
{
	if (sqlePath) {
		sExpr = buildFunctionString(eJSON_SEARCH, { *this, sqleOneAll, sqlePath });
	}
	else {
		sExpr = buildFunctionString(eJSON_SEARCH, { *this, sqleOneAll });
	}
	return *this;
}

SQLExpression & SQLExpression::JSON_APPEND(const SQLExpressionList & sqlelPathValPairs)
{
	sExpr = buildFunctionString(eJSON_APPEND, *this, sqlelPathValPairs);
	return *this;
}

SQLExpression & SQLExpression::JSON_ARRAY_APPEND(const SQLExpressionList & sqlelPathValPairs)
{
	sExpr = buildFunctionString(eJSON_ARRAY_APPEND, *this, sqlelPathValPairs);
	return *this;
}

SQLExpression & SQLExpression::JSON_ARRAY_INSERT(const SQLExpressionList & sqlelPathValPairs)
{
	sExpr = buildFunctionString(eJSON_ARRAY_INSERT, *this, sqlelPathValPairs);
	return *this;
}

SQLExpression & SQLExpression::JSON_INSERT(const SQLExpressionList & sqlelPathValPairs)
{
	sExpr = buildFunctionString(eJSON_INSERT, *this, sqlelPathValPairs);
	return *this;
}

SQLExpression & SQLExpression::JSON_MERGE(const SQLExpressionList & sqleDocs)
{
	sExpr = buildFunctionString(eJSON_MERGE, *this, sqleDocs);
	return *this;
}

SQLExpression & SQLExpression::JSON_MERGE_PATCH(const SQLExpressionList & sqleDocs)
{
	sExpr = buildFunctionString(eJSON_MERGE_PATCH, *this, sqleDocs);
	return *this;
}

SQLExpression & SQLExpression::JSON_MERGE_PRESERVE(const SQLExpressionList & sqleDocs)
{
	sExpr = buildFunctionString(eJSON_MERGE_PRESERVE, *this, sqleDocs);
	return *this;
}

SQLExpression & SQLExpression::JSON_REMOVE(const SQLExpressionList & sqleDocs)
{
	sExpr = buildFunctionString(eJSON_REMOVE, *this, sqleDocs);
	return *this;
}

SQLExpression & SQLExpression::JSON_REPLACE(const SQLExpressionList & sqlelPathValPairs)
{
	sExpr = buildFunctionString(eJSON_REPLACE, *this, sqlelPathValPairs);
	return *this;
}

SQLExpression & SQLExpression::JSON_SET(const SQLExpressionList & sqlelPathValPairs)
{
	sExpr = buildFunctionString(eJSON_SET, *this, sqlelPathValPairs);
	return *this;
}

SQLExpression & SQLExpression::JSON_UNQUOTE()
{
	sExpr = buildFunctionString(eJSON_UNQUOTE, { *this });
	return *this;
}

SQLExpression & SQLExpression::JSON_DEPTH()
{
	sExpr = buildFunctionString(eJSON_DEPTH, { *this });
	return *this;
}

SQLExpression & SQLExpression::JSON_LENGTH(const SQLExpression & sqlePath)
{
	if (sqlePath) {
		sExpr = buildFunctionString(eJSON_LENGTH, { *this, sqlePath });
	}
	else {
		sExpr = buildFunctionString(eJSON_LENGTH, { *this });
	}
	return *this;
}

SQLExpression & SQLExpression::JSON_TYPE()
{
	sExpr = buildFunctionString(eJSON_TYPE, { *this });
	return *this;
}

SQLExpression & SQLExpression::JSON_VALID()
{
	sExpr = buildFunctionString(eJSON_VALID, { *this });
	return *this;
}

SQLExpression & SQLExpression::JSON_PRETTY()
{
	sExpr = buildFunctionString(eJSON_PRETTY, { *this });
	return *this;
}

SQLExpression & SQLExpression::JSON_STORAGE_SIZE()
{
	sExpr = buildFunctionString(eJSON_STORAGE_SIZE, { *this });
	return *this;
}

SQLExpression & SQLExpression::GTID_SET(const SQLExpression & sqleSubSet)
{
	sExpr = buildFunctionString(eGTID_SUBSET, { sqleSubSet, *this });
	return *this;
}

SQLExpression & SQLExpression::GTID_SUBSET(const SQLExpression & sqleSet)
{
	sExpr = buildFunctionString(eGTID_SUBSET, { *this, sqleSet });
	return *this;
}

SQLExpression & SQLExpression::GTID_SUBTRACT(const SQLExpression & sqleSubSet)
{
	sExpr = buildFunctionString(eGTID_SUBTRACT, { *this, sqleSubSet });
	return *this;
}

SQLExpression & SQLExpression::WAIT_FOR_EXECUTED_GTID_SET(const SQLExpression & sqleTimeout)
{
	if (sqleTimeout) {
		sExpr = buildFunctionString(eWAIT_FOR_EXECUTED_GTID_SET, { *this, sqleTimeout });
	}
	else {
		sExpr = buildFunctionString(eWAIT_FOR_EXECUTED_GTID_SET, { *this });
	}

	return *this;
}

SQLExpression & SQLExpression::WAIT_UNTIL_SQL_THREAD_AFTER_GTIDS(const SQLExpression & sqleTimeout, const SQLExpression & sqleChannel)
{
	SQLExpressionList sqlelTmp = { *this };
	if (sqleTimeout) {
		sqlelTmp.push_back(sqleTimeout);
	}

	if (sqleChannel) {
		sqlelTmp.push_back(sqleChannel);
	}
	
	sqlelTmp.updateString();
	sExpr = buildFunctionString(eWAIT_UNTIL_SQL_THREAD_AFTER_GTIDS, sqlelTmp);
	return *this;
}
