import time


def read_list_length() -> int:
    input_length = input("\nPlease enter the length of the list: ")
    while not input_length.isnumeric() or int(input_length) <= 0:
        input_length = input("\nThe value you introduced is not valid. Please enter a proper value:")
    return int(input_length)


def generate_random_list(random_list_length: int) -> list:
    """
    This function generates a random list of given length
    :return: The random list generated
    """
    import random
    random_list_generated = []
    random_list_length = int(random_list_length)
    for i in range(random_list_length):
        random_list_generated.append(random.randint(0, 100))
    return random_list_generated


def generate_random_list_timing(random_list_length: int) -> list:
    """
    This function generates a random list of given length for the timing part
    :param: random_list_length:
    :return: The random list generated
    """
    import random
    random_list_generated = []
    random_list_length = int(random_list_length)
    for i in range(16 * random_list_length):
        random_list_generated.append(random.randint(0, 100000))
    return random_list_generated


def best_case_complexity(to_be_sorted: list) -> list:
    """
    This function is sorting ascending the list, so we can check the best case of complexity
    :param to_be_sorted: The sort we want to sort
    :return: The ascending sorted list
    """
    return sorted(to_be_sorted)


def worst_case_complexity(to_be_sorted: list) -> list:
    """
        This function is sorting descending the list, so we can check the worst case of complexity
        :param to_be_sorted: The sort we want to sort
        :return: The descending sorted list
        """
    return sorted(to_be_sorted, reverse=True)


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


def exchange_sort_complexity(to_be_sorted: list) -> list:
    """
    This function will take a list and will sort it ascending using exchange sort method
    :param to_be_sorted: The list we want to be sorted
    :return: The sorted list
    """
    list_length = len(to_be_sorted)
    for i in range(list_length - 1):
        for j in range(i + 1, list_length):
            if to_be_sorted[i] > to_be_sorted[j]:
                to_be_sorted[i], to_be_sorted[j] = to_be_sorted[j], to_be_sorted[i]
    return to_be_sorted


def timing_exchange_sort(to_be_sorted: list) -> float:
    """
    This function is timing the exchange sort method
    :param to_be_sorted: The list we want to sort using exchange sort for timing the complexity
    :return: How much it takes the algorithm to make the sort using this method
    """
    start_timer = time.perf_counter()
    exchange_sort_complexity(to_be_sorted)
    return time.perf_counter() - start_timer


def gnome_sort(to_be_sorted: list, step: int) -> list:
    """
    This function will take a list and will sort it ascending using gnome sort method
    :param to_be_sorted: The list we want to be sorted
    :param step :The step we will show the partial sorted list
    :return: The sorted list
    """
    step_made = 0
    list_length = len(to_be_sorted)
    current_position = 0
    while current_position != list_length:
        if current_position == 0:
            current_position += 1
        elif to_be_sorted[current_position] < to_be_sorted[current_position - 1]:
            swap_variable = to_be_sorted[current_position]
            to_be_sorted[current_position] = to_be_sorted[current_position - 1]
            to_be_sorted[current_position - 1] = swap_variable
            step_made += 1
            current_position -= 1
        elif to_be_sorted[current_position] >= to_be_sorted[current_position]:
            current_position += 1
        if step_made == step:
            print("This is the sorted list until now: ", to_be_sorted)
            step_made = 0
    return to_be_sorted


def gnome_sort_complexity(to_be_sorted: list) -> list:
    """
    This function will take a list and will sort it ascending using gnome sort method
    :param to_be_sorted: The list we want to be sorted
    :return:  The sorted list
    """
    list_length = len(to_be_sorted)
    current_position = 0
    while current_position != list_length:
        if current_position == 0:
            current_position += 1
        elif to_be_sorted[current_position] < to_be_sorted[current_position - 1]:
            swap_variable = to_be_sorted[current_position]
            to_be_sorted[current_position] = to_be_sorted[current_position - 1]
            to_be_sorted[current_position - 1] = swap_variable
            current_position -= 1
        elif to_be_sorted[current_position] >= to_be_sorted[current_position]:
            current_position += 1
    return to_be_sorted


def timing_gnome_sort(to_be_sorted: list) -> float:
    """
    This function is timing the gnome sort method
    :param to_be_sorted: The list we want to sort using gnome sort for timing the complexity
    :return: How much it takes the algorithm to make the sort using this method
    """
    start_timer = time.perf_counter()
    gnome_sort_complexity(to_be_sorted)
    return time.perf_counter() - start_timer


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


