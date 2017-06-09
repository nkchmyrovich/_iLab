#include "tree.h"
#include <Windows.h>

int main () {
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	/*GuessManager gm;
	gm.Run();*/
	GuessManager gm;
	gm._Definition();
	system("PAUSE");
	return 0;
}
