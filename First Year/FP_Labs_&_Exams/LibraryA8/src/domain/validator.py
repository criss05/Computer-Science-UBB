import datetime
from src.domain.domain_exceptions import ClientValidationError, BookValidationError, RentalValidationError


class ValidateClient:
    def __init__(self):
        pass

    def validate_client(self, client):
        errors = []
        if len(client.name) < 3:
            errors.append("Client Name invalid!")
        if not client.client_id.isnumeric():
            errors.append("ID should be numeric!")
        if errors:
            raise ClientValidationError(errors)


class ValidateBook:
    def __init__(self):
        pass

    def validate_book(self, book):
        errors = []
        if not book.book_id.isnumeric():
            errors.append("ID should be numeric!")
        if len(book.author) < 3 or len(book.title) < 3:
            errors.append("Author and Title should have at least 3 characters!")
        if errors:
            raise BookValidationError(errors)


class ValidateRental:
    def __init__(self):
        pass

    def validate_rental(self, rental):
        errors = []
        if not rental.rental_id.isnnumeric():
            errors.append("ID should be numeric!")
        try:
            datetime.datetime.strptime(rental.rented_date, "%d/%m")
        except ValueError:
            errors.append("Date should be DD/MM")
        if rental.returned_date:
            try:
                datetime.datetime.strptime(rental.returned_date, "%d/%m")
            except ValueError:
                errors.append("Date should be DD/MM")
        if errors:
            raise RentalValidationError(errors)
