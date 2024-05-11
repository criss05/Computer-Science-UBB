# Project made by Bărnuț Cristiana
def number_validation(number: str, base: int):
    """
    This function checks if the number is valid taking into consideration the base
    :param number: The number we want to check
    :param base: The base in which we work
    :return: If the number is not correct the program will raise an error
    """
    possible_characters = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']
    for digit in number:
        if digit not in possible_characters:
            raise ValueError("Invalid numbers!!")
        elif digit.isnumeric():
            if int(digit) >= base:
                raise ValueError("Invalid numbers!!")
        else:
            if base != 16:
                raise ValueError("Invalid numbers!!")


def validation_base(base: str):
    """
    Checking if the base is in working interval
    :param base: The base we want to check
    :return: If the base is not good will raise an error
    """
    possible_bases = ['2', '3', '4', '5', '6', '7', '8', '9', '10', '16']
    if base in possible_bases:
        return int(base)
    else:
        raise ValueError("Incorrect base!")


def conversion_table_from_string_to_digit(digit: str) -> int:
    """
    Converts the digit given as a string into integer so the operations can be done
    :param digit: The digit we want to convert from string
    :return: The digit converted into integer
    """
    table = {"0": 0, "1": 1, "2": 2, "3": 3, "4": 4, "5": 5, "6": 6, "7": 7, "8": 8, "9": 9, "A": 10, "B": 11, "C": 12,
             "D": 13, "E": 14, "F": 15}
    return table[digit]


def conversion_table_from_digit_to_string(character: int) -> str:
    """
    Converts the digit given as an integer so the number can be concatenated and printed
    :param character: The digit we want to convert from integer
    :return: The digit converted into character
    """
    table = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']
    return table[character]


def addition(addend_1: str, addend_2: str, base: int) -> str:
    """
    The function make the sum between two numbers in some given base
    :param addend_1: The first numbers given
    :param addend_2: The second number given
    :param base: The base we use
    :return: The sum between the given numbers
    """
    addend_1 = addend_1.upper()
    addend_2 = addend_2.upper()
    # Make all characters uppercase if the input is with lowercase, so the calculation to be easier
    number_validation(addend_1, base)
    number_validation(addend_2, base)
    # Valid the numbers given
    carry = 0  # The first carry is 0
    result = ''  # In this variable will save the result
    while addend_1 or addend_2:
        if addend_1:
            digit_1 = conversion_table_from_string_to_digit(addend_1[len(addend_1) - 1])
        else:
            digit_1 = 0
        # If the first number is shorter than the second one the digits used for addition will be 0
        # Otherwise, the digit will be the last one from the number
        if addend_2:
            digit_2 = conversion_table_from_string_to_digit(addend_2[len(addend_2) - 1])
        else:
            digit_2 = 0
        # If the second number is shorter than the first one the digits used for addition will be 0
        # Otherwise, the digit will be the last one from the number
        partial_result = digit_1 + digit_2 + carry  # Partial sum using the formula
        carry = partial_result // base  # Sets the next carry
        result = conversion_table_from_digit_to_string(partial_result % base) + result
        # puts the partial sum in the final result
        addend_1 = addend_1[:-1]
        addend_2 = addend_2[:-1]
        # Eliminate the last digits from every number
    if carry:
        result = conversion_table_from_digit_to_string(carry) + result
        # if there is a carry at the end, add it to the result
    while result[0] == '0' and len(result) > 1:
        result = result[1:]
    # If the result has an 0 at the beginning, and it is different from 0it will be deleted
    return result


