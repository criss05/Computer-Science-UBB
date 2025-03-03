#pragma once
#include "Pet.h"
#include <vector>


class ClientRepositoryBase{
protected:
	std::vector<Pet> adopted;
public:
	ClientRepositoryBase() {};

	virtual void AdoptPet(Pet pet) = 0;
	virtual std::vector<Pet> GetAdoptionList() = 0;
	virtual int GetAdoptionListSize() = 0;

	virtual void WriteToFile() {}
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
	ClientRepositoryCSV(std::string file_name) : file_name{ file_name } {}
	
	void AdoptPet(Pet pet) override;
	std::vector<Pet> GetAdoptionList() override;
	int GetAdoptionListSize() override;

	void WriteToFile() override;
	void OpenAdoptionList() override;
};
class ClientRepositoryHTML : public ClientRepository {
protected:
	std::string file_name;
public:
	ClientRepositoryHTML(std::string file_name) : file_name{ file_name } {}

	void AdoptPet(Pet pet) override;
	std::vector<Pet> GetAdoptionList() override;
	int GetAdoptionListSize() override;

	void WriteToFile() override;
	void OpenAdoptionList() override;
};