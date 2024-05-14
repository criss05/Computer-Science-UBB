import unittest
from src.domain.client import Client
from src.domain.validator import ValidateClient
from src.repository.client_repository import ClientRepository
from src.services.service_client import Service_client


class TestClient(unittest.TestCase):
    def setUp(self):
        self.client_repositpry = ClientRepository()
        self.client_validator = ValidateClient()
        self.client_service = Service_client(self.client_repositpry, self.client_validator)

    def test_add_client(self):
        self.client_service.add_client('1', 'Andrei')
        self.assertEqual(self.client_service.get_clients(), [Client('1', 'Andrei')])

        self.client_service.add_client('2', 'Maria')
        self.assertEqual(self.client_service.get_clients(), [Client('1', 'Andrei'), Client('2', 'Maria')])

    def test_remove_client(self):
        self.client_service.add_client('1', 'Andrei')
        self.client_service.add_client('2', 'Maria')
        self.client_service.add_client('3', 'Marc')

        self.client_service.remove_client('1')
        self.assertEqual(self.client_service.get_clients(), [Client('2', 'Maria'), Client('3', 'Marc')])

        self.client_service.remove_client('3')
        self.assertEqual(self.client_service.get_clients(), [Client('2', 'Maria')])

    def test_update_client(self):
        self.client_service.add_client('1', 'Andrei')
        self.client_service.add_client('2', 'Maria')
        self.client_service.add_client('3', 'Marc')

        self.client_service.update_client('3', 'Dani')
        self.assertEqual(self.client_service.get_clients(),
                         [Client('1', 'Andrei'), Client('2', 'Maria'), Client('3', 'Dani')])

        self.client_service.update_client('1', 'Alex')
        self.assertEqual(self.client_service.get_clients(),
                         [Client('1', 'Alex'), Client('2', 'Maria'), Client('3', 'Dani')])