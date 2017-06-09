Calculator::Calculator() :
	curr(0),
	buf()
	{}

Calculator::~Calculator() {
	
}

void Calculator::Read_formula () {
	fflush(stdin);
	std::getline(std::cin, buf);
	
}

Node* Calculator::GetG () {
	Node* val = GetE();
	if (buf[curr] != '\0') printf("GET_G ERROR\n");
	return val;
}

Node* Calculator::GetN() {
	bool point = false;
	double result = 0;
	double deg = 1;
	size_t i = 0;
	char _buf [100];
	std::string str;
	if (('0' <= buf[curr] && buf[curr] <= '9') || (buf[curr] == '.')) {
		while (('0' <= buf[curr] && buf[curr] <= '9') || (buf[curr] == '.')) {
			if ('0' <= buf[curr] && buf[curr] <= '9') {
				_buf[i] = buf[curr];
			} else if ( buf[curr] == '.' ) {
				if (point) { 
					printf ("ERROR_GET_N_POINT");
					break;
				} else {
					point = true;
					_buf[i] = buf[curr];
				}
			}
			curr++;
			i++;
		}
		str = _buf;
		Node* _node = new Node (str, CONST);
		return _node;
	} else if (buf[curr] != '\0') {
		while (('A' <= buf[curr] && buf[curr] <= 'Z') || ('a' <= buf[curr] && buf[curr] <= 'z')) {
			_buf[i] = buf[curr];
			curr++;
			i++;
		}
		str = _buf;
		Node* _node = new Node (str, VAR);
		return _node;
	}
}

Node* Calculator::GetT() {
	Node* _node = new Node ();
	Node* node_1 = GetD();
	_node = node_1;
	while (buf[curr] == '*' || buf[curr] == '/') {
		char __operator = buf[curr];
		curr++;
		Node* node_2 = GetT();
		if (__operator == '*') {
			_node->val.type = OPERATOR;
			_node->val.value = _operator[MUL];
			_node->leftCh = node_1;
			_node->rightCh = node_2;
		} else {
			_node->val.type = OPERATOR;
			_node->val.value = _operator[DIV];
			_node->leftCh = node_1;
			_node->rightCh = node_2;
		}
	}
	return _node;
}

Node* Calculator::GetE() {
	Node* _node = new Node ();
	Node* node_1 = GetT();
	_node = node_1;
	while (buf[curr] == '+' || buf[curr] == '-') {
		char __operator = buf[curr];
		curr++;
		Node* node_2 = new Node ();
		node_2 = GetE();
		if (__operator == '+') {
			_node->val.type = OPERATOR;
			_node->val.value = _operator[SUM];
			_node->leftCh = node_1;
			_node->rightCh = node_2;
		} else {
			_node->val.type = OPERATOR;
			_node->val.value = _operator[DEC];
			_node->leftCh = node_1;
			_node->rightCh = node_2;
		}
	}
	_node->Printf();
	return _node;
}

Node* Calculator::GetP() {
	Node* _node = new Node ();
	if (buf[curr] != '(') {
		_node = GetN();
		return _node;
	}
	curr++;
	_node = GetE();
	if (buf[curr] != ')') printf("ERROR_GET_P");
	curr++; 
	return _node;
}

Node*  Calculator::GetD() {
	Node* _node = new Node ();
	Node* node_1 = GetI();
	if (buf[curr] == '^') {
		char __operator = buf[curr];
		curr++;
		Node* node_2 = GetI();
		_node->val.type = OPERATOR;
		_node->val.value = _operator[DEG];
		_node->leftCh = node_1;
		_node->rightCh =  node_2;
		return _node;
	} else {
		return node_1;
	}
}

Node* Calculator::GetI() {
	Node* _node = new Node ();
	_node = GetP();
	if (isalpha(buf[curr])) {
		size_t i = 0;
		std::string str = "";
		char str_ [100];
		bool func = false;
		while (isalpha(buf[curr])) {
			str_[i] = buf[curr];
			i++;
			curr++;
		}
		if (buf[curr] != '(') printf("ERROR_GET_I\n");
		Node* val_ = new Node ();
		str = str_;
		if (!str.compare(_function[SIN])) {
			_node->val.type = FUNC;
			_node->val.value = _function[SIN];
			_node->leftCh = val_;
		} else if (!str.compare(_function[COS])) {
			_node->val.type = FUNC;
			_node->val.value = _function[COS];
			_node->leftCh = val_;
		} else if (!str.compare(_function[LN])) {
			_node->val.type = FUNC;
			_node->val.value = _function[LN];
			_node->leftCh = val_;
		} else  if (!str.compare(_function[EXP])) {
			_node->val.type = FUNC;
			_node->val.value = _function[EXP];
			_node->leftCh = val_;
		} else {
			printf("GET_I_ERROR\n");
			return NULL;
		}
		if (buf[curr-1] != ')') printf("ERROR_GET_I\n");
		return _node;
	} else {
		return _node;
	}
}