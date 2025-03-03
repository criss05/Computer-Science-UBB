#include "Pet.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

Pet::Pet(){
	this->breed = "";
	this->name = "";
	this->age = 0;
	this->photograph = "";
}

Pet::Pet(const std::string& breed, const std::string& name, int age, const std::string& photograph){
	this->breed = breed;
	this->name = name;
	this->age = age;
	this->photograph = photograph;
}

Pet::Pet(const Pet& pet){
	this->breed = pet.breed;
	this->name = pet.name;
	this->age = pet.age;
	this->photograph = pet.photograph;
}


std::string Pet::GetBreed() const{
	return this->breed;
}

std::string Pet::GetName() const{
	return this->name;
}

int Pet::GetAge() const{
	return this->age;
}

std::string Pet::GetPhotograph() const{
	return this->photograph;
}

void Pet::SetBreed(const std::string& new_breed){
	this->breed = new_breed;
}

void Pet::SetName(const std::string& new_name){
	this->name = new_name;
}

void Pet::SetAge(int new_age){
	this->age = new_age;
}

void Pet::SetPhotograph(const std::string& new_photograph){
	this->photograph = new_photograph;
}

bool Pet::operator==(const Pet& pet){
	if (this->name == pet.name && this->breed == pet.breed) 
		return true;
	return false;
}

Pet& Pet::operator=(const Pet& pet){
	this->breed = pet.breed;
	this->name = pet.name;
	this->age = pet.age;
	this->photograph = pet.photograph;
	return *this;
}


std::ostream& operator<<(std::ostream& stream, const Pet& pet){
	stream << pet.breed + "|" + pet.name + "|" + std::to_string(pet.age) + "|" + pet.photograph + "\n";
	return stream;
}

vector<string> tokenize(string str, char delimiter) {
	vector<string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter)) {
		result.push_back(token);
	}
	return result;
}

std::istream& operator>>(std::istream& stream, Pet& pet){
	std::string line;
	getline(stream, line);
	vector<string> tokens = tokenize(line, ',' );

	if (tokens.size() != 4) {
		return stream;
	}
	pet.breed = tokens[0];
	pet.name = tokens[1];
	pet.age = stoi(tokens[2]);
	pet.photograph = tokens[3];
}