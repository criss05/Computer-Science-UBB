from src.domain.domain import Expenses


class MemoryRepository:
    def __init__(self):
        self._expenses = []
        self._previous_state = []

    def add_expense(self, given_expense: Expenses):
        """
        Add an expense into the list and saves it in file if is the case
        :param given_expense: The expense user gave
        :return: The new list
        """
        for expense in self._expenses:
            if expense == given_expense:
                raise ValueError("Expense already exist!")
        self._previous_state.append(self._expenses[:])
        self._expenses.append(given_expense)

    def filter_expense_above_a_given_value(self, given_amount):
        """
        Filter the expenses list such that the new list to contain just expenses with amount bigger than the given amount
        :param given_amount: The input amount to compare the expenses amount with
        :return: The new list of expenses
        """
        self._previous_state.append(self._expenses[:])
        new_list = []
        for expense in self._expenses:
            if int(expense.amount_of_money) > int(given_amount):
                new_list.append(expense)
        self._expenses = new_list[:]

    def get_expenses(self):
        """
        Gets expenses list
        :return: The list of expenses to the service module
        """
        return self._expenses.copy()

    def undo(self):
        """
        Undoes the last operation made by user
        :return: The previous list of expenses
        """
        if self._previous_state:
            self._expenses = self._previous_state.pop()
        else:
            raise ValueError("Nothing to undo!")

    def expenses_list_length(self):
        """
        :return: The length of the list
        """
        return len(self._expenses)
