#pragma once
#include "Service.h"

class UI {
private:
	Service service;

	void PrintMenu();
	void PrintAdminMenu();
	void PrintUserMenu();
	void PrintAdoptMenu();

	void AddDog();
	void DeleteDog();
	void UpdateDog();

	void PrintAllDogs();
	void PrintDogsOneByOne();
	void PrintYoungDogsWithGivenBreed();
	void PrintAdoptionList();

	void GeneratePets();
	int ValidateNumber(const std::string& string);
	void AddElementsInAdoptionList();

public:
	UI(Service service);

	void StartUI();
};
