#include "UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

int main() {
	Ui* ui = CreateUi(20);
	testFunctions(ui->service);
	Start(ui);
	DestroyUi(ui);
	_CrtDumpMemoryLeaks();
	return 0;
}