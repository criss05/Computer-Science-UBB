import unittest
from unittest import TestCase

from src.domain.domain import Expenses
from src.repository.MemoryRepository import MemoryRepository
from src.services.service import Services


class TestFunction(TestCase):
    def setUp(self):
        self.__repository = MemoryRepository()
        self.__service = Services(self.__repository)

    def test_add_expense(self):
        self.__service.add_expense('12', '200', 'gas')
        self.assertEqual(self.__service.get_all_expenses(), [Expenses('12', '200', 'gas')])

        self.__service.add_expense('13', '20', 'water')
        self.assertEqual(self.__service.get_all_expenses(),
                         [Expenses('12', '200', 'gas'), Expenses('13', '20', 'water')])

        self.__service.add_expense('20', '50', 'heat')
        self.assertEqual(self.__service.get_all_expenses(),
                         [Expenses('12', '200', 'gas'), Expenses('13', '20', 'water'), Expenses('20', '50', 'heat')])

        self.__service.add_expense('15', '80', 'gas')
        self.assertEqual(self.__service.get_all_expenses(),
                         [Expenses('12', '200', 'gas'), Expenses('13', '20', 'water'), Expenses('20', '50', 'heat'),
                          Expenses('15', '80', 'gas')])
