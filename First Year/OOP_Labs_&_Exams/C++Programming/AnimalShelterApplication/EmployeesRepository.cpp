#include "EmployeesRepository.h"
#include <iostream>

void EmployeesRepository::AddPetToRepo(Pet pet) {
	Pet* pets = this->pets.GetElements();
	for (int i = 0; i < this->pets.GetSize(); i++) {
		if (pets[i] == pet) {
			throw std::exception("Pet already exists!");
		}
	}
	this->pets.AddElement(pet);
}

void EmployeesRepository::DeletePetFromRepo(Pet pet) {
	Pet* pets = this->pets.GetElements();
	bool exists = false;
	for (int i = 0; i < this->pets.GetSize(); i++) {
		if (pets[i] == pet) {
			exists = true;
		}
	}
	if (!exists) {
		throw std::exception("Pet does not exists!");
	}
	this->pets.DeleteElement(pet);
}

Pet& EmployeesRepository::GetPetFromRepo(const std::string& name, std::string breed) {
	Pet* pets = this->pets.GetElements();
	for (int i = 0; i < this->pets.GetSize(); i++) {
		if (pets[i].GetName() == name && pets[i].GetBreed() == breed) {
			return pets[i];
		}
	}
	throw std::exception("Pet does not exists!");}

Pet* EmployeesRepository::GetPetsFromRepo() {
	return this->pets.GetElements();
}

int EmployeesRepository::GetPetsNumber() {
	return this->pets.GetSize();
}
