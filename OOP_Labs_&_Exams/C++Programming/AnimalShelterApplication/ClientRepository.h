#pragma once
#include "DynamicVector.h"

class ClientRepository {
private:
	DynamicVector<Pet> adopted;

public:
	//Function that adds a pet to the adoption list
	//Input: pet - Pet
	void Adoptpet(Pet pet);

	//Function that returns the adoption list
	Pet* GetAdoptionList();

	//Function that returns the size of the adoption list
	int GetAdoptionListSize();
};
