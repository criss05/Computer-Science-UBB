import os

from domain.bus_domain import BusDomain
from repo_exceptions import BusIDAlreadyExist, BusIDDoesNotExist


class BusRepo:
    def __init__(self):
        self.__buses = {}

    def add_bus(self, bus: BusDomain):
        if bus.bus_id in self.__buses:
            raise BusIDAlreadyExist
        self.__buses[bus.bus_id] = bus

    def get_all_buses(self):
        """
        Returnes all the buses in the list
        """
        return list(self.__buses.values())

    def get_bus_by_id(self, bus_id):
        if bus_id not in self.__buses:
            raise BusIDDoesNotExist
        return self.__buses[bus_id]


class BusFileRepo(BusRepo):
    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name
        self.load_buses()

    def add_bus(self, bus: BusDomain):
        super().add_bus(bus)
        self.save_buses()

    def load_buses(self):
        try:
            if os.path.exists(self.__file_name):
                file_repo = open(self.__file_name, 'r')
                lines = file_repo.readlines()
                for line in lines:
                    bus_id, route_code, model, times_used_route = line.strip().split(', ')
                    bus = BusDomain(bus_id, route_code, model, times_used_route)
                    super().add_bus(bus)
                file_repo.close()
        except EOFError:
            raise FileNotFoundError("File not found!")

    def save_buses(self):
        file_repo = open(self.__file_name, 'w')
        for bus in self.get_all_buses():
            file_repo.write(f"{bus.bus_id}, {bus.route_code}, {bus.model}, {bus.times_used_route}\n")
        file_repo.close()