def subtraction(minuend: str, subtrahend: str, base: int) -> str:
    """
        The function make the difference between two numbers in some given base
        :param minuend: The first numbers given
        :param subtrahend: The second number given
        :param base: The base we use
        :return: The difference between the given numbers
    """
    minuend = minuend.upper()
    subtrahend = subtrahend.upper()
    # Make all characters uppercase if the input is with lowercase, so the calculation to be easier
    number_validation(minuend, base)
    number_validation(subtrahend, base)
    # Valid the numbers given
    borrow = 0  # Borrow is 0 at the beginning
    result = ''  # In this variable will save the result
    if len(minuend) < len(subtrahend):
        raise ValueError("The minuend is bigger then the subtrahend! Please enter proper operators!")
    # If the minuend is less then the subtrahend, will raise an error because the operation i s ot valid in this case
    while minuend or subtrahend:
        digit_1 = conversion_table_from_string_to_digit(minuend[len(minuend) - 1])
        # The digit from minuend will be the last one from the number
        if subtrahend:
            digit_2 = conversion_table_from_string_to_digit(subtrahend[len(subtrahend) - 1])
        else:
            digit_2 = 0
        # If the subtrahend is shorter than the minuend the digits used for subtraction will be 0
        # Otherwise, the digit will be the last one from the number
        partial_result = digit_1 - digit_2 + borrow  # We perform the partial subtraction
        if partial_result < 0:
            borrow = -1
            partial_result = conversion_table_from_digit_to_string(partial_result + base)
            # If the partial result is less than 0 the next borrow will be -1 and at the result the base will be added
        else:
            borrow = 0
            partial_result = conversion_table_from_digit_to_string(partial_result)
            # If the partial result is grater than 0 the next borrow will be 0 and the result will be the result
        result = partial_result + result
        # puts the partial subtraction in the final result
        minuend = minuend[:-1]
        subtrahend = subtrahend[:-1]
        # Eliminate the last digits of the number
    while result[0] == '0' and len(result) > 1:
        result = result[1:]
    # If the result has an 0 at the beginning, and it is different from 0it will be deleted
    return result


def multiplication(factor_1: str, factor_2: str, base: int) -> str:
    """
    This function will perform the multiplication of a number in a given base by one digit in the same base
    :param factor_1: The first factor
    :param factor_2: The second factor (one digit)
    :param base: The base we work on
    :return: The result of the multiplication
    """
    factor_1 = factor_1.upper()
    factor_2 = factor_2.upper()
    # Make all characters uppercase if the input is with lowercase, so the calculation to be easier
    number_validation(factor_1, base)
    number_validation(factor_2, base)
    # Valid the numbers given
    carry = 0  # First carry digit will be 0
    result = ''  # In this variable will save the result
    if len(factor_2) > 1:
        raise ValueError("Multiplication by one digit!!!")
    # The multiplication in made by one digit, so if the second factor is not a digit will raise an error
    factor_2 = conversion_table_from_string_to_digit(factor_2)
    # Convert the second number from character to integer
    while factor_1:
        digit_1 = conversion_table_from_string_to_digit(factor_1[len(factor_1) - 1])
        # Convert the last digit from the first number into integer
        partial_result = digit_1 * factor_2 + carry  # We perform the partial multiplication
        carry = partial_result // base  # Set the next carry digit
        result = conversion_table_from_digit_to_string(partial_result % base) + result
        # The final result will be updated
        factor_1 = factor_1[:-1]  # Eliminate the last digit in the first number
    if carry:
        result = conversion_table_from_digit_to_string(carry) + result
    # At the end, if there is a digit left, will be put in the result
    while result[0] == '0' and len(result) > 1:
        result = result[1:]
    # If the result has an 0 at the beginning, and it is different from 0it will be deleted
    return result


def division(dividend: str, divisor: str, base: int) -> tuple[str, str]:
    """
    This function will perform the division of a number in a given base by one digit in the same base
    :param dividend: The dividend given
    :param divisor:  The given divisor
    :param base: The base we work on
    :return: The result and the remainder of the division
    """
    dividend = dividend.upper()
    divisor = divisor.upper()
    # Make all characters uppercase if the input is with lowercase, so the calculation to be easier
    number_validation(dividend, base)
    number_validation(divisor, base)
    # Valid the numbers given
    result = ''  # In this variable will save the result
    if len(divisor) > 1:
        raise ValueError("Division by one digit!!!")
    # The division in made by one digit, so if the second factor is not a digit will raise an error
    divisor = conversion_table_from_string_to_digit(divisor)
    # Convert the divisor from character to integer
    if divisor == 0:
        raise ValueError("Division by 0!!!")
    # If the divisor is 0 then the division cannot be performed
    remainder = conversion_table_from_string_to_digit(dividend[0])
    # The first digit from the dividend will be the remainder we need for the first partial division
    while dividend:
        partial_result = remainder // divisor  # The partial division performed
        remainder = remainder % divisor  # The first remainder obtained
        result = result + conversion_table_from_digit_to_string(partial_result)
        # The final result will be updated
        dividend = dividend[1:]
        # The first digit from the dividend will be eliminated
        if not dividend:
            break
        remainder = remainder * base + conversion_table_from_string_to_digit(dividend[0])
        # The next remainder we need for partial division will be obtained in base 10 using the formula
    remainder = conversion_table_from_digit_to_string(remainder)
    # In the end the remainder will be converted from integer to character
    while result[0] == '0' and len(result) > 1:
        result = result[1:]
    # If the result has an 0 at the beginning, and it is different from 0it will be deleted
    return result, remainder
