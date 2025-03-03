class RepoException(Exception):
    def __init__(self, error_message):
        self.__error_message = error_message

    @property
    def message(self):
        return self.__error_message

    def __str__(self):
        return f"Repo Exception: {self.message}"


class BusIDDoesNotExist(RepoException):
    def __init__(self):
        RepoException.__init__(self, "Bus id does not exist!")


class RouteIDDoesNotExist(RepoException):
    def __init__(self):
        RepoException.__init__(self, "Route ID does not exist!")


class BusIDAlreadyExist(RepoException):
    def __init__(self):
        RepoException.__init__(self, "Bus ID already exist!")


class RouteIDAlreadyExist(RepoException):
    def __init__(self):
        RepoException.__init__(self, "Route Id already exist!")
