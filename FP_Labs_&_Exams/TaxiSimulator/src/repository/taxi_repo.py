class TaxiRepository:
    def __init__(self):
        self._taxis = {}

    def add_taxi(self, taxi):
        self._taxis[taxi.taxi_id] = taxi

    def modify_taxi(self, taxi):
        self._taxis[taxi.taxi_id] = taxi

    def get_all_taxis(self):
        return list(self._taxis.values())

    def get_taxi(self, taxi_id):
        return self._taxis[taxi_id]
