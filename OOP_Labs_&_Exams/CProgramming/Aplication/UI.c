#include "UI.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <crtdbg.h>

Ui* CreateUi(int length)
{
    Ui* ui= malloc(sizeof(Ui));
    Service* service = CreateService(length);
    ui->service = service;
    ui->length = length;
    return ui;
}

void DestroyUi(Ui* ui){
    DestroyService(ui->service);
    free(ui);
}

void PrintMenu() {
    printf("\n1. Add a medicine.\n");
    printf("2. Delete a medicine.\n");
    printf("3. Update a medicine.\n");
    printf("4. See all medicine containing a given string ascending (If the string is empty will display all medicines).\n");
    printf("5. See all medicine containing a given string descending (If the string is empty will display all medicines).\n");
    printf("6. See the medicines that are in short supply. (Give a value to compare with)\n");
    printf("7. See the medicines that are cheaper. (Give a value to compare with)\n");
    printf("8. Undo.\n");
    printf("9. Redo.\n");
    printf("10. Exit.\n\n");
}

int ValidateString(char string[]) {
    if (strlen(string) < 3)
        return 0;
    for (int i = 0; i < strlen(string); i++)
        if (isalpha(string[i]) == 0 && string[i] != ' ')
            return 0;
    return 1;
}

int ValidateNumber(char str_number[]) {
    return atoi(str_number);
}

void AddMedicineUI(Ui* ui) {
    char name[30];
    char string_concentration[10], string_quantity[10], string_price[10];

    printf("Please give the medicine name: ");
    fgets(name, 30, stdin);
    name[strlen(name) - 1] = '\0';
    int error = ValidateString(name);
    if (error == 0) {
        printf("\nInvalid name! Give a text only with letters, having more than 3 characters.");
        return;
    }

    printf("Please give the medicine concentration: ");
    fgets(string_concentration, 10, stdin);
    int concetration = ValidateNumber(string_concentration);
    if (concetration == 0) {
        printf("\nInvalid Concetration! Give an integer bigger then 0.");
        return;
    }

    printf("Please give the medicine quantity: ");
    fgets(string_quantity, 10, stdin);
    int quantity = ValidateNumber(string_quantity);
    if (quantity == 0) {
        printf("\nInvalid quantity! Give an integer bigger then 0.");
        return;
    }

    printf("Please give the medicine price: ");
    fgets(string_price, 10, stdin);
    int price = ValidateNumber(string_price);
    if (price == 0) {
        printf("\nInvalid price! Give an integer bigger then 0.");
        return;
    }

    AddMedicine(ui->service, name, concetration, quantity, price);
}

void DeleteMedicineUI(Ui* ui) {
    char name[30];
    char string_concentration[10], string_quantity[10], string_price[10];
    printf("Please give the medicine name: ");
    fgets(name, 30, stdin);
    name[strlen(name) - 1] = '\0';
    int error = ValidateString(name);
    if (error == 0) {
        printf("\nInvalid name! Give a text only with letters, having more than 3 characters.");
        return;
    }

    printf("Please give the medicine concentration: ");
    fgets(string_concentration, 10, stdin);
    int concetration = ValidateNumber(string_concentration);
    if (concetration == 0) {
        printf("\nInvalid Concetration! Give an integer bigger then 0.");
        return;
    }
    int delete_error = DeleteMedicine(ui->service, name, concetration);
    if (delete_error == -1) {
        printf("\nCould not delete this medicine.");
        return;
    }
}

void UpdateMedicineUI(Ui* ui) {
    char name[30];
    char string_concentration[10], string_quantity[10], string_price[10];
    printf("Please give the medicine's name: ");
    fgets(name, 30, stdin);
    name[strlen(name) - 1] = '\0';
    int error = ValidateString(name);
    if (error == 0) {
        printf("\nInvalid name! Give a text only with letters, having more than 3 characters.");
        return;
    }

    printf("Please give the medicine's concentration: ");
    fgets(string_concentration, 10, stdin);
    int concetration = ValidateNumber(string_concentration);
    if (concetration == 0) {
        printf("\nInvalid Concetration! Give an integer bigger then 0.");
        return;
    }

    printf("Please give the medicine's new quantity: ");
    fgets(string_quantity, 10, stdin);
    int new_quantity = ValidateNumber(string_quantity);
    if (new_quantity == 0) {
        printf("\nInvalid quantity! Give an integer bigger then 0.");
        return;
    }

    printf("Please give the medicine's new price: ");
    fgets(string_price, 10, stdin);
    int new_price = ValidateNumber(string_price);
    if (new_price == 0) {
        printf("\nInvalid price! Give an integer bigger then 0.");
        return;
    }

    int update_error = UpdateMedicine(ui->service, name, concetration, new_quantity, new_price);
    if (update_error == -1) {
        printf("\nCould not update this medicine.");
        return;
    }
}

