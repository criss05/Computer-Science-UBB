class ValidationException(Exception):
    def __init__(self, error_message_list):
        self._error_messages = error_message_list

    @property
    def error_messages(self):
        return self._error_messages

    def __str__(self):
        return "Validation error:" + "\n".join(self.error_messages)


class ClientValidationError(ValidationException):
    def __init__(self, error_messages):
        ValidationException.__init__(self, error_messages)


class BookValidationError(ValidationException):
    def __init__(self, error_messages):
        ValidationException.__init__(self, error_messages)


class RentalValidationError(ValidationException):
    def __init__(self, error_messages):
        ValidationException.__init__(self, error_messages)
