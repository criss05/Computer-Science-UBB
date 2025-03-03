#include "Service.h"
#include <string.h>
#include <iostream>
#include <algorithm>



Service::Service(){}

Service::Service(ClientRepositoryBase* client_repo, EmployeesRepositoryBase* employees_repo){
	this->client_repo = client_repo;
	this->employees_repo = employees_repo;
}

void Service::AddPet(const std::string& breed, const std::string& name, int age, const std::string& photograph){
	Pet pet = Pet(breed, name, age, photograph);
	this->validator.validate(pet);
	this->employees_repo->AddPetToRepo(pet);

	Action* action = new ActionAdd(employees_repo, pet);
	this->undo_stack.push_back(action);
	this->redo_stack.clear();
}

void Service::DeletePet(const std::string& breed, const std::string& name){
	this->validator.validate(Pet(breed, name, 1, "www"));
	Pet pet = this->employees_repo->GetPetFromRepo(name, breed);
	this->employees_repo->DeletePetFromRepo(pet);

	Action* action = new ActionDelete(employees_repo, pet);
	this->undo_stack.push_back(action);
	this->redo_stack.clear();
}

void Service::UpdatePet(const std::string& breed, const std::string& name, int new_age, const std::string& new_photograph){
	this->validator.validate(Pet(breed, name, new_age, new_photograph));
	Pet& pet = this->employees_repo->GetPetFromRepo(name, breed);
	Pet old_pet = pet;
	pet.SetAge(new_age);
	pet.SetPhotograph(new_photograph);
	this->employees_repo->WriteToFile();

	Action* action = new ActionUpdate(employees_repo, pet, old_pet);
	this->undo_stack.push_back(action);
	this->redo_stack.clear();
}

vector<Pet> Service::GetAllPets(){
	return this->employees_repo->GetPetsFromRepo();
}

vector<Pet> Service::GetPetsFromAdoptionList(){
	return this->client_repo->GetAdoptionList();
}

void Service::AdoptPet(Pet pet){
	this->client_repo->AdoptPet(pet);
}

vector<Pet> Service::GetYoungDogsOfGivenBreed(std::string given_breed, int given_age){
	if (given_breed.empty())
		this->validator.validate(Pet("breed", "Name", given_age, "www"));
	else
		this->validator.validate(Pet(given_breed, "Name", given_age, "www"));

	vector<Pet> pets = this->employees_repo->GetPetsFromRepo();
	vector<Pet> copy;
	copy_if(pets.begin(), pets.end(), back_inserter(copy), [given_breed, given_age](Pet pet) {return pet.GetAge()<given_age && (pet.GetBreed() == given_breed || given_breed.empty()); });
	return copy;
}

int Service::GetSizeOfAdoptionList(){
	return this->client_repo->GetAdoptionListSize();
}

int Service::GetPetSize(){
	return this->employees_repo->GetPetsNumber();
}

int Service::GetNumberPetAge(int start_age, int end_age){
	int count = 0;
	vector<Pet> pets = this->employees_repo->GetPetsFromRepo();
	for (auto pet : pets)
		if (end_age != NULL) {
			if (pet.GetAge() > start_age && pet.GetAge() <= end_age)
				count++;
		}
		else
			if (pet.GetAge() > start_age)
				count++;
	return count;
}

void Service::OpenAdoptionList(){
	this->client_repo->OpenAdoptionList();
}

void Service::ReadFromFileService(){
	this->employees_repo->ReadFromFile();
}

void Service::Undo(){
	Action* action = undo_stack.back();
	redo_stack.push_back(undo_stack.back());
	undo_stack.pop_back();
	action->ExecuteUndo();
}

void Service::Redo(){
	Action* action = redo_stack.back();
	undo_stack.push_back(redo_stack.back());
	redo_stack.pop_back();
	action->ExecuteRedo();
}

bool Service::NotUndo(){
	return undo_stack.empty();
}

bool Service::NotRedo(){
	return redo_stack.empty();
}
