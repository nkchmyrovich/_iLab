Diff::Diff () :
    root(),
    file_read(fopen("diff_read.txt", "r")),
    file_out(fopen("diff_out.txt", "w")),
    file_tex_out(fopen("diff_tex_out.txt", "w"))
{}

Diff::~Diff () {
	
}


Node* Diff::Copy (Node* root) {
	if (root) {
		Node* rootCpy = new Node ();
		rootCpy->val.value = root->val.value;
		rootCpy->val.type = root->val.type;
		rootCpy->root = root->root;
		rootCpy->leftCh = Copy(root->leftCh);
		rootCpy->rightCh = Copy(root->rightCh);
		return rootCpy;
	}
	return NULL;
}

Node* Diff::_Diff (Node* root) {
	switch(root->val.type) {
	case CONST:
		root->val.value = node_val[ZERO];
		break;
	case VAR:
		root->val.value = node_val[ONE];
		root->val.type = CONST;
		break;
	case FUNC:
		if (!root->val.value.compare(_function[COS])) {
            Node* lftCh = Copy(root->leftCh);
            Node* lftCh1 = Copy(root->leftCh);
            root->val.value = _operator[MUL];
            root->val.type = OPERATOR;
            Node* _node_mul = new Node (_operator[MUL], OPERATOR);
            Node* _node_sin = new Node (_function[SIN], FUNC);
            Node* _node_m_one = new Node (node_val[M_ONE], CONST);
            Node* _node_none = new Node (_NONE, NONE);
            root->AddLeft(_node_mul);
            root->AddRight(_Diff(lftCh));
            root->leftCh->AddLeft(_node_sin);
            root->leftCh->AddRight(_node_m_one);
            root->leftCh->leftCh->AddLeft(lftCh1);
            root->leftCh->leftCh->AddRight(_node_none);
		} else if (!root->val.value.compare(_function[SIN])) {
            Node* lftCh = Copy(root->leftCh);
            Node* lftCh1 = Copy(root->leftCh);
            root->val.value = _operator[MUL];
            root->val.type = OPERATOR;
            Node* _node_mul = new Node (_operator[MUL], OPERATOR);
            Node* _node_cos = new Node (_function[COS], FUNC);
            Node* _node_none = new Node (_NONE, NONE);
            root->AddLeft(_node_cos);
            root->AddRight(_Diff(lftCh));
            root->leftCh->AddLeft(lftCh1);
            root->leftCh->AddRight(_node_none);
		} else if (!root->val.value.compare(_function[LOG])) {

        } else if (!root->val.value.compare(_function[LN])) {
            Node* lftCh = Copy(root->leftCh);
            Node* lftCh1 = Copy(root->leftCh);
            root->val.value = _operator[MUL];
            root->val.type = OPERATOR;
            Node* _node_mul = new Node (_operator[MUL], OPERATOR);
            Node* _node_div = new Node (_operator[DIV], OPERATOR);
            Node* _node_one = new Node (node_val[ONE], CONST);
            root->AddLeft(_node_div);
            root->AddRight(_Diff(lftCh));
            root->leftCh->AddLeft(_node_one);
            root->leftCh->AddRight(lftCh1);
        } else if (!root->val.value.compare(_function[EXP])) {
            Node* lftCh = Copy(root->leftCh);
            Node* lftCh1 = Copy(root->leftCh);
            root->val.value = _operator[MUL];
            root->val.type = OPERATOR;
            Node* _node_mul = new Node (_operator[MUL], OPERATOR);
            Node* _node_exp = new Node (_function[EXP], FUNC);
            Node* _node_none = new Node (_NONE, NONE);
            root->AddLeft(_node_exp);
            root->AddRight(_Diff(lftCh1));
            root->leftCh->AddLeft(lftCh);
            root->leftCh->AddRight(_node_none);
        }
		break;
	case OPERATOR:
		if ((!root->val.value.compare(_operator[SUM]))||(!root->val.value.compare(_operator[DEC]))) {
			_Diff(root->leftCh);
			_Diff(root->rightCh);
		} else if (!root->val.value.compare(_operator[MUL])) {
			root->val.value = _operator[SUM];
			Node* lftCh = Copy(root->leftCh);
			Node* rghtCh = Copy(root->rightCh);
			Node* rghtCh1 = Copy(root->rightCh);
			Node* lftCh1 = Copy(root->leftCh);
			root->leftCh->val.value = _operator[MUL];
			root->leftCh->val.type = OPERATOR;
			root->rightCh->val.value = _operator[MUL];
			root->rightCh->val.type = OPERATOR;
			root->leftCh->AddLeft(lftCh);
			root->leftCh->AddRight(_Diff(rghtCh));
			root->rightCh->AddRight(rghtCh1);
			root->rightCh->AddLeft(_Diff(lftCh1));
		} else if (!root->val.value.compare(_operator[DIV])) {
			Node* lftCh = Copy(root->leftCh);
			Node* rghtCh = Copy(root->rightCh);
			Node* lftCh1 = Copy(root->leftCh);
			Node* rghtCh1 = Copy(root->rightCh);
			Node* rghtCh2 = Copy(root->rightCh);
			Node* rghtCh3 = Copy(root->rightCh);
			root->leftCh->val.value = _operator[DEC];
			root->leftCh->val.type = OPERATOR;
			root->rightCh->val.value = _operator[MUL];
			root->rightCh->val.type = OPERATOR;
			root->rightCh->AddRight(rghtCh);
			root->rightCh->AddLeft(rghtCh1);
			Node* _node_mul_1 = new Node (_operator[MUL], OPERATOR);
			Node* _node_mul_2 = new Node (_operator[MUL], OPERATOR);
			root->leftCh->AddLeft(_node_mul_1);
			root->leftCh->AddRight(_node_mul_2);
			root->leftCh->leftCh->AddLeft(_Diff(lftCh));
			root->leftCh->leftCh->AddRight(rghtCh3);
			root->leftCh->rightCh->AddLeft(_Diff(rghtCh2));
			root->leftCh->rightCh->AddRight(lftCh1);
		} else if (!root->val.value.compare(_operator[DEG])) {
			switch (root->leftCh->val.type) {
				case VAR:
					switch (root->rightCh->val.type) {
						case VAR:

							break;
						case CONST: {
							Node* lftCh = Copy(root->leftCh);
							Node* rghtCh = Copy(root->rightCh);
							Node* rghtCh1 = Copy(root->rightCh);
							Node* lftCh1 = Copy(root->leftCh);
							root->val.value = _operator[MUL];
							root->val.type = OPERATOR;
							Node* _node_deg = new Node (_operator[DEG], OPERATOR);
							Node* _node_dec_val = new Node (_Dec(rghtCh->val.value), CONST);
							Node* _node_mul = new Node (_operator[MUL], OPERATOR);
							root->AddLeft(_node_deg);
							root->leftCh->AddLeft(lftCh);
							root->leftCh->AddRight(_node_dec_val);
							root->AddRight(_node_mul);
							root->rightCh->AddLeft(_Diff(lftCh1));
							root->rightCh->AddRight(rghtCh1);
							}
							break;
					}
					break;
				case CONST:
					switch (root->rightCh->val.type) {
						case VAR:

							break;
						case CONST:
							root->val.value = node_val[ZERO];
							root->val.type = CONST;
							root->leftCh = NULL;
							root->rightCh = NULL;
							break;
					}
					break;
			}
		}

		break;
	}
return root;
}

