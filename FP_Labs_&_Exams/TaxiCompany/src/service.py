from domain import TaxiDomain


class TaxiService:
    def __init__(self,repository):
        self.__repository = repository

    def add_taxi(self, taxi_id, name, number, x, y):
        taxi = TaxiDomain(taxi_id, name, number, x, y)
        self.__repository.add_taxi(taxi)

    def get_all_taxis(self):
        return self.__repository.get_all_taxis()

    def find_taxis_having_given_distance_from_given_position(self, distance, given_x, given_y):
        taxis = self.get_all_taxis()
        taxis_found = []
        for taxi in taxis:
            if ((taxi.x - given_x) ** 2 + (taxi.y - given_y) ** 2) ** 0.5 <= distance:
                taxis_found.append(taxi)
        return taxis_found

    def find_min_distance(self):
        minim_distance = 100000
        min_x = 101
        min_y = 101
        for i in range(-100, 101):
            for j in range(-100, 101):
                distance = 0
                exists = False
                for taxi in self.get_all_taxis():
                    distance += ((taxi.x - i) ** 2 + (taxi.y - j) ** 2) ** 0.5
                    if taxi.x == i and taxi.y == j:
                        exists = True
                if distance < minim_distance and not exists:
                    minim_distance = distance
                    min_x = i
                    min_y = j
        return min_x, min_y
