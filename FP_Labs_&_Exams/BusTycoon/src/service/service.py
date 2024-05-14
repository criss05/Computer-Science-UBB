class Service:
    def __init__(self, bus_repository, route_repository):
        self.__bus_repository = bus_repository
        self.__route_repository = route_repository

    def get_all_buses(self):
        """
            Returns all the buses in the repo
        """
        return self.__bus_repository.get_all_buses()

    def get_all_routes(self):
        """
        Returns all the routes in repo
        """
        return self.__route_repository.get_all_routes()

    def find_buses_on_route(self, given_route_code):
        buses_found = []
        for bus in self.get_all_buses():
            if bus.route_code == given_route_code:
                buses_found.append(bus)
        return buses_found

    def kilometers_travelled(self, bus_id: str):
        """
        Calculate the number of kilometers the bus with the given bus id has travelled on his route
        :param bus_id: The bus id
        :return: The bus data and the distance
        """
        bus = self.__bus_repository.get_bus_by_id(bus_id)
        route = self.__route_repository.get_route_by_code(bus.route_code)
        distance = int(bus.times_used_route) * int(route.length)
        return bus, distance

    def sort_routes_by_milage(self):
        routes = self.get_all_routes()
        mileage = {}
        for route in routes:
            buses_on_route = self.find_buses_on_route(route.route_code)
            total_mileage = 0
            for bus in buses_on_route:
                the_bus, distance = self.kilometers_travelled(bus.bus_id)
                total_mileage += distance
            mileage[route.route_code] = total_mileage
        for i in range(len(routes)-1):
            for j in range(i+1, len(routes)):
                if mileage[routes[i].route_code] < mileage[routes[j].route_code]:
                    routes[i], routes[j] = routes[j], routes[i]
        return routes