#define OPERATOR_TEX(op, _type, bracket, _bracket) if (!root->val.value.compare(_type)) {\
char br = bracket;\
char _br = _bracket;\
if ((root->leftCh->val.value.compare(_operator[DEG])) && (root->leftCh->val.type != CONST) && (root->leftCh->val.type != VAR)) fprintf (file_tex_out, "%c", br);\
To_Tex(root->leftCh);\
if ((root->leftCh->val.value.compare(_operator[DEG])) && (root->leftCh->val.type != CONST) && (root->leftCh->val.type != VAR)) fprintf (file_tex_out, "%c", _br);\
fprintf op;\
if ((root->rightCh->val.value.compare(_operator[DEG])) && (root->rightCh->val.type != CONST) && (root->rightCh->val.type != VAR)) fprintf (file_tex_out, "%c", br);\
To_Tex(root->rightCh);\
if ((root->rightCh->val.value.compare(_operator[DEG])) && (root->rightCh->val.type != CONST) && (root->rightCh->val.type != VAR)) fprintf (file_tex_out, "%c", _br);\
} else

#define OPERATOR_TEX_H(op, type) if (!root->val.value.compare(type)) {\
fprintf (file_tex_out, "\\");\
fprintf op;\
fprintf(file_tex_out, "{");\
To_Tex(root->leftCh);\
fprintf(file_tex_out, "}");\
fprintf(file_tex_out, "{");\
To_Tex(root->rightCh);\
fprintf(file_tex_out, "}");\
} else

#define FUNCTION_TEX(op, type) if (!root->val.value.compare(type)) {\
fprintf (file_tex_out, "\\");\
fprintf op;\
fprintf(file_tex_out, "(");\
To_Tex(root->leftCh);\
fprintf(file_tex_out, ")");\
} else

