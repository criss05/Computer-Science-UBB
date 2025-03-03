#include "ClientRepository.h"
#include "RepoException.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <cstdlib>

using namespace std;

void ClientRepository::AdoptPet(Pet pet){
	this->adopted.push_back(pet);
}

vector<Pet> ClientRepository::GetAdoptionList(){
	return this->adopted;
}

int ClientRepository::GetAdoptionListSize(){
	return this->adopted.size();
}

void ClientRepositoryCSV::AdoptPet(Pet pet){
	ClientRepository::AdoptPet(pet);
	this->WriteToFile();
}

std::vector<Pet> ClientRepositoryCSV::GetAdoptionList()
{
	return ClientRepository::GetAdoptionList();
}

int ClientRepositoryCSV::GetAdoptionListSize()
{
	return ClientRepository::GetAdoptionListSize();
}

void ClientRepositoryCSV::WriteToFile(){
	ofstream file(this->file_name);
	if (!file.is_open())
		throw FileException("The file couldn't be opened.\n");
	for (auto pet : this->adopted)
		file << pet.GetBreed() << "," << pet.GetName() << "," << to_string(pet.GetAge()) << "," << pet.GetPhotograph() << "\n";
	file.close();
}

void ClientRepositoryCSV::OpenAdoptionList(){
	//system(string("notepad \"adoption_list.csv\"").c_str());
	ShellExecuteA(NULL, NULL, "C:\\Windows\\notepad.exe", "adoption_list.csv", NULL, SW_SHOWMAXIMIZED);
	return;
}

void ClientRepositoryHTML::AdoptPet(Pet pet){
	ClientRepository::AdoptPet(pet);
	this->WriteToFile();
}

std::vector<Pet> ClientRepositoryHTML::GetAdoptionList()
{
	return ClientRepository::GetAdoptionList();
}

int ClientRepositoryHTML::GetAdoptionListSize()
{
	return ClientRepository::GetAdoptionListSize();
}

void ClientRepositoryHTML::WriteToFile(){
	ofstream file(this->file_name);
	if (!file.is_open())
		throw FileException("The file couldn't be opened.");
	file << "<!DOCTYPE html>\n";
	file << "<html>\n";
	file << "<head>\n";
	file << "<title>Adoption List</title>\n";
	file << "</head>\n";
	file << "<body>\n";
	file << "<table border=\"1\">\n";
	file << "<tr>\n";
	file << "<td>Breed</td>\n";
	file << "<td>Name</td>\n";
	file << "<td>Age</td>\n";
	file << "<td>Photograph</td>\n";
	file << "</tr>\n";

	for (auto pet : this->adopted) {
		file << "<tr>\n";
		file << "<td>" << pet.GetBreed() << "</td>\n";
		file << "<td>" << pet.GetName() << "</td>\n";
		file << "<td>" << to_string(pet.GetAge()) << "</td>\n";
		file << "<td>" << pet.GetPhotograph() << "</td>\n";
	}
	file << "</table>\n";
	file << "</body>\n";
	file << "</html>\n";
	file.close();
}

void ClientRepositoryHTML::OpenAdoptionList(){
	ShellExecuteA(NULL, NULL, "C:\\Program Files\\Mozilla Firefox\\firefox.exe", "adoption_list.html", NULL, SW_SHOWMAXIMIZED);
	return;
}
