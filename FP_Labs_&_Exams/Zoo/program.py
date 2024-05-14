#
# Functions section
#
def create_animal_dictionary_with_animal_data(animal_code: str, animal_name: str, animal_type: str,
                                              animal_species: str):
    return {"code": animal_code, "name": animal_name, "type": animal_type, "species": animal_species}


def get_animal_code(animal: dict) -> str:
    return animal["code"]


def get_animal_name(animal: dict) -> str:
    return animal["name"]


def get_animal_type(animal) -> str:
    return animal["type"]


def get_animal_species(animal) -> str:
    return animal["species"]


def add_the_new_animal_data_in_animals_list(animals: list, animal_code: str, animal_name: str, animal_type: str,
                                            animal_species: str) -> list:
    animals.append(create_animal_dictionary_with_animal_data(animal_code, animal_name, animal_type, animal_species))
    return animals


def find_animal_species_and_change_its_type(animals: list, animal_species: str, animal_type: str):
    for i in range(len(animals)):
        if get_animal_species(animals[i]).lower() == animal_species.lower():
            animals[i]["type"] = animal_type


def sort_animals_by_their_species_and_then_by_their_name(animals: list) -> list:
    for i in range(len(animals)):
        for j in range(len(animals)):
            if get_animal_species(animals[i]) < get_animal_species(animals[j]):
                animals[i], animals[j] = animals[j], animals[i]
            elif get_animal_species(animals[i]) == get_animal_species(animals[j]):
                if get_animal_name(animals[i]) < get_animal_name(animals[j]):
                    animals[i], animals[j] = animals[j], animals[i]
    return animals


#
# User interface section
#
def input_five_animals_at_the_beginning():
    animals = [create_animal_dictionary_with_animal_data("ZO1", "Alex", "herbivore", "zebra"),
               create_animal_dictionary_with_animal_data("ZO2", "Bruno", "omnivore", "lion"),
               create_animal_dictionary_with_animal_data("ZO3", "Mandarin", "carnivore", "tigre"),
               create_animal_dictionary_with_animal_data("ZO4", "Marin", "carnivore", "lion"),
               create_animal_dictionary_with_animal_data("ZO5", "Lulu", "herbivore", "koala")]
    return animals


def add_animal_to_the_zoo_collection(animals: list) -> list:
    animal_code = input("Enter the animal code: ").strip()
    animal_name = input("Enter the animal name: ").strip()
    animal_type = input("Enter the animal type: ").strip()
    animal_species = input("Enter the animal species: ").strip()
    if not animal_species or not animal_type or not animal_name or not animal_code:
        raise ValueError("Invalid input!")
    for animal in animals:
        if get_animal_code(animal) == animal_code:
            raise ValueError("Code animal already exist!")
    animals = add_the_new_animal_data_in_animals_list(animals, animal_code, animal_name, animal_type, animal_species)
    return animals


def change_animal_type_of_given_species(animals: list) -> list:
    animal_species = input("Enter the animal species: ").strip()
    animal_type = input("Enter the animal new type: ").strip()
    if not animal_type:
        raise ValueError("Invalid input!")
    find_animal_species_and_change_its_type(animals, animal_species, animal_type)
    return animals


def show_all_species_sorted_by_their_species_or_name(animals: list):
    animals = sort_animals_by_their_species_and_then_by_their_name(animals)
    display_animals(animals)


def display_animals(animals: list):
    for animal in animals:
        print(f"Animal code: {get_animal_code(animal)}\n"
              f"Animal name: {get_animal_name(animal)}\n"
              f"Animal type: {get_animal_type(animal)}\n"
              f"Animal species: {get_animal_species(animal)}\n")


def print_menu():
    print("1. Add an animal to zoo.\n"
          "2. Change the type fo a given species.\n"
          "3. Show all animals sorted by their species, and then, by their name.\n")


def menu_application():
    add_animal = '1'
    change_animal_type = '2'
    show_all_animals_sorted = '3'
    animals = input_five_animals_at_the_beginning()
    while True:
        try:
            option = input("Please enter the option from the list above: ")
            if option == add_animal:
                add_animal_to_the_zoo_collection(animals)
            elif option == change_animal_type:
                change_animal_type_of_given_species(animals)
            elif option == show_all_animals_sorted:
                show_all_species_sorted_by_their_species_or_name(animals)
            else:
                print("Invalid input!")
        except ValueError as validation:
            print(validation)


print_menu()
menu_application()
