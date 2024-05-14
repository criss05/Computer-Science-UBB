

from src.domain.rental import Rental
from src.repository.rental_repository import RentalTextFileRepository, RentalBinaryRepository
from src.repository.repository_exceptions import IDDoesNotExistException, BookWasNotRentedException


class RentalService:
    def __init__(self, rental_repository, book_repository, client_repository, rental_validation):
        self._rental_repository = rental_repository
        self._book_repository = book_repository
        self._client_repository = client_repository
        self.__rental_validation = rental_validation

    def rent_book(self, book_id, client_id, rented_date):
        books = self._book_repository.get_all_books()
        clients = self._client_repository.get_all_clients()
        rentals = self._rental_repository.get_all_rentals()
        book_found = False
        for book in books:
            if book_id == book.book_id:
                book_found = True
        client_found = False
        for client in clients:
            if client_id == client.client_id:
                client_found = True
        if not book_found or not client_found:
            raise IDDoesNotExistException
        rental_id = len(rentals) + 1
        returned_date = None
        rental = Rental(rental_id, book_id, client_id, rented_date, returned_date)
        self._rental_repository.rent_book(rental)
        self.save_rentals_to_file()

    def return_book(self, book_id, returned_date):
        number_of_returned_date_for_book = 0
        number_of_not_returned_date_for_book = 0
        rentals = self._rental_repository.get_all_rentals()
        for book in rentals:
            if book_id in book.book_id:
                if book.returned_date:
                    number_of_returned_date_for_book += 1
                else:
                    number_of_not_returned_date_for_book += 1
        if number_of_returned_date_for_book > number_of_not_returned_date_for_book:
            raise BookWasNotRentedException
        self.save_rentals_to_file()
        return self._rental_repository.return_book(book_id, returned_date)

    def search_rental_by_rental_id(self, rental_id):
        return self._rental_repository.search_rental_by_rental_id(rental_id)

    def search_rental_by_book_id(self, book_id):
        return self._rental_repository.search_rental_by_book_id(book_id)

    def search_rental_by_client_id(self, client_id):
        return self._rental_repository.search_rental_by_client_id(client_id)

    def search_rental_by_rented_date(self, rented_date):
        return self._rental_repository.search_rental_by_rented_date(rented_date)

    def search_rental_by_returned_date(self, returned_date):
        return self._rental_repository.search_rental_by_returned_date(returned_date)

    def statistic_most_rented_books(self):
        rented_books = []
        rentals = self._rental_repository.get_all_rentals()
        books = self._book_repository.get_all_books()
        for book in books:
            for rental in rentals:
                if book.book_id == rental.book_id:
                    if book.title not in rented_books:
                        rented_books.append(book.title)
        for i in range(len(rented_books) - 1):
            for j in range(i + 1, len(rented_books)):
                if len(self._book_repository.search_book_by_title(rented_books[i])) < len(
                        self._book_repository.search_book_by_title(rented_books[j])):
                    rented_books[i], rented_books[j] = rented_books[j], rented_books[i]
        most_rented_books = []
        for title in most_rented_books:
            for book in books:
                if book.title == title:
                    most_rented_books.append(book)
        return most_rented_books

    def statistic_most_active_clients(self):
        active_clients = []
        rentals = self._rental_repository.get_all_rentals()
        clients = self._client_repository.get_all_clients()
        for client in clients:
            for rental in rentals:
                if client.client_id == rental.client_id:
                    if client.client_id not in active_clients:
                        active_clients.append(client.client_id)
        for i in range(len(active_clients) - 1):
            for j in range(i + 1, len(active_clients)):
                if len(self._client_repository.search_client_by_name(active_clients[i])) < len(
                        self._client_repository.search_client_by_name(active_clients[j])):
                    active_clients[i], active_clients[j] = active_clients[j], active_clients[i]
        most_active_clients = []
        for client in most_active_clients:
            for client_id in active_clients:
                if client.client_id == client_id:
                    most_active_clients.append(client)
        return most_active_clients

    def statistic_most_rented_author(self):
        rented_authors = []
        rentals = self._rental_repository.get_all_rentals()
        books = self._book_repository.get_all_books()
        for book in books:
            for rental in rentals:
                if book.book_id == rental.book_id:
                    if book.author not in rental:
                        rented_authors.append(book.author)
        for i in range(len(rented_authors) - 1):
            for j in range(i + 1, len(rented_authors)):
                if len(self._book_repository.search_book_by_author(rented_authors[i])) < len(
                        self._book_repository.search_book_by_author(rented_authors[j])):
                    rented_authors[i], rented_authors[j] = rented_authors[j], rented_authors[i]
        most_rented_authors = []
        for author in most_rented_authors:
            for book in books:
                if book.author == author:
                    most_rented_authors.append(book)
        return most_rented_authors

    def save_rentals_to_file(self):
        if isinstance(self._rental_repository, RentalTextFileRepository) or isinstance(self._rental_repository, RentalBinaryRepository):
            self._rental_repository.save_rentals_to_file()

    def get_rentals(self):
        return self._rental_repository.get_all_rentals()

    # def generate_20_rentals(self):
    #     for rental_id in range(1, 21):
    #         book_id = str(random.randint(1, 20))
    #         client_id = str(random.randint(1, 20))
    #         rented_day = str(random.randint(1,15))
    #         if len(rented_day) < 2:
    #             rented_day = '0' + rented_day
    #         rented_month = str(random.randint(1, 15))
    #         if len(rented_month) < 2:
    #             rented_month = '0' + rented_month
    #         returned_day = str(random.randint(1, 15))
    #         if len(returned_day) < 2:
    #             returned_day = '0' + returned_day
    #         returned_month = str(random.randint(1, 15))
    #         if len(returned_month) < 2:
    #             returned_month = '0' + returned_month
    #         self.rent_book(str(rental_id), str(book_id), str(cl))
