#pragma once
#include "Pet.h"
#include <iostream>

template <typename TElem> 
class DynamicVector {

private:
	TElem* elements;
	int size;
	int capacity;

	// Resizes the vector by doubling its capacity
	//Input: factor - integer
	//Output: the vector is resized
	void Resize(int factor=2) {
		this->capacity *= factor;
		TElem* copy = new TElem[this->capacity];
		for (int i = 0; i < this->size; i++)
			copy[i] = this->elements[i];
		delete[] this->elements;
		this->elements = copy;
	}  

public:
	// Default constructor
	//Input: capacity - integer
	//Output: a Dynamic Vector is created
	DynamicVector(int capacity = 10) {
		this->capacity = capacity;
		this->size = 0;
		this->elements = new TElem[capacity];
	}

	// Copy constructor for a Dynamic Vector
	//Input: dynamicVector - a Dynamic Vector
	//Output: a Dynamic Vector is copied
	DynamicVector(const DynamicVector& dynamicVector) {
		this->size = dynamicVector.size;
		this->capacity = dynamicVector.capacity;
		this->elements = new TElem[this->capacity];
		for (int i = 0; i < dynamicVector.size; i++) {
			this->elements[i] = dynamicVector.elements[i];
		}
	}

	// Destructor
	~DynamicVector() {
		delete[] this->elements;
	}

	//Assignment operator for a Dynamic Vector	
	//Input: dynamicVector - a Dynamic Vector
	//Output: the current Dynamic Vector is assigned the values of the one given as a parameter
	DynamicVector& operator=(const DynamicVector& dynamicVector) {
		if (this == &dynamicVector)
			return *this;

		this->size = dynamicVector.size;
		this->capacity = dynamicVector.capacity;

		delete[] this->elements;

		this->elements = new TElem[this->capacity];
		for (int i = 0; i < this->size; i++)
			this->elements[i] = dynamicVector.elements[i];

		return *this;
	}

	// Overloading the subscript operator
	//Input: position - integer
	//Output: the element on the position given as a parameter
	TElem& operator[](int position) {
		return this->elements[position];
	}

	// Adds an element to the current Dynamic Vector
	//Input: element - TElem
	//Output: the element is added to the current Dynamic Vector
	void AddElement(TElem element) {
		if (this->size == this->capacity)
			this->Resize();
		this->elements[this->size] = element;
		this->size++;
	}

	// Deletes an element from the current Dynamic Vector
	//Input: element - TElem
	//Output: the element is deleted from the current Dynamic Vector
	void DeleteElement(TElem element) {
		for (int i = 0; i < this->size; i++) {
			if (this->elements[i] == element) {
				this->elements[i] = this->elements[this->size - 1];
				this->size--;
				break;
			}
		}
	}

	//Returns the numbers of elements in the vector
	int GetSize() const {
		return this->size;
	}

	//Returns the elements of the vector
	TElem* GetElements() const {
		return this->elements;
	}
};