from unittest import TestCase
from domain.taxidomain import TaxiDomain
from repository.taxi_repo import TaxiRepository
from service.taxiservice import TaxiService


class TestAddRide(TestCase):
    def setUp(self):
        self.__repository = TaxiRepository()
        self.__service = TaxiService(self.__repository)

    def test_add_ride(self):
        self.__repository.add_taxi(TaxiDomain(1, (10, 10), 0))
        self.__repository.add_taxi(TaxiDomain(2, (50, 50), 0))
        self.__repository.add_taxi(TaxiDomain(3, (100, 100), 0))
        self.__service.add_ride((40, 40), (90, 90))

        self.assertEqual(self.__repository.get_all_taxis(),
                         [TaxiDomain(1, (10, 10), 0), TaxiDomain(2, (90, 90), 100), TaxiDomain(3, (100, 100), 0)])
