class RepositoryException(Exception):
    def __init__(self, error_message):
        self._error_message = error_message

    @property
    def message(self):
        return self._error_message

    def __str__(self):
        return "Repo Exception: " + str(self.message)


class DuplicateIDException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "Id already exist!")


class IDDoesNotExistException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "Id does not exist!")


class BookAlreadyRentedException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "Book already rented!")


class BookWasNotRentedException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self,
                                     "A book can be returned if it was rented before or if it was not returned yet!")


class IDNotRentedException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "This ID is not in rental list!")


class DateNotFoundException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "The date was not found!")