void Diff::To_Tex (Node* root) {
    switch (root->val.type) {
    case OPERATOR:
        OPERATOR_TEX((file_tex_out, "+"), _operator[SUM], '{', '}')
        OPERATOR_TEX((file_tex_out, "-"), _operator[DEC], '(', ')')
        OPERATOR_TEX((file_tex_out, "*"), _operator[MUL], '(', ')')
        OPERATOR_TEX_H((file_tex_out, "frac"), _operator[DIV])
        OPERATOR_TEX((file_tex_out, "^"), _operator[DEG], '{', '}')
        {}
        break;
    case FUNC:
        FUNCTION_TEX((file_tex_out, "cos"), _function[COS])
        FUNCTION_TEX((file_tex_out, "sin"), _function[SIN])
        FUNCTION_TEX((file_tex_out, "log"), _function[LOG])
        FUNCTION_TEX((file_tex_out, "ln"), _function[LN])
        FUNCTION_TEX((file_tex_out, "exp"), _function[EXP])
        {}
        break;
    case VAR:
        fprintf(file_tex_out, "%s", root->val.value.c_str());
        break;
    case CONST:
        fprintf(file_tex_out, "%s", root->val.value.c_str());
        break;
    case NONE:

        break;
    }
}

void  Diff::_Optim_0(Node* root) {
    if (root) {
        if (!root->val.value.compare(_operator[MUL])) {
            if (!root->leftCh->val.value.compare(node_val[ZERO])||!root->rightCh->val.value.compare(node_val[ZERO])) {
                root->val.value = node_val[ZERO];
                root->val.type = CONST;
                root->leftCh = NULL;
                root->rightCh = NULL;
            }
        }
        _Optim_0(root->leftCh);
        _Optim_0(root->rightCh);
    }

}

void Diff::_Optim_1L(Node* root) {
    if (root) {
        if(!root->val.value.compare(_operator[MUL])) {
            if ((!root->leftCh->val.value.compare(node_val[ONE]))&&(root->leftCh->val.type == CONST)) {
                root->val = root->rightCh->val;
                Node* lftCh = Copy(root->rightCh->leftCh);
                Node*  rghtCh = Copy(root->rightCh->rightCh);
                root->leftCh = lftCh;
                root->rightCh = rghtCh;
            }
        }
        _Optim_1L(root->leftCh);
        _Optim_1L(root->rightCh);
    }
}

void Diff::_Optim_1R(Node* root) {
    if (root) {
        if(!root->val.value.compare(_operator[MUL])) {
            if ((!root->rightCh->val.value.compare(node_val[ONE]))&&(root->rightCh->val.type == CONST)) {
                root->val = root->leftCh->val;
                Node* lftCh = Copy(root->leftCh->leftCh);
                Node*  rghtCh = Copy(root->leftCh->rightCh);
                root->leftCh = lftCh;
                root->rightCh = rghtCh;
            }
        }
        _Optim_1R(root->leftCh);
        _Optim_1R(root->rightCh);
    }
}

void Diff::_Optim_P0_L(Node* root) {
    if (root) {
        if((!root->val.value.compare(_operator[SUM]))||(!root->val.value.compare(_operator[DEC]))) {
            if ((!root->leftCh->val.value.compare(node_val[ZERO]))&&(root->leftCh->val.type == CONST)) {
                root->val = root->rightCh->val;
                Node* lftCh = Copy(root->rightCh->leftCh);
                Node*  rghtCh = Copy(root->rightCh->rightCh);
                root->leftCh = lftCh;
                root->rightCh = rghtCh;
            }
        }
        _Optim_P0_L(root->leftCh);
        _Optim_P0_L(root->rightCh);
    }
}

void Diff::_Optim_P0_R(Node* root) {
    if (root) {
        if((!root->val.value.compare(_operator[SUM]))||(!root->val.value.compare(_operator[DEC]))) {
            if ((!root->rightCh->val.value.compare(node_val[ZERO]))&&(root->rightCh->val.type == CONST)) {
                root->val = root->leftCh->val;
                Node* lftCh = Copy(root->leftCh->leftCh);
                Node*  rghtCh = Copy(root->leftCh->rightCh);
                root->leftCh = lftCh;
                root->rightCh = rghtCh;
            }
        }
        _Optim_P0_R(root->leftCh);
        _Optim_P0_R(root->rightCh);
    }
}

void Diff::Optim () {
    _Optim_0(&root);
    _Optim_P0_L(&root);
    _Optim_P0_R(&root);
    _Optim_1L(&root);
    _Optim_1R(&root);
}

void Diff::Run () {
	root.Read(file_read);
	_Diff(&root);
	Optim();
	To_Tex(&root);
}