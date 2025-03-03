#pragma once
#include "Repo.h"


class Service {
private:
	Repo repo;
public:
	//Adds a patient to the list
	//name is the name of the patient
	// age is the age of the patient
	// infected is the status of infection
	//room is the number of room
	//returns true if the patient was added, false otherwise
	bool AddPatientToService(string name, int age, bool infected, int room);

	vector<Patient> GetAllPatients();
	void GeneratePatients();

	void UpdatePatient(int age);
	void HealPatient(string name);
};
