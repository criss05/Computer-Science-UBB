#include "Service.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

Service* CreateService(int length){
	Service* service = malloc(sizeof(Service));
	if (service == NULL)
		return NULL;

	Repository* repo = CreateRepository(length);
	if (repo == NULL)
		return NULL;

	DynamicArray* undo_stack = CreateDynamicArray(20, DestroyDynamicArray, NULL);
	if (undo_stack == NULL)
		return NULL;

	DynamicArray* redo_stack = CreateDynamicArray(20, DestroyDynamicArray, NULL);
	if (redo_stack == NULL)
		return NULL;

	service->repo = repo;
	service->undo_stack = undo_stack;
	service->redo_stack = redo_stack;
	service->length;
	return service;
}

void DestroyService(Service* service){
	if (service == NULL)
		return;
	DestroyDynamicArray(service->undo_stack);
	DestroyDynamicArray(service->redo_stack);
	DestroyRepository(service->repo);
	free(service);
}

void AddMedicine(Service* service, char* name, int concentration, int quantity, int price) {
	AddElementToDA(service->undo_stack, CopyDynamicArray(GetDynamicArray(service->repo)));
	Medicine* medicine = CreateMedicine(name, concentration, quantity, price);
	AddMedicineToRepo(service->repo, medicine);
}

int DeleteMedicine(Service* service, char* name, int concetration){
	
	Medicine* medicine = GetMedicine(service->repo, name, concetration);
	if (medicine == NULL)
		return -1;
	AddElementToDA(service->undo_stack, CopyDynamicArray(GetDynamicArray(service->repo)));
	int error = DeleteMedicineFromRepo(service->repo, medicine);
	return error;
}

int UpdateMedicine(Service* service, char* name, int concetration, int new_quantity, int new_price){
	Medicine* medicine = GetMedicine(service->repo, name, concetration);
	if (medicine == NULL)
		return - 1;
	AddElementToDA(service->undo_stack, CopyDynamicArray(GetDynamicArray(service->repo)));
	int error = UpdateMedicineInRepo(service->repo, name, concetration, new_quantity, new_price);
	return error;
}

int CompareAscending(Medicine* firts_medicine, Medicine* second_medicine){
	if (strcmp(firts_medicine->name, second_medicine->name) > 0)
		return 1;
	return 0;
}

int CompareDescending(Medicine* firts_medicine, Medicine* second_medicine){
	if (strcmp(firts_medicine->name, second_medicine->name) < 0)
		return 1;
	return 0;
}

int FilterByQuantity(Medicine* medicine, int quantity){
	if (medicine->quantity < quantity)
		return 1;
	return 0;
}

int FilterByPrice(Medicine* medicine, int price){
	if (medicine->price < price)
		return 1;
	return 0;
}

Medicine** GetAll(Service* service){
	return GetMedicines(service->repo);
}

int GetLength(Service* service) {
	return GetMedicinesLength(service->repo);
}

Medicine** GetAllWithGivenString(Service* service, char given_string[], int* number_elements, CompareFunction compare_function)
{
	*number_elements = 0;
	Medicine* aux;
	Medicine** medicines = GetMedicines(service->repo);
	for (int i = 0; i < GetMedicinesLength(service->repo)-1; i++)
		for (int j = i + 1; j < GetMedicinesLength(service->repo); j++)
			if (compare_function(medicines[i], medicines[j]) >0) {
				aux = medicines[i];
				medicines[i] = medicines[j];
				medicines[j] = aux;
			}
	if (strlen(given_string) == 0) {
		*number_elements = GetMedicinesLength(service->repo);
		Medicine** copy_list = malloc(sizeof(Medicine*) * (*number_elements));
		if(copy_list == NULL)
			return NULL;
		int k = 0;
		for (int i=0; i<GetMedicinesLength(service->repo); i++)
			copy_list[k++] = medicines[i];
		return copy_list;
	}
	else {
		for (int i = 0; i < GetMedicinesLength(service->repo); i++)
			if (strstr(medicines[i]->name, given_string)!=0)
				(*number_elements) ++;
		Medicine** copy_list = malloc(sizeof(Medicine*) * (*number_elements));
		if (copy_list == NULL)
			return NULL;
		int k = 0;
		for (int i = 0; i < GetMedicinesLength(service->repo); i++)
			if (strstr(medicines[i]->name, given_string)) {
				copy_list[k] = medicines[i];
				k++;
			}
		return copy_list;
	}
	return;
}