def best_case_timing():
    """
    This function is going to generate a list and sort it ascending and then take parts of the list and check
    how much it takes for all of them to be sorted
    :return: How much it takes the algorithm to make the sort using lists of different sizes
    """
    list_length = read_list_length()
    best_list = best_case_complexity(generate_random_list_timing(list_length))
    partial_list = []
    current_position = 0
    length = len(best_list) // 16
    print("\nThe timing for the best case is: \n")
    print("Exchange |  Gnome")
    print(20 * '_')
    for element in best_list:
        partial_list.append(element)
        current_position += 1
        if current_position == length:
            copy_list_exchange = copy_the_list(partial_list)
            copy_list_gnome = copy_the_list(partial_list)
            print('%.5f' % timing_exchange_sort(copy_list_exchange), ' | ', '%.5f' % timing_gnome_sort(copy_list_gnome))
            print(20 * '_')
            length *= 2


def average_case_timing():
    """
    This function is going to generate a list and take parts of the list and then check how much it takes for all of
    them to be sorted
    :return: How much it takes the algorithm to make the sort using lists of different sizes
    """
    list_length = read_list_length()
    random_list = generate_random_list_timing(list_length)
    partial_list = []
    current_position = 0
    length = len(random_list) / 16
    print("\nThe timing for the average case is: \n")
    print("Exchange |  Gnome")
    print(20 * '_')
    for element in random_list:
        partial_list.append(element)
        current_position += 1
        if current_position == length:
            copy_list_exchange = copy_the_list(partial_list)
            copy_list_gnome = copy_the_list(partial_list)
            print('%.5f' % timing_exchange_sort(copy_list_exchange), ' | ', '%.5f' % timing_gnome_sort(copy_list_gnome))
            print(20 * '_')
            length *= 2


def worst_case_timing():
    """
    This function is going to generate a list and sort it descending and then take parts of the list and check
    how much it takes for all of them to be sorted
    :return: How much it takes the algorithm to make the sort using lists of different sizes"""
    list_length = read_list_length()
    worst_list = worst_case_complexity(generate_random_list_timing(list_length))
    partial_list = []
    current_position = 0
    length = len(worst_list) / 16
    print("\nThe timing for the worst case is: \n")
    print("Exchange |  Gnome")
    print(20 * '_')
    for element in worst_list:
        partial_list.append(element)
        current_position += 1
        if current_position == length:
            copy_list_exchange = copy_the_list(partial_list)
            copy_list_gnome = copy_the_list(partial_list)
            print('%.5f' % timing_exchange_sort(copy_list_exchange), ' | ', '%.5f' % timing_gnome_sort(copy_list_gnome))
            print(20 * '_')
            length *= 2


def valid_option_chosen(option_given: str) -> int:
    """
    Tests if the option chosen is correct
    :param option_given: The input option
    :return: The correct input option
    """
    while not option_given.isnumeric() or (7 < int(option_given) or int(option_given) < 1):
        option_given = input(
            "\nThe option you introduced is not valid. Please choose an option from the list above: ")
    return int(option_given)


def menu_application():
    input_random_list = []
    while True:
        option = input("\nPlease choose an option from the list above: ")
        option = valid_option_chosen(option)
        if not input_random_list and option in [2, 3, 4, 5, 6]:
            while option not in [1, 4, 5, 6, 7]:
                option = input("\nPlease choose a valid number for the first operation, such as:\n "
                               "1. For generating the list\n 4. For timing the best case\n 5. For timing the average "
                               "case\n 6. For timing the worst case\n 7. For exiting the program\nYour option: ")
                option = valid_option_chosen(option)
        if option == 1:
            input_list_length = read_list_length()
            input_random_list = generate_random_list(input_list_length)
            print("\nThe random generated list is:", input_random_list)
        if option == 7:
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
        elif option == 4:
            best_case_timing()
        elif option == 5:
            average_case_timing()
        elif option == 6:
            worst_case_timing()


print("Sorting Algorithms\n")
print("1. Generate a random list of natural numbers (generated numbers must be between 0 and 100).\n"
      "2. Sort the generated list using Exchange Sort method\n"
      "3. Sort the generated list using Gnome Sort method\n"
      "4. Timing the best case of the sorting algorithms\n"
      "5. Timing the average case of the sorting algorithms\n"
      "6. Timing the worse case of the sorting algorithms\n"
      "7. Exit the program\n")
menu_application()
