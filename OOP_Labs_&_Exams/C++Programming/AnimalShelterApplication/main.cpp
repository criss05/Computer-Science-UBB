#include "EmployeesRepository.h"
#include "Service.h"
#include "UI.h"
#include <iostream>
#include "Testing.h"
//#include <crtdbg.h>

int main() {
	{
		Test test;
		test.TestAll();
		std::cout << "Test done.";
		EmployeesRepository employees_repo = EmployeesRepository();
		ClientRepository client_repo = ClientRepository();
		Service service = Service(client_repo, employees_repo);
		UI ui = UI(service);
		ui.StartUI();
	}
	_CrtDumpMemoryLeaks();
}


/*
operator++() -> elements[++i];
operator++(int) -> elements[i++];
*/