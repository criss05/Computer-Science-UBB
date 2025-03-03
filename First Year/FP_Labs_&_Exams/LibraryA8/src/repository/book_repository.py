from src.domain.book import Book
from src.repository.repository_exceptions import DuplicateIDException, IDDoesNotExistException


class BookRepository:
    def __init__(self):
        self._books = {}

    def add_a_book(self, new_book: Book):
        """
        Add a book
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
        del self._books[book_id]

    def update_book(self, new_book):
        """
        Update a book
        :param new_book:
        :return:
        """
        if new_book.book_id not in self._books:
            raise IDDoesNotExistException
        self._books[new_book.book_id] = new_book

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

