#include "Medicine.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Medicine* CreateMedicine(char* name, int concentration, int quantity, int price) {
	Medicine* medicine = malloc(sizeof(Medicine));
	if (medicine == NULL)
		return NULL;
	medicine->name = malloc(sizeof(char) * (strlen(name)+1));
	if (medicine->name == NULL){
		free(medicine);
		return NULL;
	}
	strcpy(medicine->name, name);
	medicine->concentration = concentration;
	medicine->quantity = quantity;
	medicine->price = price;
	return medicine;
}

void DestroyMedicine(Medicine* medicine) {
	if (medicine == NULL)
		return NULL;
	free(medicine->name);
	free(medicine);
}

char* GetName(Medicine* medicine) {
	return medicine->name;
}

int GetConcentration(Medicine* medicine) {
	return medicine->concentration;
}

int GetQuantity(Medicine* medicine) {
	return medicine->quantity;
}

int GetPrice(Medicine* medicine) {
	return medicine->price;
}

void SetName(Medicine* medicine, char* name){
	strcpy(medicine->name, name);
}

void SetConcentration(Medicine* medicine, int concentration){
	medicine->concentration = concentration;
}

void SetQuantity(Medicine* medicine, int quantity){
	medicine->quantity = quantity;
}

void SetPrice(Medicine* medicine, int price){
	medicine->price = price;
}

void PrintMedicine(Medicine* medicine, char string[]) {
	sprintf(string, "Name: %s  Concentration: %d  Quantity: %d  Price: %d\n", medicine->name, medicine->concentration, medicine->quantity, medicine->price);
	//return string;
}

int EqualMedicine(Medicine* first_medicine, Medicine* second_medicine) {
	if (first_medicine == NULL || second_medicine == NULL)
		return 0;
	if (strcmp(first_medicine->name, second_medicine->name)==0 && (first_medicine->concentration == second_medicine->concentration))
		return 1;
	return 0;
}

Medicine* CopyMedicine(Medicine* medicine){
	if (medicine == NULL)
		return NULL;
	return CreateMedicine(medicine->name, medicine->concentration, medicine->quantity, medicine->price);
}
