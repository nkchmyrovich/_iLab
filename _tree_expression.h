#ifndef _TREE_EXPRESSION_H_INCLUDED
#define _TREE_EXPRESSION_H_INCLUDED

class Calculator {
public:
	void Read_formula ();
	std::string buf;
	size_t curr;
	Node* GetG();
	Node* GetN();
	Node* GetT();
	Node* GetE();
	Node* GetP();
	Node* GetD();
	Node* GetI();
	Calculator();
	~Calculator();
};

#include <_tree_expression.cpp>

#endif