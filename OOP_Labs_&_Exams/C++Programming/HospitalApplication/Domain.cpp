#include "Domain.h"

Patient::Patient(string name, int age, bool infected, int room){
	this->name = name;
	this->age = age;
	this->infected = infected;
	this->room = room;
}

string Patient::GetName()
{
	return this->name;
}

int Patient::GetAge()
{
	return this->age;
}

bool Patient::GetInfected()
{
	return this->infected;
}

int Patient::GetRoom()
{
	return this->room;
}

void Patient::SetInfected(bool new_status){
	this->infected = new_status;
}
