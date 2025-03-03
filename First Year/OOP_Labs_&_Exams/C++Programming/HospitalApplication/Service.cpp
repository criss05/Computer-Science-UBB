#include "Service.h"
#include <iostream>
using namespace std;


bool Service::AddPatientToService(string name, int age, bool infected, int room)
{
	return this->repo.AddPatient(Patient{name, age, infected, room});
}

vector<Patient> Service::GetAllPatients()
{
	return this->repo.GetPatients();
}

void Service::GeneratePatients(){
	this->repo.AddPatient(Patient("Jessica Thompson", 42, false, 3));
	this->repo.AddPatient(Patient("Lidia Aspen", 30, true, 3));
	this->repo.AddPatient(Patient("Scott Smith", 86,false, 2));
	this->repo.AddPatient(Patient("Zeno Hardy", 37, true, 8));
	this->repo.AddPatient(Patient("Andrew Scott", 62, false, 2));
}

void Service::UpdatePatient(int age){
	vector<Patient> patients = this->repo.GetPatients();
	for (int i = 0; i < patients.size(); i++)
		if (patients[i].GetInfected() == true)
			for (int j = 0; j < patients.size(); j++)
				if (patients[j].GetRoom() == patients[j].GetRoom() || patients[j].GetRoom() == patients[j].GetRoom() + 1 || patients[j].GetRoom() == patients[j].GetRoom() - 1)
					patients[j].SetInfected(true);
}

void Service::HealPatient(string name){
	for (int i = 0; i < this->repo.GetPatients().size(); i++)
		if (this->repo.GetPatients()[i].GetName() == name) {
			this->repo.GetPatients()[i].SetInfected(false);
		}
}