Medicine** GetAllFiltered(Service* service, int value, int* number_elements, FilterFunction filter_function)
{	
	*number_elements = 0;
	Medicine** medicines = GetMedicines(service->repo);
	for (int i = 0; i < GetMedicinesLength(service->repo); i++)
		if (filter_function(medicines[i], value))
			(*number_elements)++;
	Medicine** copy_list = malloc(sizeof(Medicine*) * (*number_elements));
	if (copy_list == NULL)
		return;
	int k = 0;
	for (int i = 0; i < GetMedicinesLength(service->repo); i++)
		if (filter_function(medicines[i], value)) {
			copy_list[k] = medicines[i];
			k++;
		}
	return copy_list;
}

int Undo(Service* service) {
	if (GetSizeOfDA(service->undo_stack) == 0)
		return -1;
	DynamicArray* last_operation = GetElementFromPosition(service->undo_stack, GetSizeOfDA(service->undo_stack) - 1);
	AddElementToDA(service->redo_stack, CopyDynamicArray(GetDynamicArray(service->repo)));
	DestroyDynamicArray(GetDynamicArray(service->repo));
	SetDynamicArray(service->repo, CopyDynamicArray(last_operation));
	DeteleElementFromPosition(service->undo_stack, GetSizeOfDA(service->undo_stack) - 1);
	return 1;
}

int Redo(Service* service) {
	if (GetSizeOfDA(service->redo_stack) == 0)
		return -1;
	DynamicArray* last_operation = GetElementFromPosition(service->redo_stack, GetSizeOfDA(service->redo_stack) - 1);
	AddElementToDA(service->undo_stack, CopyDynamicArray(GetDynamicArray(service->repo)));
	DestroyDynamicArray(GetDynamicArray(service->repo));
	SetDynamicArray(service->repo, CopyDynamicArray(last_operation));
	DeteleElementFromPosition(service->redo_stack, GetSizeOfDA(service->redo_stack) - 1);
	return 1;
}

void testFunctions(Service* service)
{

	//test add
	AddMedicine(service, "Paracetamol", 10, 100, 5);
	AddMedicine(service, "Nurofen", 20, 50, 10);
	AddMedicine(service, "Aspirina", 30, 30, 15);
	assert(GetLength(service) == 3);
	assert(strcmp(GetAll(service)[0]->name, "Paracetamol") == 0);
	assert(strcmp(GetAll(service)[1]->name, "Nurofen") == 0);
	assert(strcmp(GetAll(service)[2]->name, "Aspirina") == 0);

	//test delete
	DeleteMedicine(service, "Nurofen", 20);
	assert(GetLength(service) == 2);
	assert(strcmp(GetAll(service)[1]->name, "Nurofen") != 0);
	
	//test update
	UpdateMedicine(service, "Paracetamol", 10, 200, 10);
	assert(GetAll(service)[0]->quantity == 200);

	//test undo
	Undo(service);
	assert(GetAll(service)[0]->quantity == 100);
	Undo(service);
	assert(GetLength(service) == 3);
	assert(strcmp(GetAll(service)[1]->name, "Nurofen") == 0);

	//test redo
	Redo(service);
	assert(GetLength(service) == 2);
	assert(strcmp(GetAll(service)[1]->name, "Nurofen") != 0);

	//test filter
	int number_elements0 = 0;
	Medicine** filtered_list1 = GetAllFiltered(service, 40, &number_elements0, FilterByQuantity);
	assert(number_elements0 == 1);
	assert(strcmp(filtered_list1[0]->name, "Aspirina") == 0);

	int number_elements1 = 0;
	Medicine** filtered_list2 = GetAllFiltered(service, 11, &number_elements1, FilterByPrice);
	assert(number_elements1 == 1);
	assert(strcmp(filtered_list2[0]->name, "Paracetamol") == 0);   

	//test sort
	int number_elements2 = 0;
	Medicine** sorted_list1 = GetAllWithGivenString(service, "a", &number_elements2, CompareAscending);
	assert(strcmp(sorted_list1[0]->name, "Aspirina") == 0);
	assert(strcmp(sorted_list1[1]->name, "Paracetamol") == 0);

	int number_elements3 = 0;
	Medicine** sorted_list2 = GetAllWithGivenString(service, "a", &number_elements3, CompareDescending);
	assert(strcmp(sorted_list2[0]->name, "Paracetamol") == 0);
	assert(strcmp(sorted_list2[1]->name, "Aspirina") == 0);


	printf("The tests passed successfully!\n");
}
