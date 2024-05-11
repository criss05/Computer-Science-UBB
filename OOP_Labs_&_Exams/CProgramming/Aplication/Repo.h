#pragma once
#include "DynamicArray.h"

typedef struct {
	int length;
	DynamicArray* array;
}Repository;

//Creates a repository
//Parameters: length - integer, the length of the repository
//Returns: a pointer to the repository
Repository* CreateRepository(length);

//Destroys a repository
//Parameters: repo - pointer to the repository
void DestroyRepository(Repository* repo);

//Adds a medicine to the repository
//Parameters: repo - pointer to the repository, 
//			 medicine - pointer to the medicine
//If the medicine is already in the repository, the quantity is updated
void AddMedicineToRepo(Repository* repo, Medicine* medicine);

//Deletes a medicine from the repository
//Parameters: repo - pointer to the repository,
//			 medicine - pointer to the medicine
//Returns: 1 if the medicine was deleted, -1 otherwise
int DeleteMedicineFromRepo(Repository* repo, Medicine* medicine);

//Updates the quantity of a medicine in the repository
//Parameters: repo - pointer to the repository,
//			 name - string, the name of the medicine,
//			 concentration - integer, the concentration of the medicine,
//			 new_quantity - integer, the new quantity of the medicine
//           new_price - integer, the new price of the medicine
//Returns: 1 if the medicine was updated, - otherwise
int UpdateMedicineInRepo(Repository* repo, char* name, int concetration, int new_quantity, int new_price);

//Gets the length of the repository
//Parameters: repo - pointer to the repository
//Returns: the length of the repository
int GetMedicinesLength(Repository* repo);

//Gets a medicine from the repository
//Parameters: repo - pointer to the repository,
//			 name - string, the name of the medicine,
//			 concentration - integer, the concentration of the medicine
//Returns: a pointer to the medicine
//		 NULL if the medicine is not in the repository
Medicine* GetMedicine(Repository* repo, char* name, int ocncetration);

//Gets all the medicines from the repository
//Parameters: repo - pointer to the repository
//Returns: a pointer to the array of medicines
Medicine** GetMedicines(Repository* repo);

//Gets the dynamic array from the repository
//Parameters: repo - pointer to the repository
//Returns: a pointer to the dynamic array
DynamicArray* GetDynamicArray(Repository* repo);

//Sets the dynamic array of the repository
//Parameters: repo - pointer to the repository,
//			 array - pointer to the dynamic array
void SetDynamicArray(Repository* repo, DynamicArray* array);