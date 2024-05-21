#include "EmployeesRepository.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "RepoException.h"

using namespace std;

void EmployeesRepository::AddPetToRepo(Pet pet) {
	auto it = find(this->pets.begin(), this->pets.end(), Pet{ pet.GetBreed(),pet.GetName(), 0, "" });
	if (it != this->pets.end())
		throw DuplicatePetException();
	this->pets.push_back(pet);
}

void EmployeesRepository::DeletePetFromRepo(Pet pet) {
	auto it = find(this->pets.begin(), this->pets.end(), pet);
	if (it != this->pets.end())
		this->pets.erase(it);
	else
		throw InexistentPetException();
}

Pet& EmployeesRepository::GetPetFromRepo(const std::string& name, std::string breed) {
	auto it = find(this->pets.begin(), this->pets.end(), Pet{breed,name, 0, ""});
	if (it == this->pets.end())
		throw InexistentPetException();
	return *it;
}

vector<Pet> EmployeesRepository::GetPetsFromRepo() {
	return this->pets;
}

int EmployeesRepository::GetPetsNumber() {
	return this->pets.size();
}

void FileEmployeesRepository::AddPetToRepo(Pet pet){
	EmployeesRepository::AddPetToRepo(pet);
	this->WriteToFile();
}

void FileEmployeesRepository::DeletePetFromRepo(Pet pet){
	EmployeesRepository::DeletePetFromRepo(pet);
	this->WriteToFile();
}

Pet& FileEmployeesRepository::GetPetFromRepo(const std::string& name, std::string breed){
	return EmployeesRepository::GetPetFromRepo(name, breed);
}

vector<Pet> FileEmployeesRepository::GetPetsFromRepo(){
	return EmployeesRepository::GetPetsFromRepo();
}

int FileEmployeesRepository::GetPetsNumber(){
	return EmployeesRepository::GetPetsNumber();
}

void FileEmployeesRepository::WriteToFile(){
	ofstream file(this->file_name);
	if (!file.is_open())
		throw FileException("The file couldn't be opened!");
	for (auto pet : this->pets)
		file << pet;
	file.close();
}

void FileEmployeesRepository::ReadFromFile(){
	ifstream file(this->file_name);
	if (!file.is_open())
		throw FileException("The file " + this->file_name +" couldn't be opened!");
	this->pets.clear();
	string line;
	while (getline(file, line)) {
		stringstream stream(line);
		string name, breed, age, photograph;
		getline(stream, breed, '|');
		getline(stream, name, '|');
		getline(stream, age, '|');
		getline(stream, photograph, '|');
		this->pets.push_back(Pet(breed, name, stoi(age), photograph));
	}
	file.close();
}
