#pragma once
#include "DynamicVector.h"

class EmployeesRepository {
private:
	DynamicVector<Pet> pets;

public:
	//Function that adds a pet to the repository
	//Input: pet - Pet
	//Throws: exception if the pet already exists
	void AddPetToRepo(Pet pet);

	//Function that deletes a pet from the repository
	//Input: pet - Pet
	//Throws: exception if the pet does not exist
	void DeletePetFromRepo(Pet pet);
	
	//Function that returns the pet with the given name and breed
	//Input: name - the pet name,
	//		 breed - the pet breed
	//Output: the pet with the given name and breed
	Pet& GetPetFromRepo(const std::string& name, std::string breed);

	//Function that returns the pets from the repository
	//Output: the pets from the repository
	Pet* GetPetsFromRepo();

	//Function that returns the number of pets from the repository
	int GetPetsNumber();
};