#include "Expression.h"

Expression::Expression(double dVal)
{
	sCore = std::to_string(dVal);
	eType = eNumeric;
}

Expression::Expression(const std::string & sVal)
{
	sCore = sVal;
	eType = eString;
}

std::string Expression::toString() const
{
	return sLeft + sCore + sRight;
}

std::string Expression::getCore() const
{
	return sCore;
}

bool Expression::setCore(const Expression & expr)
{
	std::string sTmp = sanitize(sTmp);
	bool bRet = validate(sTmp);
	if (bRet) {
		eType = expr.eType;
		sCore = expr.toString();
	}
	return bRet;
}

std::string Expression::sanitize(const std::string & sVal)
{
	return sVal;
}

bool Expression::validate(const std::string & sVal)
{
	return true;
}

Expression::Expression() : eType(eUnknown)
{
}

void Expression::generalFunction(const std::string & sFunc)
{
	eType = eFunc;
	sCore = sFunc + "()";
	sLeft = "";
	sRight = "";
}

void Expression::generalFunction(const std::string & sFunc, const std::vector<std::shared_ptr<Expression> >& operands)
{
	sLeft = sFunc + "(" + sLeft;
	for (size_t i = 0; i < operands.size(); ++i) {
		if (operands[i] && !operands[i]->toString().empty()) {
			sRight += "," + operands[i]->toString();
		}
	}
	sRight += ")";
}

void Expression::generalOperation(const std::string & sOperation, const std::string & sRightOp)
{
	sRight += " " + sOperation + " " + sRightOp;
}

void Expression::generalOperation(const std::string & sOperation, bool bLeft)
{
	if (bLeft) {
		sLeft = sOperation + sLeft;
	}
	else {
		sRight += sOperation;
	}
}

void Expression::surround(const std::string & sBeg, const std::string & sEnd)
{
	sLeft = sBeg + sLeft;
	sRight += sEnd;
}

void Expression::clearEdges()
{
	sLeft = "";
	sRight = "";
}
