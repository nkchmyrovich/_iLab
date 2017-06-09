#ifndef _DIFF_H_INCLUDED
#define _DIFF_H_INCLUDED

class Diff {
public:
    FILE* file_read;
    FILE* file_out;
    FILE* file_tex_out;
    Node root;
    Node* _Diff(Node* root);
    Node* Copy(Node* root);
    void To_Tex(Node* root);
    void _Optim_0(Node* root);
    void _Optim_1L(Node* root);
    void _Optim_1R(Node* root);
    void _Optim_P0_L(Node* root);
    void _Optim_P0_R(Node* root);
    void Optim();
	void Run();
    Diff();
    ~Diff();
};

#include <_diff.cpp>

#endif