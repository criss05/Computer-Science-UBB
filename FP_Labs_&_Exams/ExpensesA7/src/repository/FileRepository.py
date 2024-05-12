import os

from src.repository.MemoryRepository import MemoryRepository
from src.domain.domain import Expenses


class FileRepository(MemoryRepository):
    def __init__(self):
        super().__init__()
        self.load_expenses()
        self._previous_state = []

    def load_expenses(self):
        """
        Loads the expenses from the text file
        :return: The loaded list of expenses
        """
        if os.path.exists("file_repo.txt"):
            file_repo = open("file_repo.txt", 'r')
            lines = file_repo.readlines()
            for line in lines:
                day, amount, type_ = line.strip().split()
                self.add_expense(Expenses(day, amount, type_))
            file_repo.close()

    def save_expenses(self):
        """
        Saves the list in the text file
        """
        file_repo = open("file_repo.txt", 'w')
        for expense in self._expenses:
            file_repo.write(f"{expense.day} {expense.amount_of_money} {expense.type_expenses}\n")
        file_repo.close()
