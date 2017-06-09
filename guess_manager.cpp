GuessManager::GuessManager () :
	file_read(fopen("tree_read.txt", "r")),
	file_out(fopen("tree_out.txt", "w")),
	buf()
	{}

GuessManager::~GuessManager () {

}


void GuessManager::Ask (Node* root) {
	static Node* root_ = root;
	setlocale(LC_ALL, "Russian");
	std::wstring buf = L"";
	wchar_t str[100];
	if ((root->rightCh == NULL)&&(root->leftCh == NULL)) {
		wprintf(L"Это %s?\n", root->val.c_str());
		fflush(stdin);
		std::getline(std::wcin, buf);
		if (!buf.compare(answ[ANSW_YES])) {
			wprintf(L"Молодец! Круто! Продолжить игру?");
			fflush(stdin);
			std::getline(std::wcin, buf);
			if (!buf.compare(answ[ANSW_YES])) {
				Ask(root_);
			} else if (!buf.compare(answ[ANSW_NO])) {
				wprintf(L"Game over.");
			}
		} else if (!buf.compare(answ[ANSW_NO])) {
			wprintf(L"Кого вы загадали?\n");
			fflush(stdin);
			std::getline(std::wcin, buf);
			root->AddLeft(buf);
			root->AddRight(root->val);
			wprintf(L"Чем ваш объект отличается от угаданного мной?\n");
			fflush(stdin);
			std::getline(std::wcin, buf);
			root->val = buf;
			wprintf(L"Молодец! Круто! Продолжить игру?");
			fflush(stdin);
			std::getline(std::wcin, buf);
			if (!buf.compare(answ[ANSW_YES])) {
				Ask(root_);
			} else if (!buf.compare(answ[ANSW_NO])) {
				wprintf(L"Game over.");
			}
		} else {
			wprintf(L"Not correct answer, try again.\n");
			Ask(root);
		}
	} else {
		wprintf(L"%s?\n", root->val.c_str());
		wscanf(L"%s", &str);
		buf = str;
		if (!buf.compare(answ[ANSW_YES])) {
			Ask(root->leftCh);
		} else if (!buf.compare(answ[ANSW_NO])) {
			Ask(root->rightCh);
		} else {
			wprintf(L"Not correct answer, try again.\n");
			Ask(root);
		}
	}
}

void GuessManager::Run () {
	root.Read(file_read);
	Ask(&root);
	root.Print(file_out);
}

Node* GuessManager::Find (std::wstring name, Node* root) {
	Node* node;
	if (!name.compare(root->val)) {
		wprintf(L"DEFINITION: %s ", root->val.c_str());
		return root;
	}
	if (!((root->leftCh)&&(root->rightCh))) {
		return NULL;
	}
	if ((node = Find(name, root->leftCh)) != NULL) {
		return node;
	}
	if ((node = Find(name, root->rightCh)) != NULL) {
		return node;
	}
	return NULL;
}

void GuessManager::Definition (std::wstring name, Node* tree) {

	if (tree->root != NULL) {
		if (tree->root->leftCh == tree) {
			wprintf(L"%s, ", tree->root->val.c_str());
			Definition(name, tree->root);
		}
		if (tree->root->rightCh == tree) {
			wprintf(L"НЕ %s, ", tree->root->val.c_str());
			Definition(name, tree->root);
		}
	} else {

	}
}

void GuessManager::_Definition () {
	std::wstring name;
	Node* node;
	root.Read(file_read);
	wprintf(L"Введите имя, определение которого хотите получить.");
	fflush(stdin);
	std::getline(std::wcin, name);
	if ((node = Find(name, &root)) != NULL) {
		Definition(name, node);
	} else {
		wprintf(L"Объект не найден");
	}
