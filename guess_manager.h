#ifndef GUESS_MANAGER_H_INCLUDED
#define GUESS_MANAGER_H_INCLDED

class GuessManager {
public:
	FILE* file_read;
	FILE* file_out;
	void Ask(Node* root);
	Node* Find(std::wstring name, Node* tree);
	void Definition (std::wstring name, Node* tree);
	void _Definition ();
	void Run();
	Node root;
	std::string buf;
	GuessManager();
	~GuessManager();
};

#include "guess_manager.cpp"

#endif // GUESS_MANAGER_H_INCLUDED
