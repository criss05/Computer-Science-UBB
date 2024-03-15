# Project made by Bărnuț Cristiana
import functions


def print_operation(number_1: str, number_2: str, result: str, sign: str, base: int):
    print('\n', number_1, sign, number_2, "=", result, " in base", base, '\n')


def print_menu():
    print("\nOPERATIONS IN DIFFERENT BASES\n"
          "Project made by Bărnuț Cristiana\n\n"
          "1. Add two numbers in a given base.\n"
          "2. Subtract two numbers in a given base.\n"
          "3. Multiply a number with a digit in a given base.\n"
          "4. Divide a number by a digit in a given base.\n\n"
          "!!!The base should be between 2 and 16.\n")


def menu_application():
    add = '1'
    subtract = '2'
    multiply = '3'
    divide = '4'
    while True:
        try:
            option = input("Please chose an option from the list above: ")
            # Depending on the user choice, the program will call the appropriate function and will return the result,
            # Then it's going to call the print function to print the desired operation
            if option == add:
                base = input("Please enter the base you want to use: ")
                base = functions.validation_base(base)
                addend_1 = input("Please enter the first addend: ")
                addend_2 = input("Please enter the second addend: ")
                result = functions.addition(addend_1, addend_2, base)
                print_operation(addend_1, addend_2, result, "+", base)

            elif option == subtract:
                base = input("Please enter the base you want to use: ")
                base = functions.validation_base(base)
                minuend = input("Please enter the minuend: ")
                subtrahend = input("Please enter the subtrahend: ")
                result = functions.subtraction(minuend, subtrahend, base)
                print_operation(minuend, subtrahend, result, "-", base)

            elif option == multiply:
                base = input("Please enter the base you want to use: ")
                base = functions.validation_base(base)
                factor_1 = input("Please enter the first factor: ")
                factor_2 = input("Please enter the second factor: ")
                result = functions.multiplication(factor_1, factor_2, base)
                print_operation(factor_1, factor_2, result, "×", base)

            elif option == divide:
                base = input("Please enter the base you want to use: ")
                base = functions.validation_base(base)
                dividend = input("Please enter the dividend: ")
                divisor = input("Please enter the divisor: ")
                result, remainder = functions.division(dividend, divisor, base)
                final_result = result + " remainder " + remainder
                print_operation(dividend, divisor, final_result, "÷", base)

            else:
                print("Invalid option!")
                # If the input option is not in the list will print an error
        except ValueError as validation:
            print(validation)
            # If there is anything wrong with the input given, the problem will print the error
