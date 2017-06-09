#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

class Node {
public:
	Node* root;
	std::wstring val;
	Node* leftCh;
	Node* rightCh;
	void Print (FILE* file_out);
	void Printf();
	void Read (FILE* file_read);
	void AddLeft (std::wstring str);
	void AddRight (std::wstring str);
	Node();
	Node(std::wstring str);
	Node(Node* _leftCh, Node* _rightCh);
	~Node();
};

#include "tree.cpp"

#endif // TREE_H_INCLUDED
