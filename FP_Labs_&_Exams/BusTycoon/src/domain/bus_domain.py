class BusDomain:
    def __init__(self, bus_id, route_code, model, times_used_route):
        self.__bus_id = bus_id
        self.__route_code = route_code
        self.__model = model
        self.__times_used_route = times_used_route

    @property
    def bus_id(self):
        return self.__bus_id

    @property
    def route_code(self):
        return self.__route_code

    @property
    def model(self):
        return self.__model

    @property
    def times_used_route(self):
        return self.__times_used_route

    def __str__(self):
        return f"{self.bus_id}, {self.route_code}, {self.model}, {self.times_used_route}"
