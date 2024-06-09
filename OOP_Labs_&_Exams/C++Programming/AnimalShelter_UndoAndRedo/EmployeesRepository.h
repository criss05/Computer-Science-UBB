#pragma once
#include <vector>
#include "Pet.h"

using namespace std;

class EmployeesRepositoryBase {
protected:
	std::vector<Pet> pets;
public:
	EmployeesRepositoryBase() {};
	virtual void AddPetToRepo(Pet pet) = 0;
	virtual void DeletePetFromRepo(Pet pet) = 0;
	virtual Pet& GetPetFromRepo(const std::string& name, std::string breed) = 0;
	virtual vector<Pet> GetPetsFromRepo() = 0;
	virtual int GetPetsNumber() = 0;
	virtual void WriteToFile() = 0;
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

	void WriteToFile() override {}
	void ReadFromFile() override {}
};


class FileEmployeesRepository : public EmployeesRepository {
protected:
	std::string file_name;
public:
	FileEmployeesRepository(std::string file_name) : file_name{ file_name } {}

	void AddPetToRepo(Pet pet) override;
	void DeletePetFromRepo(Pet pet) override;
	Pet& GetPetFromRepo(const std::string& name, std::string breed) override;
	vector<Pet> GetPetsFromRepo() override;
	int GetPetsNumber() override;
	void WriteToFile() override;
	void ReadFromFile() override;
}; 