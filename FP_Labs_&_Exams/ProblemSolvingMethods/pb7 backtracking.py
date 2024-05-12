def print_list(to_be_printed: list):
    print(to_be_printed)


def checking_if_the_complete_subsequence_is_correct_generated(
        to_be_check: list):
    return to_be_check[len(to_be_check) - 1] == 0


def verify_if_the_generated_subsequence_has_the_correct_length(to_be_verified: list, subseq_length: int):
    return len(to_be_verified) == subseq_length


def checking_if_the_partial_subsequence_is_correct_generated_for_recursion(to_be_check: list) -> bool:
    return (to_be_check[0] == 0 and len(to_be_check) == 1) or (
            to_be_check[len(to_be_check) - 1] != to_be_check[len(to_be_check) - 2])


def checking_if_the_partial_subsequence_is_correct_generated_for_iteration(to_be_check: list,
                                                                           subseq_length: int) -> bool:
    return (to_be_check[0] == 0 and subseq_length == 1) or (
            to_be_check[subseq_length - 1] != to_be_check[subseq_length - 2])


def generate_all_subsequences_that_have_0_on_first_and_last_positions_and_different_digits_from_1_0_neg1_on_consecutive_position_recursive(
        subsequence: list, subseq_length: int):
    """
        The function generates all the subsequences of 2*n+1 length with digits from {-1,0,1} with the first and last
         element 0 and the digits on the consecutive positions are different in a recursive way
     """
    subsequence.append(-1)
    for i in range(-1, 2):
        subsequence[len(subsequence) - 1] = i
        if verify_if_the_generated_subsequence_has_the_correct_length(subsequence, subseq_length):
            if checking_if_the_complete_subsequence_is_correct_generated(subsequence):
                print_list(subsequence)
        elif checking_if_the_partial_subsequence_is_correct_generated_for_recursion(subsequence):
            generate_all_subsequences_that_have_0_on_first_and_last_positions_and_different_digits_from_1_0_neg1_on_consecutive_position_recursive(subsequence[:], subseq_length)


def generate_all_subsequences_that_have_0_on_first_and_last_positions_and_different_digits_from_1_0_neg1_on_consecutive_position_iterative(
        subseq_length: int):
    """
    The function generates all the subsequences of 2*n+1 length with digits from {-1,0,1} with the first and last
     element 0 and the digits on the consecutive positions are different in an iterative way
    """
    stack = []
    subsequence = [0] * subseq_length
    stack.append((subsequence, 1))
    while stack:
        subsequence, level = stack.pop()
        if verify_if_the_generated_subsequence_has_the_correct_length(subsequence, level):
            if checking_if_the_complete_subsequence_is_correct_generated(subsequence):
                print_list(subsequence)
        elif checking_if_the_partial_subsequence_is_correct_generated_for_iteration(subsequence, level):
            for i in range(-1, 2):
                subsequence[level] = i
                stack.append((subsequence[:], level + 1))


def valid_option_chosen(option_given: str) -> int:
    while not option_given.isnumeric() or (3 < int(option_given) or int(option_given) < 1):
        option_given = input(
            "\nThe option you introduced is not valid. Please choose an option from the list above: ")
    return int(option_given)


def is_number(length_given: str) -> int:
    while not length_given.isnumeric():
        length_given = input(
            "\nThe option you introduced is not valid. Please choose an option from the list above: ")
    return int(length_given)


def menu_application():
    length = input("Please enter the length for the subsequences: ")
    length = is_number(length)
    while True:
        option = input("Please introduce the option you want for executing the problem: ")
        option = valid_option_chosen(option)
        if option == 1:
            print("The subsequence generated recursive: ")
            (generate_all_subsequences_that_have_0_on_first_and_last_positions_and_different_digits_from_1_0_neg1_on_consecutive_position_recursive
             ([], 2 * length + 1))
        elif option == 2:
            print("The subsequence generated iterative: ")
            generate_all_subsequences_that_have_0_on_first_and_last_positions_and_different_digits_from_1_0_neg1_on_consecutive_position_iterative(
                2 * length + 1)
        elif option == 3:
            print("Exiting the program...")
            break


print("1.Generate all the subsequences using backtracking\n2.Generate all the subsequences in a iterative way\n"
      "3.Exit the program\n")
menu_application()
