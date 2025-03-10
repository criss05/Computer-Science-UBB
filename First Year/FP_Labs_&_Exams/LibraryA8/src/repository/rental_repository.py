from src.domain.rental import Rental
from src.repository.book_repository import BookRepository
from src.repository.repository_exceptions import BookAlreadyRentedException, BookWasNotRentedException, \
    IDDoesNotExistException, IDNotRentedException, DateNotFoundException


class RentalRepository:
    def __init__(self):
        self._rentals = {}

    def rent_book(self, rent_book: Rental):
        book_already_rented = False
        for book in self._rentals.values():
            if self.book_is_already_rented(rent_book, book):
                book_already_rented = True
        if book_already_rented:
            raise BookAlreadyRentedException
        self._rentals[rent_book.rental_id] = rent_book

    @staticmethod
    def book_is_already_rented(rent_book, other_book):
        if rent_book.book_id == other_book.book_id and (
                not other_book.returned_date or other_book.returned_date >= rent_book.rented_date):
            return True
        return False

    def return_book(self, book_id, update_returned_date):
        book_not_rented = False
        rental_id_ = None
        for book in self._rentals.values():
            if book_id in book.book_id and not book.returned_date:
                book_not_rented = True
                rental_id_ = book.rental_id
        if not book_not_rented:
            raise BookWasNotRentedException
        book = self._rentals[rental_id_]
        book.returned_date = update_returned_date


    def search_rental_by_rental_id(self, rental_id):
        search_rental = []
        for rental in self._rentals:
            if rental_id.lower().strip() in rental.rental_id.lower().strip():
                search_rental.append(rental)
        if search_rental:
            return search_rental
        else:
            raise IDDoesNotExistException

    def search_rental_by_book_id(self, book_id):
        search_rental = []
        for rental in self._rentals.values():
            if book_id.lower().strip() in rental.book_id.lower().strip():
                search_rental.append(rental)
        if search_rental:
            return search_rental
        else:
            raise IDNotRentedException

    def search_rental_by_client_id(self, client_id):
        search_rental = []
        for rental in self._rentals.values():
            if client_id.lower().strip() in rental.client_id.lower().strip():
                search_rental.append(rental)
        if search_rental:
            return search_rental
        else:
            raise IDDoesNotExistException

    def search_rental_by_rented_date(self, rented_date):
        search_rental = []
        for rental in self._rentals.values():
            if rented_date.lower().strip() in rental.rented_date.lower().strip():
                search_rental.append(rental)
        if search_rental:
            return search_rental
        else:
            raise DateNotFoundException

    def search_rental_by_returned_date(self, returned_date):
        search_rental = []
        for rental in self._rentals.values():
            if returned_date.lower().strip() in rental.returned_date.lower().strip():
                search_rental.append(rental)
        if search_rental:
            return search_rental
        else:
            raise DateNotFoundException

    def get_all_rentals(self):
        return list(self._rentals.values())
