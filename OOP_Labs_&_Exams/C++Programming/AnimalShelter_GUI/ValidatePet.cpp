#include "ValidatePet.h"
using namespace std;

void ValidatePet::validate(const Pet& pet){
	vector<string> error;
	//if (toupper(pet.GetName().front()))
	if(!isupper(pet.GetName()[0]))
		error.push_back("The name should start with capital letter\n");

	if (pet.GetAge() <= 0)
		error.push_back("The age should be a positive integer\n");

	if (pet.GetBreed().size() < 3)
		error.push_back("The breed should not have less than 3 characters\n");

	if (pet.GetPhotograph().find("www") != 0 && pet.GetPhotograph().find("https") != 0)
		error.push_back("The photo link must start with www or https\n");
	
	if (error.size() > 0)
		throw PetException(error);
}

std::vector<std::string> PetException::getError() const{

	return this->error;
}
