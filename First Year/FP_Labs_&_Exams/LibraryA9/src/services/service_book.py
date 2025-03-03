import random
from src.domain.book import Book
from src.repository.book_repository import BookBinaryRepository, BookTextFileRepository
from src.services.undo_service import Command, Operation


class Service_book:
    def __init__(self, repository, book_validation, undo_service):
        self.__repository = repository
        self.__book_validation = book_validation
        self.__undo_service = undo_service

    def add_book(self, id_book, title, author):
        """
        Add a book to repo
        :param id_book:
        :param title:
        :param author:
        :return:
        """
        book = Book(id_book, title, author)
        self.__book_validation.validate_book(book)
        self.__repository.add_a_book(book)
        undo_action = Command(self.remove_book, id_book)
        redo_action = Command(self.add_book, id_book, title, author)
        operation = Operation(undo_action, redo_action)
        self.__undo_service.record_for_undo(operation)
        self.save_books_to_file()

    def remove_book(self, id_book):
        """
        Remove a book from repo
        :param id_book:
        :return:
        """
        deleted_book = self.__repository.remove_a_book(id_book)
        undo_action = Command(self.add_book, deleted_book.book_id, deleted_book.title, deleted_book.author)
        redo_action = Command(self.remove_book, id_book)
        operation = Operation(undo_action, redo_action)
        self.__undo_service.record_for_undo(operation)
        self.save_books_to_file()

    def update_book(self, id_book, new_title, new_author):
        """
        Update a book in repo
        :param id_book:
        :param new_title:
        :param new_author:
        :return:
        """
        old_book_title = self.__repository.get_book(id_book).title
        old_book_author = self.__repository.get_book(id_book).author
        book = Book(id_book, new_title, new_author)
        self.__repository.update_book(book)
        undo_action = Command(self.update_book, id_book, old_book_title, old_book_author)
        redo_action = Command(self.update_book, id_book, new_title, new_author)
        operation = Operation(undo_action, redo_action)
        self.__undo_service.record_for_undo(operation)
        self.save_books_to_file()

    def get_books(self):
        return self.__repository.get_all_books()

    def search_book_by_id(self, id_book):
        return self.__repository.search_book_by_id(id_book)

    def search_book_by_title(self, book_title):
        return self.__repository.search_book_by_title(book_title)

    def search_book_by_author(self, book_author):
        return self.__repository.search_book_by_author(book_author)

    def save_books_to_file(self):
        if isinstance(self.__repository, BookTextFileRepository) or isinstance(self.__repository, BookBinaryRepository):
            self.__repository.save_books_to_file()

    def generate_20_books(self):
        book_titles = ["Harry Potter", "Sense and Sensibility", "The Hobbit", "The hunger games", "Pride and prejudice",
                       "Emma", "Anna Karenina", "Murder on the Orient Express", "Sherlok Holmes", "War and peace",
                       "1984", "The Great Gatsby"]
        book_authors = ["J. K. Rowling", "Jane Austen", "J.R.R. Tolkien", "Suzanne Collins", "Jane Austen",
                        "Jane Austen", "Lev Tolstoy", "Agatha Christie", "Arthur Conan Doyle", "Lev Tolstoy",
                        "George Orwel", " F. Scott Fitzger"]
        for book_id in range(1, 21):
            index = random.randint(0, 11)
            book_title = book_titles[index]
            book_author = book_authors[index]
            self.add_book(str(book_id), book_title, book_author)
