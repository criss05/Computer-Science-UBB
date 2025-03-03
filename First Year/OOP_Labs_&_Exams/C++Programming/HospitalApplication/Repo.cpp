#include "Repo.h"
bool Repo::AddPatient(Patient patient){
	bool found = false;
	for (int i = 0; i < this->patients.size(); i++)
		if (this->patients[i].GetName() == patient.GetName())
			found = true;
	if (!found)
		this->patients.push_back(patient);
	return found;
}

vector<Patient> Repo::GetPatients(){
	return this->patients;
}
