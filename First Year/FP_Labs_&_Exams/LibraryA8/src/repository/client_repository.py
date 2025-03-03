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
        del self._clients[client_id]

    def update_client(self, new_client):
        """
        Update a client
        :param new_client:
        :return:
        """
        if new_client.client_id not in self._clients:
            raise IDDoesNotExistException
        self._clients[new_client.client_id] = new_client

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
