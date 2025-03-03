#pragma once
#include "ClientRepository.h"
#include "EmployeesRepository.h"
#include "ValidatePet.h"

class Service {
private:
	ClientRepositoryBase* client_repo;
	EmployeesRepositoryBase* employees_repo;
	ValidatePet validator;

public:
	//Implicit constructor of the service
	Service();

	//Constructor of the service
	//Input: client_repo - the repository of the clients
	//		 employees_repo - the repository of the employees
	//Output: the service
	Service(ClientRepositoryBase* client_repo, EmployeesRepositoryBase* employees_repo);

	//Function that add a pet to the repository
	//Input: breed - the breed of the new pet
	//		 name - the name of the new pet
	//		 age - the age of the new pet
	//		 photograph - the photograph of the new pet
	void AddPet(const std::string& breed, const std::string& name, int age, const std::string& photograph);

	//Function that delete a pet from the repository
	//Input: breed - the breed of the pet to delete
	//		 name - the name of the pet to delete
	void DeletePet(const std::string& breed, const std::string& name);

	//Function that update a pet from the repository
	//Input: breed - the breed of the pet to update
	//		 name - the name of the pet to update
	//		 new_age - the new age of the pet
	//		 new_photograph - the new photograph of the pet
	void UpdatePet(const std::string& breed, const std::string& name, int new_age, const std::string& new_photograph);

	//Function that get all the pets from the repository
	//Output: the pets from the repository
	vector<Pet> GetAllPets();
	
	//Function that get all the pets from the adoption list of the client
	//Output: the pets from the adoption list of the client
	vector<Pet> GetPetsFromAdoptionList();

	//Function that adds a pet to the adoption list of the client
	//Input: pet - the pet to add to the adoption list
	void AdoptPet(Pet pet);

	//Function that get all the pets from the repository that are of a given breed and have an age less than a given age
	//Input: given_breed - the given breed
	//		 given_age - the given age
	//		 number_elements - the number of elements of the array
	//Output: the pets from the repository that are of a given breed and have an age less than a given age
	vector<Pet> GetYoungDogsOfGivenBreed(std::string given_breed, int given_age);

	//Function that returns the numebr of pets in the adoption list
	//Output: the number of pets in the adoption list
	int GetSizeOfAdoptionList();

	//Function that returns the number of pets from the employeer repository
	//Output: the number of pets from the employeer repository
	int GetPetSize();

	int GetNumberPetAge(int start_age, int end_age);

	void OpenAdoptionList();
	void ReadFromFileService();
};