void FilterByGivenStringUI(Ui* ui, char sort[]) {
    char given_string[30];
    printf("Please enter the string to look for: ");
    gets(given_string);
    int number_elements = 0;
    Medicine** new_list;
    if (strcmp(sort, "ascending") == 0)
        new_list = GetAllWithGivenString(ui->service, given_string, &number_elements, CompareAscending);
    else
        new_list = GetAllWithGivenString(ui->service, given_string, &number_elements, CompareDescending);
    printf("\n");

    char string[100];
    for (int i = 0; i < number_elements; i++) {
        PrintMedicine(new_list[i], string);
        printf("%s", string);
    }
    free(new_list);
}

void SeeAllFilteredUI(Ui* ui, char filter[]) {
    char string_value[10];
    printf("Please give the value you want to filter by: ");
    fgets(string_value, 10, stdin);
    int value = ValidateNumber(string_value);
    if (value == 0) {
        printf("\nInvalid value! Give an integer bigger then 0.");
        return;
    }
    Medicine** new_list;
    int number_elements = 0;
    if (strcmp(filter, "quantity") == 0)
        new_list = GetAllFiltered(ui->service, value, &number_elements, FilterByQuantity);
    else
		new_list = GetAllFiltered(ui->service, value, &number_elements, FilterByPrice);
    if (number_elements == 0) {
        printf("\nThe string was not found!");
        free(new_list);
        return;
    }

    printf("\n");
    char string[100];
    for (int i = 0; i < number_elements; i++) {
        PrintMedicine(new_list[i], string);
		printf("%s", string);
    }
    free(new_list);
}

void UndoUI(Ui* ui) {
    int error = Undo(ui->service);
    if (error == -1)
        printf("Could not undo the operation!");
}

void RedoUI(Ui* ui) {
    int error = Redo(ui->service);
    if (error == -1)
        printf("Could not redo the operation!");
}

void GenerateMedicines(Ui* ui) {
    AddMedicine(ui->service, "Paracetamol", 20, 10, 90);
    AddMedicine(ui->service, "Parasinus", 59, 100, 130);
    AddMedicine(ui->service, "Ibuprofen", 23, 19, 87);
    AddMedicine(ui->service, "Nurofen", 2, 17, 43);
    AddMedicine(ui->service, "Algocalmin", 908, 87, 193);
    AddMedicine(ui->service, "Karissa", 123, 12, 65);
    AddMedicine(ui->service, "Carbocit", 132, 45, 253);
    AddMedicine(ui->service, "Aspirina", 98, 98, 43);
    AddMedicine(ui->service, "Kebene", 278, 34, 12);
    AddMedicine(ui->service, "Varicid", 400, 39, 25);
}

void Start(Ui* ui){
    GenerateMedicines(ui);
    while (1) {
        PrintMenu();
        char option_str[4];
        printf("Please choose an option:");
        fgets(option_str, 3, stdin);
        int option = atoi(option_str);
        fseek(stdin, 0, SEEK_END);
        switch (option){
            case 0:
                printf("\nThe option is not an integer value!");
                break;
            case 1:
                AddMedicineUI(ui);
                break;
            case 2:
                DeleteMedicineUI(ui);
                break;
            case 3:
                UpdateMedicineUI(ui);
                break;
            case 4: 
                FilterByGivenStringUI(ui, "ascending");
                break;
            case 5:
				FilterByGivenStringUI(ui, "descending");
				break;
            case 6:
                SeeAllFilteredUI(ui, "quantity");
                break;
            case 7:
                SeeAllFilteredUI(ui, "price");
                break;
            case 8:
                UndoUI(ui);
                break;
            case 9:
                RedoUI(ui);
                break;
            case 10:
                printf("Exiting...");
                return;
        default:
            printf("Option not in the list!");
            break;
        }
    }
}
