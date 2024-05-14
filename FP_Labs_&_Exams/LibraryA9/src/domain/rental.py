class Rental:
    def __init__(self, rental_id, book_id, client_id, rented_date, returned_date):
        self._rental_id = rental_id
        self._book_id = book_id
        self._client_id = client_id
        self._rented_date = rented_date
        self._returned_date = returned_date

    @property
    def rental_id(self):
        return self._rental_id

    @property
    def book_id(self):
        return self._book_id

    @property
    def client_id(self):
        return self._client_id

    @property
    def rented_date(self):
        return self._rented_date

    @property
    def returned_date(self):
        return self._returned_date

    @rented_date.setter
    def rented_date(self, new_rented_date):
        self._rented_date = new_rented_date

    @returned_date.setter
    def returned_date(self, new_returned_date):
        self._returned_date = new_returned_date

    def __eq__(self, rental):
        if not isinstance(rental, Rental):
            return False
        return self.rental_id == rental.rental_id

    def __str__(self):
        return (
            f"Rental ID: {self.rental_id} | Book ID: {self.book_id} | Client ID: {self.client_id} | "
            f"Rented date: {self.rented_date} | Returned date: {self.returned_date}")
