
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <crtdbg.h>

using namespace std;


int main() {


	testAll();
	testAllExtended();
	cout << "Test End" << endl;

	_CrtDumpMemoryLeaks();

	system("pause");
}