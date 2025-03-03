#pragma once
#include "Service.h"

class UI {
private: 
	Service service;
public:
	void Start();
private:
	void printMenu();

	void AddPatient();
	void PrintPatients();
	void HealPatient();
	void UpdateInfection();
};
