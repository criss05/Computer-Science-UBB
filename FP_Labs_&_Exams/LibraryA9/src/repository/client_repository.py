import os
import pickle

from src.domain.client import Client
from src.repository.repository_exceptions import DuplicateIDException, IDDoesNotExistException


class ClientRepository:
    def __init__(self):
        self._clients = {}

    def add_a_client(self, new_client: Client):
        """
        Add a client
        :param new_client:
        :return:
        """
        if new_client.client_id in self._clients:
            raise DuplicateIDException
        self._clients[new_client.client_id] = new_client

    def remove_a_client(self, client_id: str):
        """
        Remove a client
        :param client_id:
        :return:
        """
        if client_id not in self._clients:
            raise IDDoesNotExistException
        deleted_client = self._clients[client_id]
        del self._clients[client_id]
        return deleted_client

    def update_client(self, new_client):
        """
        Update a client
        :param new_client:
        :return:
        """
        if new_client.client_id not in self._clients:
            raise IDDoesNotExistException
        self._clients[new_client.client_id] = new_client

    def get_clients(self, client_id):
        if client_id in self._clients:
            return self._clients[client_id]
        raise IDDoesNotExistException

    def get_all_clients(self):
        return list(self._clients.values())

    def search_client_by_id(self, client_id):
        search_person = []
        for client in self._clients.values():
            if client_id.lower().strip() in client.client_id.lower().strip():
                search_person.append(client)
        if search_person:
            return search_person
        else:
            raise IDDoesNotExistException

    def search_client_by_name(self, client_name):
        search_person = []
        for client in self._clients.values():
            if client_name.lower().strip() in client.name.lower().strip():
                search_person.append(client)
        if search_person:
            return search_person
        else:
            raise IDDoesNotExistException


class ClientBinaryRepository(ClientRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name
        self.load_clients_from_file()

    def load_clients_from_file(self):
        try:
            if os.path.exists(self.__file_name):
                file = open(self.__file_name, 'rb')
                self._clients = pickle.load(file)
                file.close()
        except EOFError:
            raise FileNotFoundError("File not found")

    def save_clients_to_file(self):
        file = open(self.__file_name, 'wb')
        pickle.dump(self._clients, file)
        file.close()


class ClientTextFileRepository(ClientRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name
        self.load_clients_from_file()

    def load_clients_from_file(self):
        try:
            if os.path.exists(self.__file_name):
                file = open(self.__file_name, 'r')
                lines = file.readlines()
                for line in lines:
                    client_id, client_name = line.strip().split(' , ')
                    self.add_a_client(Client(client_id, client_name))
                file.close()
        except EOFError:
            raise FileNotFoundError("File not found")

    def save_clients_to_file(self):
        file = open(self.__file_name, 'w')
        for client in self.get_all_clients():
            file.write(f"{client.client_id} , {client.name}\n")
        file.close()