#ifndef _NODE_H_INCLUDED
#define _NODE_H_INCLUDED

class Node {
public:
	Node* root;
	Expression val;
	Node* leftCh;
	Node* rightCh;
	void Print (FILE* file_out);
	void Printf();
	void Read (FILE* file_read);
	void AddLeft (Node* node);
	void AddRight (Node* node);
	Node ();
	Node (std::string str, int _type);
	Node (const Node& that);
	Node (Node* that);
	~Node();
};

#include <_node.cpp>

#endif