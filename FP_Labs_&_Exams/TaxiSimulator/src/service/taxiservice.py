import random
from domain.taxidomain import TaxiDomain


class TaxiService:
    def __init__(self, repository):
        self._repository = repository

    def get_all_taxis(self):
        return self._repository.get_all_taxis()

    def generate_random_taxis(self, number_of_taxis):
        taxis_coordonates = []
        while number_of_taxis:
            x = random.randint(0, 100)
            y = random.randint(0, 100)
            can_place_taxi_here = True
            for taxi_id in range(len(taxis_coordonates)):
                taxi_x, taxi_y = taxis_coordonates[taxi_id]
                if (abs(taxi_x - x) + abs(taxi_y - y)) <= 5:
                    can_place_taxi_here = False
            if can_place_taxi_here:
                taxis_coordonates.append((x, y))
                number_of_taxis -= 1
        for taxi_id in range(len(taxis_coordonates)):
            taxi = TaxiDomain(taxi_id + 1, taxis_coordonates[taxi_id], 0)
            self._repository.add_taxi(taxi)

    def add_ride(self, start_point, end_point):
        x_start, y_start = start_point
        x_end, y_end = end_point
        minimum_distance = 210
        closest_taxi_id = 0
        taxis = self._repository.get_all_taxis()
        for taxi in taxis:
            taxi_x, taxi_y = taxi.current_location
            if (abs(x_start - taxi_x) + abs(y_start - taxi_y)) < minimum_distance:
                minimum_distance = abs(x_start - taxi_x) + abs(y_start - taxi_y)
                closest_taxi_id = taxi.taxi_id
        total_fare = self._repository.get_taxi(closest_taxi_id).total_fare
        total_fare += abs(x_start - x_end) + abs(y_start - y_end)
        new_taxi = TaxiDomain(closest_taxi_id, (x_end, y_end), total_fare)
        self._repository.modify_taxi(new_taxi)

    def simulate_ride(self):
        x_start = random.randint(0, 100)
        y_start = random.randint(0, 100)
        x_end = random.randint(0, 100)
        y_end = random.randint(0, 100)
        while (abs(x_start - x_end) + abs(y_start - y_end)) < 10:
            x_start = random.randint(0, 100)
            y_start = random.randint(0, 100)
            x_end = random.randint(0, 100)
            y_end = random.randint(0, 100)
        self.add_ride((x_start, y_start), (x_end, y_end))

    def sort_taxis_by_total_fare(self):
        taxis = self._repository.get_all_taxis()
        for i in range(len(taxis)-1):
            for j in range(i+1, len(taxis)):
                if taxis[i].total_fare < taxis[j].total_fare:
                    taxis[i], taxis[j] = taxis[j], taxis[i]
        return taxis
