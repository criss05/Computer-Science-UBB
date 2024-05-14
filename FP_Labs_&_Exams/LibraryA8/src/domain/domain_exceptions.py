class ValidationException(Exception):
    def __init__(self, error_msg_list):
        self._error_messages = error_msg_list

    @property
    def error_messages(self):
        return self._error_messages

    def __str__(self):
        return "Validation error:" + "\n".join(self.error_messages)


class ClientValidationError(ValidationException):
    def __init__(self, error_msgs):
        ValidationException.__init__(self, error_msgs)


class BookValidationError(ValidationException):
    def __init__(self, error_msgs):
        ValidationException.__init__(self, error_msgs)


class RentalValidationError(ValidationException):
    def __init__(self, error_msgs):
        ValidationException.__init__(self, error_msgs)
