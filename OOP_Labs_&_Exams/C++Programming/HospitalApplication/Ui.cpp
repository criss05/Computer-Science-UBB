#include "Ui.h"
#include <iostream>
#include <string>
using namespace std;

void UI::Start(){
	this->service.GeneratePatients();
	while (1) {
		this->printMenu();
		string option_str;
		cout << "Give the otion: ";
		getline(cin, option_str);
		int option = stoi(option_str);
		switch (option) {
		case 1: {
			this->AddPatient();
			break;
		}
		case 2: {
			this->PrintPatients();
			break;
		}
		case 3: {
			this->HealPatient();
			break;
		}
		case 4: {
			this->UpdateInfection();
			break;
		}
		case 5: {
			cout << "exiting..";
			return;
		}
		  defalut: {
			  cout << "Inavlid option!\n";
			  break;
		}
		}
	}
}


void UI::printMenu(){
	cout << "1. Add patient\n"
		<< "2. Print patients\n"
		<< "3. Heal patient\n"
		<< "4. update infection\n"
		<< "5. Exit\n";
}

void UI::AddPatient(){
	string name, str_age, str_room, str_infection;
	cout << "Give the name: ";
	getline(cin, name);

	cout << "GIve the age: ";
	getline(cin, str_age);
	int age = stoi(str_age);
	if (age == 0) {
		cout << "Invalid age!";
		return;
	}
	bool infection;
	cout << "GIve the infection: ";
	getline(cin, str_infection);
	if (str_infection == "true")
		infection = true;
	else
		infection = false;

	cout << "Give the room: ";
	getline(cin, str_room);
	int room = stoi(str_room);
	if (room == 0) {
		cout << "Invalid room!";
		return;
	}
	this->service.AddPatientToService(name, age, infection, room);
}

void UI::PrintPatients(){
	vector<Patient> patients = this->service.GetAllPatients();
	for (int i = 0; i < patients.size(); i++)
		cout << patients[i].GetName() << " " << patients[i].GetAge() << " " << patients[i].GetInfected() << " " << patients[i].GetRoom() << "\n";
}

void UI::HealPatient(){
	string name;
	cout << "Give the name: ";
	getline(cin, name);
	this->service.HealPatient(name);
}

void UI::UpdateInfection(){

}
