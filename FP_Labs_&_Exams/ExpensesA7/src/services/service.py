from src.domain.domain import Expenses
from src.repository.FileRepository import FileRepository
from src.repository.BinaryRepository import BinaryRepository


class Services:
    def __init__(self, repository):
        self.__repository = repository

    def add_expense(self, day, amount, type_):
        """
        The functions add an expense to the expenses list
        :param day: The expense day
        :param amount: The amount of money
        :param type_: The expense type
        :return: The updated list of expenses
        """
        if day.isnumeric():
            start_day = 1
            end_day = 30
            if not start_day <= int(day) <= end_day:
                raise ValueError("Day must be between 1 and 30!")
        else:
            raise ValueError("Day must be an integer!")
        if not amount.isnumeric():
            raise ValueError("Amount must be an positive integer!")
        if type_.isnumeric():
            raise ValueError("Type must not be a number!")
        try:
            expense = Expenses(day, amount, type_)
            self.__repository.add_expense(expense)
            self.save_expenses()
        except ValueError as error:
            print("Error occurred: ", error)

    def get_all_expenses(self):
        """
        Gets all expenses from the repository
        :return: The list of expenses to the UI module
        """
        try:
            return self.__repository.get_expenses()
        except ValueError as error:
            print("Error occurred: ", error)

    def filter_expense_by_given_value(self, given_amount):
        """
        Filter the expenses list such that the new list to contain just expenses with amount bigger than the given amount
        :param given_amount: The input amount to compare the expenses amount with
        :return: The new list of expenses
        """
        if not given_amount.isnumeric():
            raise ValueError("Amount must be integer")
        try:
            self.__repository.filter_expense_above_a_given_value(given_amount)
            self.save_expenses()
        except ValueError as error:
            print("Error occurred: ", error)

    def undo(self):
        """
        Undoes the last operation made by user
        :return: The previous list of expenses
        """
        try:
            self.__repository.undo()
            self.save_expenses()
        except ValueError as error:
            print("Error occurred: ", error)

    def save_expenses(self):
        """
        Saves expenses into a text file or a pickle, depending on the case
        """
        if isinstance(self.__repository, FileRepository) or isinstance(self.__repository, BinaryRepository):
            self.__repository.save_expenses()

    def is_empty(self):
        """
        Check if the list is empty
        """
        empty = 0
        if self.__repository.expenses_list_length() == empty:
            return True
        return False

    def generate_10_expenses_for_beginning(self):
        """
        Add 10 expenses in the list at the first start of the program so the list to not be empty when program runs
        :return: The generated list
        """
        self.add_expense('1', '200', 'gas')
        self.add_expense('2', '50', 'water')
        self.add_expense('3', '60', 'heat')
        self.add_expense('4', '80', 'electricity')
        self.add_expense('5', '130', 'gas')
        self.add_expense('6', '255', 'heat')
        self.add_expense('7', '90', 'heat')
        self.add_expense('8', '89', 'water')
        self.add_expense('9', '67', 'gas')
        self.add_expense('10', '93', 'electricity')
        self.__repository._previous_state = []
