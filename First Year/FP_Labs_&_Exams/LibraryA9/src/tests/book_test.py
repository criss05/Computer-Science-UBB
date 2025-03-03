import unittest
from src.domain.book import Book
from src.domain.validator import ValidateBook
from src.repository.book_repository import BookRepository
from src.services.service_book import Service_book


class TestBook(unittest.TestCase):
    def setUp(self):
        self.book_repositpry = BookRepository()
        self.book_validator = ValidateBook()
        self.book_service = Service_book(self.book_repositpry, self.book_validator)

    def test_add_book(self):
        self.book_service.add_book('1', 'Emma', 'Jane Austen')
        self.assertEqual(self.book_service.get_books(), [Book('1', 'Emma', 'Jane Austen')])

        self.book_service.add_book('2', 'Sense and Sensibility', 'Jane Austen')
        self.assertEqual(self.book_service.get_books(),
                         [Book('1', 'Emma', 'Jane Austen'), Book('2', 'Sense and Sensibility', 'Jane Austen')])

    def test_remove_book(self):
        self.book_service.add_book('1', 'Emma', 'Jane Austen')
        self.book_service.add_book('2', 'Sense and Sensibility', 'Jane Austen')
        self.book_service.add_book('3', 'Harry Poter', 'J. K. Rowling')

        self.book_service.remove_book('1')
        self.assertEqual(self.book_service.get_books(),
                         [Book('2', 'Sense and Sensibility', 'Jane Austen'), Book('3', 'Harry Poter', 'J. K. Rowling')])

        self.book_service.remove_book('3')
        self.assertEqual(self.book_service.get_books(), [Book('2', 'Sense and Sensibility', 'Jane Austen')])

    def test_update_book(self):
        self.book_service.add_book('1', 'Emma', 'Jane Austen')
        self.book_service.add_book('2', 'Sense and Sensibility', 'Jane Austen')
        self.book_service.add_book('3', 'Harry Poter', 'J. K. Rowling')

        self.book_service.update_book('3', 'Pride and prejudice', 'Jane Austen')
        self.assertEqual(self.book_service.get_books(),
                         [Book('1', 'Emma', 'Jane Austen'), Book('2', 'Sense and Sensibility', 'Jane Austen'),
                          Book('3', 'Pride and prejudice', 'Jane Austen')])

        self.book_service.update_book('1', 'The Hobbit', 'J.R.R. Tolkien')
        self.assertEqual(self.book_service.get_books(),
                         [Book('1', 'The Hobbit', 'J.R.R. Tolkien'), Book('2', 'Sense and Sensibility', 'Jane Austen'),
                          Book('3', 'Pride and prejudice', 'Jane Austen')])
