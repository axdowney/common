#pragma once
#include <string>
#include <vector>
#include <memory>
class Expression {
public:
	enum Type {
		eUnknown,
		eNumeric,
		eString,
		eFunc
	};
	Expression(double dVal);
	Expression(const std::string &sVal);

	std::string toString() const;
	std::string getCore() const;
	bool setCore(const Expression &expr);
	virtual std::string sanitize(const std::string &sVal);
	virtual bool validate(const std::string &sVal);
	
protected:
	Expression();
	void generalFunction(const std::string &sFunc);
	void generalFunction(const std::string &sFunc, const std::vector<std::shared_ptr<Expression> > &operands);
	void generalOperation(const std::string &sOperation, const std::string &sRightOp);
	void generalOperation(const std::string &sOperation, bool bLeft = true);
	void surround(const std::string &sBeg, const std::string &sEnd);
	void clearEdges();
	std::string sLeft;
	std::string sCore;
	std::string sRight;
	Type eType;
};