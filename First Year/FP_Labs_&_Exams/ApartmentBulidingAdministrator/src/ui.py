#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements)
# are found here
#
import functions


def print_menu():
    print("(A) Add new transaction\n"
          "  add <apartment> <type> <amount>\n")
    print("(B) Modify expenses\n"
          "  remove <apartment>\n"
          "  remove <start apartment> to <end apartment\n"
          "  remove <type>\n"
          "  replace <apartment> <type> with <amount>")
    print("(C) Display expenses having different properties\n"
          "  list\n"
          "  list <apartment>\n"
          "  list [ < | = | > ] <amount>\n")
    print("(D) Filter\n"
          "  filter <type>\n"
          "  filter <value>\n")
    print("(E) Undo\n"
          "  undo")


def print_apartments_expenses(apartments):
    if apartments:
        for apartment in apartments:
            print(f"Number of apartment: {functions.get_number_of_apartment(apartment)} "
                  f"Amount of apartment: {functions.get_amount_of_apartment(apartment)} "
                  f"Type of expense: {functions.get_type_of_expense(apartment)}")
    else:
        print("List is empty!")


def menu_application():
    add_transaction = "add"
    remove_expenses = "remove"
    replace_expenses = "replace"
    display_expenses = "list"
    filter_ = "filter"
    undo = "undo"
    apartments = functions.generate_10_apartments_for_beginning()
    stack = [apartments[:]]
    while True:
        option = input("Please enter the option: ")
        try:
            if " " in option.strip():
                command, parameters = option.split(" ", 1)
            else:
                command = option.strip()
                parameters = None

            if command == add_transaction and parameters:
                apartments = functions.add_new_transaction(apartments, parameters)
                stack.append(apartments[:])

            elif command == remove_expenses and parameters:
                apartments = functions.remove_expenses_of_apartments(apartments,parameters)
                stack.append(apartments[:])

            elif command == replace_expenses and parameters:
                apartments = functions.replace_expenses_of_apartments(apartments, parameters)
                stack.append(apartments[:])

            elif command == display_expenses:
                to_be_printed = functions.display_expenses_having_different_properties(apartments, parameters)
                print_apartments_expenses(to_be_printed)

            elif command == filter_ and parameters:
                apartments = functions.filter_expenses(apartments, parameters)
                stack.append(apartments[:])

            elif command == undo and not parameters:
                apartments = functions.undo(stack)

            else:
                print("Invalid command!")
        except ValueError as error:
            print("Error occurred: ", error)
