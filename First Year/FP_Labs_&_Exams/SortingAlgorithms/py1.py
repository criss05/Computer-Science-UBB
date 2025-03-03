def generate_random_list():
    """
    This function generates a random list with the length given
    :return: The random list generated
    """
    random_list_length = input("\nPlease enter the length of the list: ")
    while not random_list_length.isnumeric() or int(random_list_length) <= 0:
        random_list_length = input("\nThe value you introduced is not valid. Please enter a proper value:")
    import random
    random_list_generated = []
    random_list_length = int(random_list_length)
    for i in range(random_list_length):
        random_list_generated.append(random.randint(0, 100))
    print("\nThe random generated list is: ", random_list_generated)
    return random_list_generated


def read_step_value():
    """
    This function reads the step we need for the sort part
    :return: The value of the step
    """
    print("\nDuring sorting, the program will display the partially sorted list each time it makes step operations. ")
    step_value = input("\nPlease enter the value for the step: ")
    while not step_value.isnumeric() or step_value == 0:
        step_value = input("\nPlease enter a valid value for the step: ")
    return int(step_value)


def exchange_sort(to_be_sorted: list, step: int) -> list:
    """
    This function will take a list and will sort it ascending using exchange sort method
    :param to_be_sorted: The list we want to be sorted
    :param step: The step we will show the partial sorted list
    :return: The sorted list
    """
    list_length = len(to_be_sorted)
    step_made = 0
    for i in range(list_length - 1):
        for j in range(i + 1, list_length):
            if to_be_sorted[i] > to_be_sorted[j]:
                to_be_sorted[i], to_be_sorted[j] = to_be_sorted[j], to_be_sorted[i]
                step_made += 1
            if step_made == step:
                print("This is the sorted list until now: ", to_be_sorted)
                step_made = 0
    return to_be_sorted


def gnome_sort(to_be_sorted: list, step: int) -> list:
    """
    This function will take a list and will sort it ascending using gnome sort method
    :param to_be_sorted: The list we want to be sorted
    :param step: The step we will show the partial sorted list
    :return:  The sorted list
    """
    step_made = 0
    list_length = len(to_be_sorted)
    current_position = 0
    while current_position != list_length:
        if current_position == 0:
            current_position += 1
        elif to_be_sorted[current_position] < to_be_sorted[current_position - 1]:
            aux = to_be_sorted[current_position]
            to_be_sorted[current_position] = to_be_sorted[current_position - 1]
            to_be_sorted[current_position - 1] = aux
            step_made += 1
            current_position -= 1
        elif to_be_sorted[current_position] >= to_be_sorted[current_position]:
            current_position += 1
        if step_made == step:
            print("This is the sorted list until now: ", to_be_sorted)
            step_made = 0
    return to_be_sorted


def copy_the_list(copy_input: list) -> list:
    """
    This function copies a list.
    :param copy_input: The list we want to be copied
    :return: The copied list
    """
    copy_list = []
    for element in copy_input:
        copy_list.append(element)
    return copy_list


def valid_option_chosen(option_given: str) -> int:
    """
    Tests if the option chosen is correct
    :param option_given: The input option
    :return: The correct input option
    """
    good_option = False
    while not option_given.isnumeric() or (4 < int(option_given) or int(option_given) < 1):
        option_given = input(
            "\nThe option you introduced is not valid. Please choose an option from the list above: ")
    return int(option_given)


def menu_application():
    input_random_list = []
    while True:
        option = input("\nPlease choose an option from the list above: ")
        option = valid_option_chosen(option)
        if not input_random_list and option in [2, 3]:
            while option not in [1, 4]:
                option = input("\nPlease choose a valid number for the first operation, such as:\n "
                               "1. For generating the list\n 4. For exiting the program\n Your option: ")
                option = valid_option_chosen(option)
        if option == 1:
            input_random_list = generate_random_list()
        if option == 4:
            print("\nExiting the program...")
            break
        elif option == 2:
            input_step = read_step_value()
            copy_random_list = copy_the_list(input_random_list)
            sorted_list = exchange_sort(copy_random_list, input_step)
            print("\nThe list sorted by Exchange Sort method: ", sorted_list)
        elif option == 3:
            input_step = read_step_value()
            copy_random_list = copy_the_list(input_random_list)
            sorted_list = gnome_sort(copy_random_list, input_step)
            print("\nThe list sorted by Gnome Sort method: ", sorted_list)


print("Sorting Algorithms\n")
print("1. Generate a random list of natural numbers (generated numbers must be between 0 and 100).\n"
      "2. Sort the generated list using Exchange Sort method\n"
      "3. Sort the generated list using Gnome Sort method\n"
      "4. Exit the program\n")
menu_application()
