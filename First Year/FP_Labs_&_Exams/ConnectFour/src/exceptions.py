class Exceptions(Exception):
    def __init__(self, error_message: str):
        self.__error_message = error_message

    @property
    def error_message(self):
        return self.__error_message

    def __str__(self):
        return self.error_message


class OutsideOfBoundsError(Exceptions):
    def __init__(self):
        Exceptions.__init__(self, "Place outside the board. Choose a proper column.")


class ColumnFullError(Exceptions):
    def __init__(self):
        Exceptions.__init__(self, "This column is full. Choose another one.")


class InvalidInputException(Exceptions):
    def __init__(self):
        Exceptions.__init__(self, "Invalid Input!")