#pragma once
#include <vector>
#include "Pet.h"

class PetException {
private:
	std::vector<std::string> error;
public:
	PetException(std::vector<std::string> error) { this->error = error; }
	std::vector<std::string> getError() const;
};

class ValidatePet {
public:
	ValidatePet(){}
	static void validate(const Pet& pet);
};
