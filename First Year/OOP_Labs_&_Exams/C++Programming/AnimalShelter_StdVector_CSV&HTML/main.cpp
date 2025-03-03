#include "Service.h"
#include "UI.h"
#include <iostream>
#include "Testing.h"
#include "EmployeesRepository.h"
#include "ClientRepository.h"
#include "RepoException.h"
#include <crtdbg.h>

using namespace std;

int main() {
	{
		system("cls");
		try {
			FileEmployeesRepository* employees_repo = new FileEmployeesRepository("pets.txt");

			cout << "1. CSV.\n";
			cout << "2. HTML.\n";
			cout << "Choose the format: ";
			string file_type;
			getline(cin, file_type);
			if (stoi(file_type) == 1) {
				ClientRepositoryCSV* client_repo = new ClientRepositoryCSV("adoption_list.csv");
				Service service = Service(client_repo, employees_repo);
				UI ui = UI(service);
				ui.StartUI();
				delete client_repo;
			}
			else if (stoi(file_type) == 2) {
				ClientRepositoryHTML* client_repo = new ClientRepositoryHTML("adoption_list.html");
				Service service = Service(client_repo, employees_repo);
				UI ui = UI(service);
				ui.StartUI();
				delete client_repo;
			}
			delete employees_repo;
		}
		catch (FileException& error) {
			cout << error.what();
		}
	}
	_CrtDumpMemoryLeaks();
}


/*
operator++() -> elements[++i];
operator++(int) -> elements[i++];
*/