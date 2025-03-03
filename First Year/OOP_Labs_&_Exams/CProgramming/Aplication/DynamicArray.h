#pragma once
#include "Medicine.h"


typedef void* TElem;

typedef void (*DestroyFunction)(TElem);
typedef int (*EqualityFunction)(TElem, TElem);

typedef struct {
	TElem* elements;
	int capacity;
	int size;
	DestroyFunction destroyFct;
	EqualityFunction equalityFct;
}DynamicArray;

//Creates a dynamic array
//Parameters: capacity - integer, the capacity of the dynamic array
//			  function - pointer to a function that destroys an element
//			  equfunction - pointer to a function that checks if two elements are equal
//Returns a pointer to the created dynamic array
DynamicArray* CreateDynamicArray(int capacity, DestroyFunction function, EqualityFunction equfunction);

//Destroys a dynamic array
//Parameters: array - pointer to the dynamic array
//Returns nothing
void DestroyDynamicArray(DynamicArray* array);

//Adds an element to the dynamic array
//Parameters: array - pointer to the dynamic array
//			  element - pointer to the element that will be added
void AddElementToDA(DynamicArray* array, TElem element);

//Deletes an element from the dynamic array
//Parameters: array - pointer to the dynamic array
//			  element - pointer to the element that will be deleted
//Returns 1 if the element was deleted, -1 otherwise
int DeleteElementFromDA(DynamicArray* array, TElem element);

//Gives the size of the dynamic array
//Parameters: array - pointer to the dynamic array
//Returns the size of the dynamic array
int GetSizeOfDA(DynamicArray* array);

//Gives the elements of the dynamic array
//Parameters: array - pointer to the dynamic array
//Returns a pointer to the elements of the dynamic array
TElem* GetElementsOfDA(DynamicArray* array);

//Gets the element from a certain position
//Parameters: array - pointer to the dynamic array
//			  position - integer, the position of the element
//Returns the element from the given position
TElem GetElementFromPosition(DynamicArray* array, int position);

//Deletes the element from a certain position
//Parameters: array - pointer to the dynamic array
//			  position - integer, the position of the element
void DeteleElementFromPosition(DynamicArray* array, int position);

//Copies a dynamic array
//Parameters: array - pointer to the dynamic array
//Returns a pointer to the copied dynamic array
DynamicArray* CopyDynamicArray(DynamicArray* array);