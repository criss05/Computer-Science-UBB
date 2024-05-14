import random
from src.domain.book import Book


class Service_book:
    def __init__(self, repository, book_validation):
        self.__repository = repository
        self.__book_validation = book_validation

    def add_book(self, id_book, title, author):
        """
        Add a book
        :param id_book:
        :param title:
        :param author:
        :return:
        """
        book = Book(id_book, title, author)
        self.__book_validation.validate_book(book)
        self.__repository.add_a_book(book)

    def remove_book(self, id_book):
        """
        Remove a book
        :param id_book:
        :return:
        """
        self.__repository.remove_a_book(id_book)

    def update_book(self, id_book, new_title, new_author):
        """
        Update a book
        :param id_book:
        :param new_title:
        :param new_author:
        :return:
        """
        book = Book(id_book, new_title, new_author)
        self.__repository.update_book(book)

    def get_books(self):
        return self.__repository.get_all_books()

    def search_book_by_id(self, id_book):
        return self.__repository.search_book_by_id(id_book)

    def search_book_by_title(self, book_title):
        return self.__repository.search_book_by_title(book_title)

    def search_book_by_author(self, book_author):
        return self.__repository.search_book_by_author(book_author)

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
