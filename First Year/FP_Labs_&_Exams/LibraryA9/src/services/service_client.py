from src.domain.client import Client
import random

from src.repository.client_repository import ClientBinaryRepository, ClientTextFileRepository
from src.services.undo_service import Command, Operation


class Service_client:
    def __init__(self, repository, client_validation, undo_service):
        self.__repository = repository
        self.__client_validation = client_validation
        self.__undo_service = undo_service

    def add_client(self, client_id, client_name):
        """
        Add a client
        :param client_id:
        :param client_name:
        :return:
        """
        client = Client(client_id, client_name)
        self.__client_validation.validate_client(client)
        self.__repository.add_a_client(client)
        undo_action = Command(self.remove_client, client_id)
        redo_action = Command(self.add_client, client_id, client_name)
        operation = Operation(undo_action, redo_action)
        self.__undo_service.record_for_undo(operation)
        self.save_clients_to_file()

    def remove_client(self, client_id):
        """
        Remove a client
        :param client_id:
        :return:
        """
        deleted_client = self.__repository.remove_a_client(client_id)
        undo_action = Command(self.add_client, deleted_client.client_id, deleted_client.name)
        redo_action = Command(self.remove_client, client_id)
        operation = Operation(undo_action, redo_action)
        self.__undo_service.record_for_undo(operation)
        self.save_clients_to_file()

    def update_client(self, client_id, new_client_name):
        """
        Update a client
        :param client_id:
        :param new_client_name:
        :return:
        """
        old_client_name = self.__repository.getclient(client_id).name
        client = Client(client_id, new_client_name)
        self.__client_validation.validate_client(client)
        self.__repository.update_client(client)
        undo_action = Command(self.update_client, client_id, old_client_name)
        redo_action = Command(self.update_client, client_id, new_client_name)
        operation = Operation(undo_action, redo_action)
        self.__undo_service.record_for_undo(operation)
        self.save_clients_to_file()

    def search_client_by_id(self, client_id):
        return self.__repository.search_client_by_id(client_id)

    def search_client_by_name(self, client_name):
        return self.__repository.search_client_by_name(client_name)

    def get_clients(self):
        return self.__repository.get_all_clients()

    def save_clients_to_file(self):
        if isinstance(self.__repository, ClientTextFileRepository) or isinstance(self.__repository, ClientBinaryRepository):
            self.__repository.save_clients_to_file()

    def generate_20_clients(self):
        client_names = ["Ana", "Briana", "Cristian", "Dragos", "Emilia", "Florin", "Gabriela", "Horia", "Ioana",
                        "Jessica", "Karina", "Lucian", "Maria", "Nicu", "Olivia", "Petru", "Raisa", "Sorana", "Tania",
                        "Victor"]
        for client_id in range(1, 21):
            client_name = client_names[random.randint(0, 19)]
            self.add_client(str(client_id), client_name)
