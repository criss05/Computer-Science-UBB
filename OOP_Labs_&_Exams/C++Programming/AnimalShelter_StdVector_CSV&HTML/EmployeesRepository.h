#pragma once
#include <vector>
#include "Pet.h"

using namespace std;

class EmployeesRepositoryBase {
protected:
	std::vector<Pet> pets;
public:
	//Default constructor
	EmployeesRepositoryBase() {};

	//Add a pet to the repository
	//Input: pet - Pet
	//Throws: exception if the pet already exists
	virtual void AddPetToRepo(Pet pet) = 0;

	//Delete a pet from the repository
	//Input: pet - Pet
	//Throws: exception if the pet does not exist
	virtual void DeletePetFromRepo(Pet pet) = 0;

	//Get a pet from the repository
	//Input: name - the pet name,
	//		 breed - the pet breed
	//Output: the pet with the given name and breed
	virtual Pet& GetPetFromRepo(const std::string& name, std::string breed) = 0;

	//Get the pets from the repository
	//Output: the pets from the repository
	virtual vector<Pet> GetPetsFromRepo() = 0;

	//Get the number of pets from the repository
	//Output: the number of pets from the repository
	virtual int GetPetsNumber() = 0;

	//Write to file
	//Output: the pets from the repository are written to the file
	virtual void WriteToFile() = 0;

	//Read from file
	//Output: the pets from the file are read to the repository
	virtual void ReadFromFile() = 0;
};

class EmployeesRepository : public EmployeesRepositoryBase {
public:
	//Function that adds a pet to the repository
	//Input: pet - Pet
	//Throws: exception if the pet already exists
	void AddPetToRepo(Pet pet) override;

	//Function that deletes a pet from the repository
	//Input: pet - Pet
	//Throws: exception if the pet does not exist
	void DeletePetFromRepo(Pet pet) override;
	
	//Function that returns the pet with the given name and breed
	//Input: name - the pet name,
	//		 breed - the pet breed
	//Output: the pet with the given name and breed
	Pet& GetPetFromRepo(const std::string& name, std::string breed) override;

	//Function that returns the pets from the repository
	//Output: the pets from the repository
	vector<Pet> GetPetsFromRepo() override;

	//Function that returns the number of pets from the repository
	int GetPetsNumber() override;

	//Function that writes the pets from the repository to the file
	//Output: the pets from the repository are written to the file
	void WriteToFile() override {}

	//Function that reads the pets from the file to the repository
	//Output: the pets from the file are read to the repository
	void ReadFromFile() override {}
};


class FileEmployeesRepository : public EmployeesRepository {
protected:
	std::string file_name;
public:

	//Constructor
	//Input: file_name - string
	FileEmployeesRepository(std::string file_name) : file_name{ file_name } {}


	//Function that writes the pets from the repository to the file
	//Output: the pets from the repository are written to the file
	void AddPetToRepo(Pet pet) override;

	//Function that deletes a pet from the repository
	//Input: pet - Pet
	void DeletePetFromRepo(Pet pet) override;

	//Function that returns the pet with the given name and breed
	//Input: name - the pet name,
	//		 breed - the pet breed
	//Output: the pet with the given name and breed
	Pet& GetPetFromRepo(const std::string& name, std::string breed) override;

	//Function that returns the pets from the repository
	//Output: the pets from the repository
	vector<Pet> GetPetsFromRepo() override;

	//Function that returns the number of pets from the repository
	//Output: the number of pets from the repository
	int GetPetsNumber() override;

	//Function that writes the pets from the repository to the file
	//Output: the pets from the repository are written to the file
	void WriteToFile() override;

	//Function that reads the pets from the file to the repository
	//Output: the pets from the file are read to the repository
	void ReadFromFile() override;
}; 