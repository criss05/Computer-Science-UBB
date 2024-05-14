
"import pickle
import os
from src.repository.MemoryRepository import MemoryRepository


class BinaryRepository(MemoryRepository):
    def __init__(self):
        super().__init__()
        self.load_expenses()
        self._previous_state = []

    def load_expenses(self):
        """
        Load expense from the binary file
        :return: The loaded list
        """
        if os.path.exists("binary_repo.pkl"):
            binary_repo = open("binary_repo.pkl", 'rb')
            self._expenses = pickle.load(binary_repo)
            binary_repo.close()

    def save_expenses(self):
        """
        Saves the list in the binary file
        """
        binary_repo = open("binary_repo.pkl", 'wb')
        pickle.dump(self._expenses, binary_repo)
        binary_repo.close()
