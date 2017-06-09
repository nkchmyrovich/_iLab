Node::Node () :
	root (NULL),
	val (),
	leftCh (NULL),
	rightCh (NULL)
	{
		
	}

Node::Node (std::string str, int _type) :
	root (NULL),
	val (),
	leftCh (NULL),
	rightCh (NULL)
	{
		val.value = str;
		val.type = _type;
	}

Node::Node(const Node& that) :
	root (that.root),
	val (that.val),
	leftCh (that.leftCh),
	rightCh (that.rightCh)
	{
	}

Node::Node(Node* that) :
	val (that->val),
	leftCh (that->leftCh),
	rightCh (that->rightCh)
	{
	}

Node::~Node () {
	
}

std::string _Dec (std::string val) {
	int a = atoi(val.c_str()) - 1;
	char buf [5];
	sprintf(buf, "%d", a);
	std::string str_buf = buf;
	return str_buf;
}

void Node::Print (FILE* file_out) {
	fprintf(file_out, " ( %d %d %s", val.type, val.value.size(), val.value.c_str());
	if (leftCh) leftCh->Print(file_out);
	if (rightCh) rightCh->Print(file_out);
	if ((!rightCh)&&(!leftCh)) fprintf(file_out, " X");
	fprintf(file_out, " )");
}

void Node::Printf () {
	printf(" ( %d %d %s", val.type, val.value.size(), val.value.c_str());
	if (leftCh) leftCh->Printf();
	if (rightCh) rightCh->Printf();
	if ((!rightCh)&&(!leftCh)) printf(" X");
	printf(" )");
}

void Node::Read (FILE* file_read) {
	char buf_[100] = "";
	char sym;
	size_t len = 0;
	fscanf(file_read, " ( %d ", &val.type);
	fscanf(file_read, "%d ", &len);
	size_t i = 0;
	for(i = 0; i < len; i++) {
		fscanf(file_read, "%c", &buf_[i]);
	}
	buf_[len] = '\0';
	val.value = buf_;
	fseek(file_read, 1, SEEK_CUR);
	fscanf(file_read, "%c", &sym);
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

void Node::AddLeft (Node* node) {
	if (!leftCh) {
		leftCh = new Node ();
		leftCh = node;
		leftCh->root = this;
	} else {
		leftCh = node;
	}

}

void Node::AddRight (Node* node) {
	if (!rightCh) {
		rightCh = new Node ();
		rightCh = node;
		rightCh->root = this;
	} else {
		rightCh = node;
	}

}
