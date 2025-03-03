#include "Pet.h"
#include <iostream>

Pet::Pet()
{
}

Pet::Pet(const std::string& breed, const std::string& name, int age, const std::string& photograph){
	this->breed = breed;
	this->name = name;
	this->age = age;
	this->photograph = photograph;
}

Pet::Pet(const Pet& pet){
	this->breed = pet.breed;
	this->name = pet.name;
	this->age = pet.age;
	this->photograph = pet.photograph;
}


std::string Pet::GetBreed() const{
	return this->breed;
}

std::string Pet::GetName() const{
	return this->name;
}

int Pet::GetAge() const{
	return this->age;
}

std::string Pet::GetPhotograph() const{
	return this->photograph;
}

void Pet::SetBreed(const std::string& new_breed){
	this->breed = new_breed;
}

void Pet::SetName(const std::string& new_name){
	this->name = new_name;
}

void Pet::SetAge(int new_age){
	this->age = new_age;
}

void Pet::SetPhotograph(const std::string& new_phptograph){
	this->photograph = new_phptograph;
}

bool Pet::operator==(const Pet& pet){
	if (this->name == pet.name && this->breed == pet.breed) 
		return true;
	return false;
}

Pet& Pet::operator=(const Pet& pet){
	this->breed = pet.breed;
	this->name = pet.name;
	this->age = pet.age;
	this->photograph = pet.photograph;
	return *this;
}

void Pet::PrintPet(std::string& print_pet){
	print_pet = "BREED: " + this->breed + " |  NAME: " + this->name + " |  AGE: " + std::to_string(this->age) + " |  PHOTOGRAPH: " + this->photograph+"\n";
}
