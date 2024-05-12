#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print
# statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#
import random


def create_apartments_list_using_dictionaries(apartment, amount, expense_type):
    return {"apartment": apartment, "amount": amount, "type": expense_type}


def get_number_of_apartment(apartment: dict) -> int:
    return apartment["apartment"]


def get_amount_of_apartment(apartment: dict) -> int:
    return apartment["amount"]


def get_type_of_expense(apartment: dict) -> str:
    return apartment["type"]


def generate_random_integer_positive_numbers():
    return random.randint(1, 100)


def generate_random_type_from_the_given_categories():
    return random.choice(("heating", "water", "electricity", "gas", "other"))


def generate_10_apartments_for_beginning():
    apartment_number = generate_random_integer_positive_numbers()
    amount = generate_random_integer_positive_numbers()
    expense_type = generate_random_type_from_the_given_categories()
    apartments = [create_apartments_list_using_dictionaries(apartment_number, amount, expense_type)]
    i = 1
    number_of_generated_apartments = 10
    while i <= number_of_generated_apartments:
        apartment_number = generate_random_integer_positive_numbers()
        amount = generate_random_integer_positive_numbers()
        expense_type = generate_random_type_from_the_given_categories()
        new_apartment = create_apartments_list_using_dictionaries(apartment_number, amount, expense_type)
        apartment_expense_is_repeating = False
        for apartment in apartments:
            if apartment_number == get_number_of_apartment(apartment) and expense_type == get_type_of_expense(
                    apartment):
                apartment_expense_is_repeating = True
        if not apartment_expense_is_repeating:
            apartments.append(new_apartment)
            i += 1
    return apartments


def add_new_transaction(apartments: list, parameters: str) -> list:
    check_length = parameters.split()
    add_apartment_len3 = 3
    if len(check_length) != add_apartment_len3:
        raise ValueError("Parameters are invalid")
    apartment, expense_type, amount = parameters.split(" ", 2)
    if not apartment.isnumeric():
        raise ValueError("Number of apartment is invalid!")
    if expense_type not in ["water", "gas", "other", "electricity", "heating"]:
        raise ValueError("Type of expense is invalid!")
    if not amount.isnumeric():
        raise ValueError("The value of the expense is invalid!")
    new_apartment = create_apartments_list_using_dictionaries(int(apartment), int(amount), expense_type)
    if new_apartment not in apartments:
        apartments.append(new_apartment)
    else:
        raise ValueError("Expense already exist!")
    return apartments


def remove_expenses_of_apartments(apartments: list, parameters: str) -> list:
    if parameters.isnumeric():
        i = 0
        while i < len(apartments):
            if get_number_of_apartment(apartments[i]) == int(parameters):
                del apartments[i]
                i -= 1
            i += 1

    elif " " not in parameters.strip():
        if parameters.strip() not in ["water", "gas", "electricity", "heating", "other"]:
            raise ValueError("Parameters are invalid!")
        i = 0
        while i < len(apartments):
            if get_type_of_expense(apartments[i]) == parameters.strip():
                del apartments[i]
                i -= 1
            i += 1

    elif " to " in parameters:
        check_length = parameters.split()
        remove_interval_len3 = 3
        if len(check_length) != remove_interval_len3:
            raise ValueError("Parameters are invalid")
        start_apartment, end_apartment = parameters.split(" to ")
        if not start_apartment.isnumeric() or not end_apartment.isnumeric():
            raise ValueError("Parameters are invalid!")
        i = 0
        while i < len(apartments):
            if int(start_apartment) <= get_number_of_apartment(apartments[i]) <= int(end_apartment):
                del apartments[i]
                i -= 1
            i += 1

    else:
        raise ValueError("Parameters are invalid!")
    return apartments


def replace_expenses_of_apartments(apartments, parameters):
    if " with " in parameters:
        check_length = parameters.split()
        replace_expense_len4 = 4
        if len(check_length) != replace_expense_len4:
            raise ValueError("Parameters are invalid")
        apartment_and_type, amount = parameters.split(" with ")
        apartment_number, expenses_type = apartment_and_type.split(" ")
        if not apartment_number.isnumeric() or not amount.isnumeric() or expenses_type not in ["water", "gas",
                                                                                               "electricity", "heating",
                                                                                               "other"]:
            raise ValueError("Parameters are invalid!")
        for i in range(len(apartments)):
            if get_number_of_apartment(apartments[i]) == int(apartment_number) and get_type_of_expense(
                    apartments[i]) == expenses_type:
                apartments[i]["amount"] = int(amount)

    else:
        raise ValueError("Parameters are invalid!")
    return apartments


