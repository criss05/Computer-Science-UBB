#include "Test.h"
#include <assert.h>

void Test::TestAll(){
	this->TetsAdd();
	this->TestHeal();
}

void Test::TetsAdd(){
	Service service;
	service.AddPatientToService("Jessica Thompson", 42, false, 3);
	service.AddPatientToService("Lidia Aspen", 30, true, 3);
	assert(service.GetAllPatients().size() == 2);
	assert(service.GetAllPatients()[0].GetName() == "Jessica Thompson");
}

void Test::TestHeal(){
	Service service;
	service.AddPatientToService("Jessica Thompson", 42, false, 3);
	service.AddPatientToService("Lidia Aspen", 30, true, 3);
	service.HealPatient("Lidia Aspen");
	assert(service.GetAllPatients()[1].GetInfected() == true);
}
