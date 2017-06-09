const std::wstring answ[2] = {L"да", L"нет"};

enum AMSWER {
	ANSW_YES = 0,
	ANSW_NO //1
};

Node::Node () :
	root(NULL),
	val (),
	leftCh (NULL),
	rightCh (NULL)
	{

	}

Node::Node (std::wstring str) :
	root(NULL),
	leftCh (NULL),
	rightCh (NULL),
	val (str)
	{

	}

Node::Node (Node* _leftCh, Node* _rightCh) :
	root(NULL),
	leftCh (_leftCh),
	rightCh (_rightCh),
	val()
	{

	}

Node::~Node () {
	if(leftCh) {
		delete leftCh;
	}
	if (rightCh) {
		delete rightCh;
	}
}

void Node::Print (FILE* file_out) {
	fwprintf(file_out, L" ( %d %s", val.size(), val.c_str());
	if (leftCh) leftCh->Print(file_out);
	if (rightCh) rightCh->Print(file_out);
	if ((!rightCh)&&(!leftCh)) fprintf(file_out, " X");
	fprintf(file_out, " )");
}

void Node::Printf () {
	wprintf(L" ( %d %s", val.size(), val.c_str());
	if (leftCh) leftCh->Printf();
	if (rightCh) rightCh->Printf();
	if ((!rightCh)&&(!leftCh)) wprintf( L" X");
	wprintf( L" )");
}

void Node::Read (FILE* file_read) {
	wchar_t buf_[100] = L"";
	char sym;
	size_t len = 0;
	fwscanf(file_read, L" ( %d ", &len);
	size_t i = 0;
	for(i = 0; i < len; i++) {
		fwscanf(file_read, L"%c", &buf_[i]);
	}
	val = buf_;
	fseek(file_read, 1, SEEK_CUR);
	fwscanf(file_read, L"%c", &sym);
	if (sym == '(') {
		leftCh = new Node ();
		leftCh->root = this;
		fseek(file_read, -1, SEEK_CUR);
		leftCh->Read(file_read);
		rightCh = new Node ();
		rightCh->root = this;
		fseek(file_read, -1, SEEK_CUR);
		rightCh->Read(file_read);
	} else if (sym == 'X') {
		fseek(file_read, 2, SEEK_CUR);
		leftCh = NULL;
		rightCh = NULL;
	}
	fscanf(file_read, " )");
}

void Node::AddLeft (std::wstring str) {
	if (leftCh == NULL) {
		leftCh = new Node (str);
		leftCh->root = this;
	}
}

void Node::AddRight (std::wstring str) {
	if (rightCh == NULL) {
		rightCh = new Node (str);
		rightCh->root = this;
	}
}
