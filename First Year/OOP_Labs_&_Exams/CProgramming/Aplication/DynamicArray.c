#include "DynamicArray.h"
#include <stdlib.h>
#include <stdio.h>

DynamicArray* CreateDynamicArray(int capacity, DestroyFunction function, EqualityFunction equfucntion){

	DynamicArray* array = malloc(sizeof(DynamicArray));
	if (array == NULL)
		return NULL;
	array->capacity = capacity;
	array->size = 0;
	array->elements = malloc(sizeof(TElem) * capacity);
	if (array->elements == NULL) {
		free(array);
		return NULL;
	}
	array->destroyFct = function;
	array->equalityFct = equfucntion;
	return array;
}

void DestroyDynamicArray(DynamicArray* array){
	if (array == NULL)
		return;
	for (int i = 0; i < array->size; i++)
		array->destroyFct(array->elements[i]);
	free(array->elements);
	free(array);
}

void Resize(DynamicArray* array) {
	if (array == NULL)
		return;
	if (array->elements == NULL)
		return;
	array->capacity *= 2;
	TElem* aux = realloc(array->elements, sizeof(TElem) * array->capacity);
	if (aux == NULL)
		return;
	array->elements = aux;
}

void AddElementToDA(DynamicArray* array, TElem element){
	if (array == NULL)
		return;
	if (array->elements == NULL)
		return;
	if (array->size == array->capacity)
		Resize(array);
	array->elements[array->size++] = element;
}

int DeleteElementFromDA(DynamicArray* array, TElem element) {
	if (array == NULL)
		return -1;
	if (array->elements == NULL)
		return -1;
	int position = -1;
	
	for (int i = 0; i <array->size; i++)
		if (array->equalityFct(array->elements[i], element) == 1){
		position = i;
		}
	if (position == -1)
		return -1;
	array->destroyFct(array->elements[position]);
	for (int i = position; i < array->size; i++)
		array->elements[i] = array->elements[i + 1];
	array->size -= 1;
	return 1;
	//ToDo shink function
}

int GetSizeOfDA(DynamicArray* array)
{
	if (array == NULL)
		return -99;
	return array->size;
}

TElem* GetElementsOfDA(DynamicArray* array){
	if (array == NULL)
		return NULL;
	if (array->elements == NULL)
		return NULL;
	return array->elements;
}

TElem GetElementFromPosition(DynamicArray* array, int position){
	if (array == NULL)
		return NULL;
	if (position < 0 || position >= array->size)
		return NULL;
	return array->elements[position];
}

void DeteleElementFromPosition(DynamicArray* array, int position){
	if (array == NULL)
		return;
	if (position < 0 || position >= array->size)
		return;
	array->destroyFct(array->elements[position]);
	for (int i = position; i < array->size - 1; i++)
		array->elements[i] = array->elements[i + 1];
	array->size -= 1;
}

DynamicArray* CopyDynamicArray(DynamicArray* array){
	if (array == NULL)
		return NULL;
	DynamicArray* copy_array = CreateDynamicArray(array->capacity, DestroyMedicine, EqualMedicine);
	if (copy_array == NULL)
		return NULL;
	copy_array->size = array->size;
	for (int i = 0; i < array->size; i++)
		copy_array->elements[i] = CopyMedicine(array->elements[i]);
	return copy_array;
}