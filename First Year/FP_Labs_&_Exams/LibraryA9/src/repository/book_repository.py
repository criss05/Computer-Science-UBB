import os
import pickle

from src.domain.book import Book
from src.repository.repository_exceptions import DuplicateIDException, IDDoesNotExistException


class BookRepository:
    def __init__(self):
        self._books = {}

    def add_a_book(self, new_book: Book):
        """
        Add a boook
        :param new_book:
        :return:
        """
        if new_book.book_id in self._books:
            raise DuplicateIDException
        self._books[new_book.book_id] = new_book

    def remove_a_book(self, book_id: str):
        """
        Remove a book
        :param book_id:
        :return:
        """
        if book_id not in self._books:
            raise IDDoesNotExistException
        deleted_book = self._books[book_id]
        del self._books[book_id]
        return deleted_book

    def update_book(self, new_book):
        """
        Upadte a book
        :param new_book:
        :return:
        """
        if new_book.book_id not in self._books:
            raise IDDoesNotExistException
        self._books[new_book.book_id] = new_book

    def get_book(self, book_id):
        if book_id in self._books:
            return self._books[book_id]
        raise IDDoesNotExistException

    def get_all_books(self):
        return list(self._books.values())

    def search_book_by_id(self, book_id):
        search_book = []
        for book in self._books.values():
            if book_id.lower().strip() in book.book_id.lower().strip():
                search_book.append(book)
        if search_book:
            return search_book
        else:
            raise IDDoesNotExistException

    def search_book_by_author(self, book_author):
        search_book = []
        for book in self._books.values():
            if book_author.lower().strip() in book.author.lower().strip():
                search_book.append(book)
        if search_book:
            return search_book
        else:
            raise IDDoesNotExistException

    def search_book_by_title(self, book_title):
        search_book = []
        for book in self._books.values():
            if book_title.lower().strip() in book.title.lower().strip():
                search_book.append(book)
        if search_book:
            return search_book
        else:
            raise IDDoesNotExistException
        

class BookBinaryRepository(BookRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name
        self.load_books_from_file()

    def load_books_from_file(self):
        try:
            if os.path.exists(self.__file_name):
                file = open(self.__file_name, 'rb')
                self._books = pickle.load(file)
                file.close()
        except EOFError:
            raise FileNotFoundError("File not found")

    def save_books_to_file(self):
        file = open(self.__file_name, 'wb')
        pickle.dump(self._books, file)
        file.close()


class BookTextFileRepository(BookRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name
        self.load_books_from_file()

    def load_books_from_file(self):
        try:
            if os.path.exists(self.__file_name):
                file = open(self.__file_name, 'r')
                lines = file.readlines()
                for line in lines:
                    book_id, book_title, book_author = line.strip().split(' , ')
                    self.add_a_book(Book(book_id, book_title, book_author))
                file.close()
        except EOFError:
            raise FileNotFoundError("File not found")

    def save_books_to_file(self):
        file = open(self.__file_name, 'w')
        for book in self.get_all_books():
            file.write(f"{book.book_id} , {book.title} , {book.author}\n")
        file.close()
