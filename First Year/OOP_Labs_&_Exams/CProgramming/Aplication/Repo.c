#include "Repo.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Repository* CreateRepository(length)
{
	Repository* repo = malloc(sizeof(Repository));
	repo->array = CreateDynamicArray(length, DestroyMedicine, EqualMedicine);
	repo->length = length;
	return repo;
}

void DestroyRepository(Repository* repo){
	DestroyDynamicArray(repo->array);
	free(repo);
}

void AddMedicineToRepo(Repository* repo, Medicine* medicine) {
	Medicine** medicines = GetElementsOfDA(repo->array);
	int position = -1;
	for (int i = 0; i < GetSizeOfDA(repo->array); i++)
		if (EqualMedicine(medicine, medicines[i])) {
			position = i;
		}
	if (position != -1) {
		SetQuantity(medicines[position], medicine->quantity + medicines[position]->quantity);
		DestroyMedicine(medicine);
	}
	else {
		AddElementToDA(repo->array, medicine);
	}
}

int DeleteMedicineFromRepo(Repository* repo, Medicine* medicine){
	int is_deleted = DeleteElementFromDA(repo->array, medicine);
	return is_deleted;
}

int UpdateMedicineInRepo(Repository* repo, char* name, int concentration, int new_quantity, int new_price){
	Medicine** medicines = GetElementsOfDA(repo->array);
	int position = -1;
	for (int i = 0; i < GetSizeOfDA(repo->array); i++)
		if (strcmp(name, medicines[i]->name)==0 && medicines[i]->concentration == concentration) {
			SetQuantity(medicines[i], new_quantity);
			SetPrice(medicines[i], new_price);
			position = i;
		}
	if (position == -1)
		return -1;
	return 1;
}

int GetMedicinesLength(Repository* repo){
	return GetSizeOfDA(repo->array);
}

Medicine* GetMedicine(Repository* repo, char* name, int concetration){
	
	Medicine** medicines = GetElementsOfDA(repo->array);
	for (int i = 0; i < GetSizeOfDA(repo->array); i++)
		if (strcmp(medicines[i]->name, name) == 0 && medicines[i]->concentration == concetration) {
			return medicines[i];
		}
	return NULL;
}

Medicine** GetMedicines(Repository* repo)
{
	return GetElementsOfDA(repo->array);
}

void SetDynamicArray(Repository* repo, DynamicArray* array) {
	repo->array = array;
}

DynamicArray* GetDynamicArray(Repository* repo) {
	return repo->array;
}