#pragma once
#include "Domain.h"


class Repo {
private:
	vector<Patient> patients;
public:
	//Add a patient 
	//patient is the patient to be added
	//return true if the patir=ent was added, false otherwise
	bool AddPatient(Patient patient);
	vector<Patient> GetPatients();
};