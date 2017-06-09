#ifndef _EXPRESSION_H_INCLUDED
#define _EXPRESSION_H_INCLUDED

class Expression {
public:
	int type;
	std::string value;
	Expression(const Expression& that);
	Expression();
	~Expression();
};

#include <_expression.cpp>

#endif