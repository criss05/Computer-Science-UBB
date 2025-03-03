def print_list_as_set(set_: list):
    print(set(set_))


def sum_of_elements_in_a_set(set_: list) -> int:
    elements_sum = 0
    for element in set_:
        elements_sum += element
    return elements_sum


def check_if_elements_in_set_repeat_and_elements_in_ascendant_order_and_elements_sum_less_equal_to_the_given_one(
        to_be_checked: list, input_sum: int):
    return len(set(to_be_checked)) == len(to_be_checked) and (
            to_be_checked[len(to_be_checked) - 2] < to_be_checked[len(to_be_checked) - 1] or
            len(to_be_checked) == 1) and sum_of_elements_in_a_set(
        to_be_checked) <= input_sum


def check_if_sum_of_elements_in_subset_is_equal_to_the_given_one(to_be_checked: list, input_sum: int) -> bool:
    return sum_of_elements_in_a_set(to_be_checked) == input_sum


def generate_subsets_that_has_elements_sum_equal_to_the_given_one_naive_solution(
        input_set: list, subset_has_elements_sum_equal_input_sum: list, input_sum: int):
    subset_has_elements_sum_equal_input_sum.append(0)
    for element in input_set:
        subset_has_elements_sum_equal_input_sum[len(subset_has_elements_sum_equal_input_sum) - 1] = element
        if check_if_elements_in_set_repeat_and_elements_in_ascendant_order_and_elements_sum_less_equal_to_the_given_one(
                subset_has_elements_sum_equal_input_sum, input_sum):
            if check_if_sum_of_elements_in_subset_is_equal_to_the_given_one(
                    subset_has_elements_sum_equal_input_sum,
                    input_sum):
                print_list_as_set(subset_has_elements_sum_equal_input_sum)
            else:
                generate_subsets_that_has_elements_sum_equal_to_the_given_one_naive_solution(
                    input_set, subset_has_elements_sum_equal_input_sum[:], input_sum)


def print_list_as_matrix(matrix: list):
    for row in matrix:
        print(row)
    print('\n')


def find_subset_in_input_set_that_has_sum_elements_equal_to_input_sum_dynamic_programming(
        input_set: list, input_sum: int):
    set_length = len(input_set)

    checking_if_sum_can_be_formed_with_set_elements = [[False for _ in range(input_sum + 1)] for _ in
                                                       range(set_length + 1)]

    for i in range(set_length + 1):
        checking_if_sum_can_be_formed_with_set_elements[i][0] = True
    print("The matrix used for creating the subset modify in this way: ")
    for i in range(1, set_length + 1):
        for current_sum in range(1, input_sum + 1):
            if current_sum < input_set[i - 1]:
                checking_if_sum_can_be_formed_with_set_elements[i][current_sum] = \
                    checking_if_sum_can_be_formed_with_set_elements[i - 1][current_sum]
            else:
                checking_if_sum_can_be_formed_with_set_elements[i][current_sum] = \
                    checking_if_sum_can_be_formed_with_set_elements[i - 1][current_sum] or \
                    checking_if_sum_can_be_formed_with_set_elements[i - 1][current_sum - input_set[i - 1]]
                print_list_as_matrix(checking_if_sum_can_be_formed_with_set_elements)

    if not checking_if_sum_can_be_formed_with_set_elements[set_length][input_sum]:
        return None

    subset_element_sum_equal_input_sum = []
    i, current_sum = set_length, input_sum
    while i > 0 and current_sum > 0:
        if checking_if_sum_can_be_formed_with_set_elements[i][current_sum] and not \
                checking_if_sum_can_be_formed_with_set_elements[i - 1][current_sum]:
            subset_element_sum_equal_input_sum.append(input_set[i - 1])
            current_sum -= input_set[i - 1]
        i -= 1
    subset_element_sum_equal_input_sum.reverse()
    print_list_as_set(subset_element_sum_equal_input_sum)


def give_explanations_about_naive_solution():
    print("\nThe naive solution is generating all the possible combination of sum until it finds one that is equal "
          "to the given one. \n")


def give_explanations_about_dynamic_programming_solution():
    print("\nThe dynamic programming solution is creating a true/false matrix, checking if it is possible to create "
          "a sum with the first i elements in the given set or not.\n In the end is rebuilding the subset based on the "
          "created matrix\n")


def is_numeric(to_be_valid):
    while not to_be_valid.isnumeric():
        to_be_valid = input("Please give a valid option: ").strip(" ")
    return int(to_be_valid)


def read_set():
    set_length = input("Give the length of the set: ").strip(" ")
    set_length = is_numeric(set_length)
    input_set = []
    for _ in range(set_length):
        element = input("Give the set element: ").strip(" ")
        element = is_numeric(element)
        input_set.append(element)
    return input_set


def read_sum_used_for_finding_the_subset_with_sum_elements_equal():
    input_sum = input("Give the sum you want to use: ").strip(" ")
    input_sum = is_numeric(input_sum)
    return input_sum


def menu_application():
    input_set = read_set()
    input_sum = read_sum_used_for_finding_the_subset_with_sum_elements_equal()

    while True:
        option = input("\nGive the option from the list above: ").strip(" ")
        if option == '1':
            give_explanations_about_naive_solution()
            generate_subsets_that_has_elements_sum_equal_to_the_given_one_naive_solution(
                input_set, [], input_sum)
        elif option == '2':
            give_explanations_about_dynamic_programming_solution()
            find_subset_in_input_set_that_has_sum_elements_equal_to_input_sum_dynamic_programming(input_set, input_sum)
        elif option == '3':
            print("Exiting the program...")
            break
        else:
            print("Option is invalid!")


def print_menu():
    print("Display one subset of a given subset which has the sum of elements equal to a given one.\n"
          "1. Solve the problem using naive programming.\n"
          "2. Solve the problem using dynamic programming.\n"
          "3. Exiting the program.")


print_menu()
menu_application()
