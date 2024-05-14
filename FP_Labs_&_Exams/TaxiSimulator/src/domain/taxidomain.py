class TaxiDomain:
    def __init__(self, taxi_id, curent_location, total_fare):
        self._taxi_id = taxi_id
        self._curent_location = curent_location
        self._total_fare = total_fare

    @property
    def taxi_id(self):
        return self._taxi_id

    @property
    def current_location(self):
        return self._curent_location

    @property
    def total_fare(self):
        return self._total_fare

    def __str__(self):
        return f'ID: {self._taxi_id}  Current location {self._curent_location}  Total fare: {self._total_fare}'

    def __eq__(self, other):
        if not isinstance(other, TaxiDomain):
            return False
        return (self.taxi_id == other.taxi_id and self.current_location == other.current_location and
                self.total_fare == other.total_fare)
