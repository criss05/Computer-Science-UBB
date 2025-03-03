#include "Service.h"
#include <string.h>
#include <iostream>



Service::Service(){}

Service::Service(ClientRepository client_repo, EmployeesRepository employees_repo){
	this->client_repo = client_repo;
	this->employees_repo = employees_repo;
}

void Service::AddPet(const std::string& breed, const std::string& name, int age, const std::string& photograph){
	Pet pet = Pet(breed, name, age, photograph);
	this->employees_repo.AddPetToRepo(pet);
}

void Service::DeletePet(const std::string& breed, const std::string& name){
	Pet pet = this->employees_repo.GetPetFromRepo(name, breed);
	this->employees_repo.DeletePetFromRepo(pet);
}

void Service::UpdatePet(const std::string& breed, const std::string& name, int new_age, const std::string& new_photograph){
	Pet& pet = this->employees_repo.GetPetFromRepo(name, breed);
	pet.SetAge(new_age);
	pet.SetPhotograph(new_photograph);
}

Pet* Service::GetAllPets(){
	return this->employees_repo.GetPetsFromRepo();
}

Pet* Service::GetPetsFromAdoptionList(){
	return this->client_repo.GetAdoptionList();
}

void Service::AdoptPet(Pet pet){
	this->client_repo.Adoptpet(pet);
}

Pet* Service::GetYoungDogsOfGivenBreed(std::string given_breed, int given_age, int& number_elements){
	Pet* pets = this->employees_repo.GetPetsFromRepo();
	Pet* copy = new Pet[this->employees_repo.GetPetsNumber()];
	int k = 0;
	for (int i = 0; i < this->employees_repo.GetPetsNumber(); i++) {
		if ((pets[i].GetBreed() == given_breed || given_breed.length()==0) && pets[i].GetAge() < given_age) {
			copy[k] = pets[i];
			k++;
		}
	}
	number_elements = k;
	return copy;
}

int Service::GetSizeOfAdoptionList(){
	return this->client_repo.GetAdoptionListSize();
}

int Service::GetPetSize()
{
	return this->employees_repo.GetPetsNumber();
}
