#include "ClientRepository.h"
#include <iostream>

void ClientRepository::Adoptpet(Pet pet){
	this->adopted.AddElement(pet);
}

Pet* ClientRepository::GetAdoptionList(){
	return this->adopted.GetElements();
}

int ClientRepository::GetAdoptionListSize(){
	return this->adopted.GetSize();
}
