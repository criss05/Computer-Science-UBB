#pragma once
#include "Pet.h"
#include <vector>


class ClientRepositoryBase{
protected:
	std::vector<Pet> adopted;
public:
	//Constructor
	ClientRepositoryBase() {};

	//Function that adds a pet to the adoption list
	//Input: pet - Pet
	virtual void AdoptPet(Pet pet) = 0;

	//Function that returns the adoption list
	//Output: the adoption list
	virtual std::vector<Pet> GetAdoptionList() = 0;

	//Function that returns the size of the adoption list
	//Output: the size of the list
	virtual int GetAdoptionListSize() = 0;

	//Function that writes the adoption list to a file
	//Output: the adoption list is written to a file
	virtual void WriteToFile() {}

	//Function that opens the adoption list
	//Output: the adoption list is opened
	virtual void OpenAdoptionList() {}
};

class ClientRepository : public ClientRepositoryBase{
public:
	//Function that adds a pet to the adoption list
	//Input: pet - Pet
	void AdoptPet(Pet pet) override;

	//Function that returns the adoption list
	std::vector<Pet> GetAdoptionList() override;

	//Function that returns the size of the adoption list
	int GetAdoptionListSize() override;
};

class ClientRepositoryCSV: public ClientRepository{
protected:
	std::string file_name;
public:
	//Constructor
	//Input: file_name - string
	ClientRepositoryCSV(std::string file_name) : file_name{ file_name } {}
	
	//Function that adds a pet to the adoption list
	//Input: pet - Pet
	void AdoptPet(Pet pet) override;

	//Function that returns the adoption list
	//Output: the adoption list
	std::vector<Pet> GetAdoptionList() override;

	//Function that returns the size of the adoption list
	//Output: the size of the list
	int GetAdoptionListSize() override;

	//Function that writes the adoption list to a file
	//Output: the adoption list is written to a file
	void WriteToFile() override;

	//Function that opens the adoption list
	//Output: the adoption list is opened
	void OpenAdoptionList() override;
};
class ClientRepositoryHTML : public ClientRepository {
protected:
	std::string file_name;
public:
	//Constructor
	//Input: file_name - string
	ClientRepositoryHTML(std::string file_name) : file_name{ file_name } {}


	//Function that adds a pet to the adoption list
	//Input: pet - Pet
	void AdoptPet(Pet pet) override;
		
	//Function that returns the adoption list
	//Output: the adoption list
	std::vector<Pet> GetAdoptionList() override;

	//Function that returns the size of the adoption list
	//Output: the size of the list
	int GetAdoptionListSize() override;

	//Function that writes the adoption list to a file
	//Output: the adoption list is written to a file
	void WriteToFile() override;

	//Function that opens the adoption list
	//Output: the adoption list is opened
	void OpenAdoptionList() override;
};