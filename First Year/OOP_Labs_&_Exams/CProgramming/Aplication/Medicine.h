#pragma once
typedef struct {
	char* name;
	int concentration;
	int quantity;
	int price;
}Medicine;

//Creates a new medicine
//Input: name - char*, concentration - int, quantity - int, price - int
//Output: a pointer to the new medicine
Medicine* CreateMedicine(char* name, int concentration, int quantity, int price);

//Destroys a medicine
//Input: medicine - pointer to the medicine
void DestroyMedicine(Medicine* medicine);

//Gets the name of a medicine
//Input: medicine - pointer to the medicine
//Output: the name of the medicine
char* GetName(Medicine* medicine);

//Gets the concentration of a medicine
//Input: medicine - pointer to the medicine
//Output: the concentration of the medicine
int GetConcentration(Medicine* medicine);

//	Gets the quantity of a medicine
//	Input: medicine - pointer to the medicine
//	Output: the quantity of the medicine
int GetQuantity(Medicine* medicine);

//Gets the price of a medicine
//Input: medicine - pointer to the medicine
//Output: the price of the medicine
int GetPrice(Medicine* medicine);

//Sets the name of a medicine
//Input: medicine - pointer to the medicine, name - char*
void SetName(Medicine* medicine, char* name);

//Sets the concentration of a medicine
//Input: medicine - pointer to the medicine, concentration - int
void SetConcentration(Medicine* medicine, int concentration);

//Sets the quantity of a medicine
//Input: medicine - pointer to the medicine, quantity - int
void SetQuantity(Medicine* medicine, int quantity);

//Sets the price of a medicine
//Input: medicine - pointer to the medicine, price - int
void SetPrice(Medicine* medicine, int price);

//Prints a medicine
//Input: medicine - pointer to the medicine, string - char[] , the string in which the medicine will be printed
void PrintMedicine(Medicine* medicine, char string[]);

//Compares two medicines
//Input: first_medicine - pointer to the first medicine, second_medicine - pointer to the second medicine
//Output: 1 if the medicines are equal, 0 otherwise
int EqualMedicine(Medicine* first_medicine, Medicine* second_medicine);

//Copies a medicine
//Input: medicine - pointer to the medicine
//Output: a pointer to the new medicine
Medicine* CopyMedicine(Medicine* medicine);