def display_expenses_having_different_properties(apartments: list, parameters: str):
    if parameters is None:
        return apartments

    elif parameters.strip().isnumeric():
        apartment_with_given_number = []
        for i in range(len(apartments)):
            if get_number_of_apartment(apartments[i]) == int(parameters):
                apartment_with_given_number.append(apartments[i])
        if apartment_with_given_number:
            return apartment_with_given_number
        else:
            raise ValueError("Apartment not found!")

    elif "=" in parameters or "<" in parameters or ">" in parameters:
        check_length = parameters.split()
        display_apartments_with_amount_len2 = 2
        no_apartment_added = 0
        if len(check_length) != display_apartments_with_amount_len2:
            raise ValueError("Parameters are invalid")
        sign, amount = parameters.split(" ")
        if not amount.isnumeric():
            raise ValueError("Parameters are invalid!")
        apartments_with_given_amount = []
        total_expenses = [create_apartments_list_using_dictionaries(get_number_of_apartment(apartments[0]),
                                                                    get_amount_of_apartment(apartments[0]),
                                                                    get_type_of_expense(apartments[0]))]
        apartments_added = 0
        for i in range(1, len(apartments)):
            for j in range(len(total_expenses)):
                if get_number_of_apartment(apartments[i]) == get_number_of_apartment(total_expenses[j]):
                    total_expenses[j]["amount"] += get_amount_of_apartment(apartments[i])
                    total_expenses[j]["type"] += '+' + get_type_of_expense(apartments[i])
                    apartments_added += 1
            if apartments_added == no_apartment_added:
                total_expenses.append(
                    create_apartments_list_using_dictionaries(get_number_of_apartment(apartments[i]),
                                                              get_amount_of_apartment(apartments[i]),
                                                              get_type_of_expense(apartments[i])))
            apartments_added = 0
        for i in range(len(total_expenses)):
            if sign == '=' and get_amount_of_apartment(total_expenses[i]) == int(amount):
                apartments_with_given_amount.append(total_expenses[i])
            elif sign == '<' and get_amount_of_apartment(total_expenses[i]) < int(amount):
                apartments_with_given_amount.append(total_expenses[i])
            elif sign == '>' and get_amount_of_apartment(total_expenses[i]) > int(amount):
                apartments_with_given_amount.append(total_expenses[i])
            else:
                raise ValueError("Parameters are invalid!")
        return apartments_with_given_amount

    else:
        raise ValueError("Parameters are invalid!")


def filter_expenses(apartments: list, parameters: str):
    if parameters.strip().isnumeric():
        expenses_having_given_amount = []
        for i in range(len(apartments)):
            if get_amount_of_apartment(apartments[i]) < int(parameters):
                expenses_having_given_amount.append(apartments[i])
        return expenses_having_given_amount

    elif parameters.strip() in ["heating", "gas", "water", "other", "electricity"]:
        expenses_having_given_type = []
        for i in range(len(apartments)):
            if get_type_of_expense(apartments[i]) == parameters:
                expenses_having_given_type.append(apartments[i])
        return expenses_having_given_type

    else:
        raise ValueError("Parameters are invalid!")


def undo(stack: list):
    stack_end = 1
    if len(stack) > stack_end:
        stack.pop()
        return stack[len(stack) - 1][:]
    elif len(stack) == stack_end:
        stack.pop()
        return []
    else:
        raise ValueError("No more undoes valid!")


def test_function():
    apartments = [create_apartments_list_using_dictionaries(12, 200, 'gas'),
                  create_apartments_list_using_dictionaries(13, 89, 'water'),
                  create_apartments_list_using_dictionaries(17, 90, 'other'),
                  create_apartments_list_using_dictionaries(20, 56, 'gas'),
                  create_apartments_list_using_dictionaries(12, 80, 'water')]

    assert add_new_transaction(apartments, '40 water 10') == [
        create_apartments_list_using_dictionaries(12, 200, 'gas'),
        create_apartments_list_using_dictionaries(13, 89, 'water'),
        create_apartments_list_using_dictionaries(17, 90, 'other'),
        create_apartments_list_using_dictionaries(20, 56, 'gas'),
        create_apartments_list_using_dictionaries(12, 80, 'water'),
        create_apartments_list_using_dictionaries(40, 10, 'water')]

    assert remove_expenses_of_apartments(apartments, '12') == [
        create_apartments_list_using_dictionaries(13, 89, 'water'),
        create_apartments_list_using_dictionaries(17, 90, 'other'),
        create_apartments_list_using_dictionaries(20, 56, 'gas'),
        create_apartments_list_using_dictionaries(40, 10, 'water')]

    assert remove_expenses_of_apartments(apartments, '13 to 19') == [
        create_apartments_list_using_dictionaries(20, 56, 'gas'),
        create_apartments_list_using_dictionaries(40, 10, 'water')]

    assert remove_expenses_of_apartments(apartments, 'gas') == [
        create_apartments_list_using_dictionaries(40, 10, 'water')]

    assert replace_expenses_of_apartments(apartments, '40 water with 70') == [
         create_apartments_list_using_dictionaries(40, 70, 'water')]
