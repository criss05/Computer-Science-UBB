#pragma once
#include "Repo.h"

typedef int (*CompareFunction)(Medicine*, Medicine*);
typedef int (*FilterFunction)(Medicine*, int);

typedef struct {
	Repository* repo;
	int length;
	DynamicArray* undo_stack;
	DynamicArray* redo_stack;
}Service;

// Creates a service
//Parameters: length - integer, the length of the repository
//Returns a pointer to the service
//Returns NULL if the service could not be created
Service* CreateService(int length);

// Destroys a service
//Parameters: service - pointer to the service
void DestroyService(Service* service);

// Adds a medicine to the repository
//Parameters: service - pointer to the service
//			  name - pointer to a string, the name of the medicine
//			  concentration - integer, the concentration of the medicine
//			  quantity - integer, the quantity of the medicine
//			  price - integer, the price of the medicine
void AddMedicine(Service* service, char* name, int concentration, int quantity, int price);

// Deletes a medicine from the repository
//Parameters: service - pointer to the service
//			  name - pointer to a string, the name of the medicine
//			  concentration - integer, the concentration of the medicine
//Returns 1 if the medicine was deleted
//Returns -1 if the medicine could not be found
int DeleteMedicine(Service* service, char* name, int concetration);

// Updates a medicine from the repository
//Parameters: service - pointer to the service
//			  name - pointer to a string, the name of the medicine
//			  concentration - integer, the concentration of the medicine
//			  new_quantity - integer, the new quantity of the medicine
//			  new_price - integer, the new price of the medicine
//Returns 1 if the medicine was updated
//Returns -1 if the medicine could not be found
int UpdateMedicine(Service* service, char* name, int concetration, int new_quantity, int new_price);


//Checks if the first medicine is bigger then the second one
// Parameters: first_medicine - pointer to the first medicine
// 		   second_medicine - pointer to the second medicine
//Returns 1 if the first medicine is bigger
//Returns 0 if the first medicine is smaller
int CompareAscending(Medicine* firts_medicine, Medicine* second_medicine);

//Checks if the first medicine is smaller then the second one
// Parameters: first_medicine - pointer to the first medicine
// 		   second_medicine - pointer to the second medicine
//Returns 1 if the first medicine is smaller
//Returns 0 if the first medicine is bigger
int CompareDescending(Medicine* firts_medicine, Medicine* second_medicine);

//Filters the medicines by quantity
//Parameters: medicine - pointer to the medicine
//			  quantity - integer, the quantity to filter by
//Returns 1 if the medicine has the quantity bigger then the given one
//Returns 0 if the medicine has the quantity smaller then the given one
int FilterByQuantity(Medicine* medicine, int quantity);

//Filters the medicines by price
//Parameters: medicine - pointer to the medicine
//			  price - integer, the price to filter by
//Returns 1 if the medicine has the price bigger then the given one
//Returns 0 if the medicine has the price smaller then the given one
int FilterByPrice(Medicine* medicine, int price);

// Gets all the medicines from the repository
//Parameters: service - pointer to the service
//Returns a pointer to an array of pointers to medicines
Medicine** GetAll(Service* service);

// Gets the length of the repository
//Parameters: service - pointer to the service
//Returns the length of the repository
int GetLength(Service* service);

//Gets the medicines from the repository that have the given string in their name
//Parameters: service - pointer to the service
//			  given_string - pointer to a string, the string to search for
//			  number_elements - pointer to an integer, the number of elements which have the property
//			  compare_function - pointer to a function that compares two medicines
//Returns a pointer to an array of pointers to medicines
Medicine** GetAllWithGivenString(Service* service, char given_string[], int* number_elements, CompareFunction compare_function);

//Gets the medicines from the repository that is smaller then the given value
//Parameters: service - pointer to the service
//			  value - integer, the value to compare with
//			  number_elements - pointer to an integer, the number of elements which have the property
//			  filter_function - pointer to a function that filters the medicines using the given value
//Returns a pointer to an array of pointers to medicines
Medicine** GetAllFiltered(Service* service, int value, int* number_elements, FilterFunction filter_function);

//Undoes the last operation
//Parameters: service - pointer to the service
//Returns 1 if the operation was undone
//Returns -1 if the operation could not be undone
int Undo(Service* service);

//Redoes the last operation
//Parameters: service - pointer to the service
//Returns 1 if the operation was redone
//Returns -1 if the operation could not be redone
int Redo(Service* service);

void testFunctions(Service* service);