import os.path
from domain.route_domain import RouteDomain
from repo_exceptions import RouteIDAlreadyExist, RouteIDDoesNotExist


class RouteRepo:
    def __init__(self):
        self.__routes = {}

    def add_route(self, route):
        if route.route_code in self.__routes:
            raise RouteIDAlreadyExist
        self.__routes[route.route_code] = route

    def get_all_routes(self):
        """
        Returns all routes in list
        """
        return list(self.__routes.values())

    def get_route_by_code(self, route_code):
        if route_code not in self.__routes:
            raise RouteIDDoesNotExist
        return self.__routes[route_code]


class RouteFileRepo(RouteRepo):
    def __init__(self, file_name):
        self.__file_name = file_name
        super().__init__()
        self.load_routes()

    def add_route(self, route):
        super().add_route(route)
        self.save_routes()

    def load_routes(self):
        if os.path.exists(self.__file_name):
            file_repo = open(self.__file_name, 'r')
            lines = file_repo.readlines()
            for line in lines:
                route_code, length = line.strip().split(', ')
                route = RouteDomain(route_code, length)
                super().add_route(route)
            file_repo.close()

    def save_routes(self):
        file_repo = open(self.__file_name, 'w')
        for route in self.get_all_routes():
            file_repo.write(f"{route.route_code}, {route.length}\n")
        file_repo.close()
