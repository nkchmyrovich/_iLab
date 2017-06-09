#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

const std::string _NONE = "N";

const std::string node_val[3] = {"0", "1", "-1"};

const std::string _operator[6] = {"+", "-", "*", "/", "^"};

const std::string _function[5] = {"cos", "sin", "log", "ln", "exp"};

enum NODE_VAL {
	ZERO,
	ONE,
	M_ONE
};

enum _OPERATOR {
	SUM = 0,
	DEC,
	MUL,
	DIV,
	DEG
};

enum _FUNCTION {
	COS = 0,
	SIN, //1
	LOG, //2
	LN, //3
	EXP //4
};

enum TYPE {
	CONST = 0,
	VAR, //1
	FUNC, //2
	OPERATOR, //3
	NONE //4
};

#endif