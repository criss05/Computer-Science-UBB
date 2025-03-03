#pragma once
#include <string>

class Pet {

private:
	std::string breed, name, photograph;
	int age;

public:
	Pet();
	//Default constructor
	//Input: breed - string, 
	//		 name - string,
	//		 age - integer,
	//		 photograph - string
	//Output: a pet is created
	Pet(const std::string& breed, const std::string& name, int age, const std::string& photograph);

	//Copy constructor
	//Input: pet - Pet
	//Output: a pet is copied
	Pet(const Pet& pet);

	//Returns the breed of the pet
	std::string GetBreed() const;

	//Returns the name of the pet
	std::string GetName() const;

	//Returns the age of the pet
	int GetAge() const;

	//Returns the photograph of the pet
	std::string GetPhotograph() const;

	//Sets the breed of the pet with a given one
	void SetBreed(const std::string& new_breed);

	//Sets the name of the pet with a given one
	void SetName(const std::string& new_name);

	//Sets the age of the pet with a given one
	void SetAge(int new_age);

	//Sets the photograph of the pet with a given one
	void SetPhotograph(const std::string& new_phptograph);

	//Overloading the equality operator
	//Input: pet - Pet
	//Output: true if the pets are equal, false otherwise
	//Two pets are equal if they have the same name and the same breed
	bool operator==(const Pet& pet);

	//Overloading the assignment operator
	//Input: pet - Pet
	Pet& operator=(const Pet& pet);

	//Overloading the output operator
	//Input: stream - ostream, pet - Pet
	//Output: the pet is printed
	friend std::ostream& operator<<(std::ostream& stream, const Pet& pet);

	//Overloading the input operator
	//Input: stream - istream, pet - Pet
	//Output: the pet is read
	friend std::istream& operator>>(std::istream& stream, Pet& pet);
};