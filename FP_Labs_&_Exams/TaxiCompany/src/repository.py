import os

from domain import TaxiDomain


class TaxiRepo:
    def __init__(self):
        self.__taxis = {}

    def add_taxi(self, taxi):
        if taxi.taxi_id in self.__taxis:
            raise ValueError("ID already exist!")
        self.__taxis[taxi.taxi_id] = taxi

    def get_all_taxis(self):
        return list(self.__taxis.values())


class FileRepo(TaxiRepo):
    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name
        self.load_taxis()

    def add_taxi(self, taxi):
        super().add_taxi(taxi)
        self.save_taxis()

    def load_taxis(self):
        try:
            if os.path.exists(self.__file_name):
                file_repo = open(self.__file_name, 'r')
                lines = file_repo.readlines()
                for line in lines:
                    taxi_id, name, number, x, y = line.strip().split(", ")
                    taxi = TaxiDomain(int(taxi_id), name, int(number), int(x), int(y))
                    super().add_taxi(taxi)
                file_repo.close()
        except EOFError:
            raise FileNotFoundError("File not found!")

    def save_taxis(self):
        file_repo = open(self.__file_name, 'w')
        for taxi in self.get_all_taxis():
            file_repo.write(f"{taxi.taxi_id}, {taxi.name}, {taxi.number}, {taxi.x}, {taxi.y}\n")
        file_repo.close()
