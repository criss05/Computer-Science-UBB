from src.domain.client import Client
import random


class Service_client:
    def __init__(self, repository, client_validation):
        self.__repository = repository
        self.__client_validation = client_validation

    def add_client(self, client_id, client_name):
        """
        Add client
        :param client_id:
        :param client_name:
        :return:
        """
        client = Client(client_id, client_name)
        self.__client_validation.validate_client(client)
        self.__repository.add_a_client(client)

    def remove_client(self, client_id):
        """
        Remove a client
        :param client_id:
        :return:
        """
        self.__repository.remove_a_client(client_id)

    def update_client(self, client_id, new_client_name):
        """
        Update a client
        :param client_id:
        :param new_client_name:
        :return:
        """
        client = Client(client_id, new_client_name)
        self.__client_validation.validate_client(client)
        self.__repository.update_client(client)

    def search_client_by_id(self, client_id):
        return self.__repository.search_client_by_id(client_id)

    def search_client_by_name(self, client_name):
        return self.__repository.search_client_by_name(client_name)

    def get_clients(self):
        return self.__repository.get_all_clients()

    def generate_20_clients(self):
        client_names = ["Ana", "Briana", "Cristian", "Dragos", "Emilia", "Florin", "Gabriela", "Horia", "Ioana",
                        "Jessica", "Karina", "Lucian", "Maria", "Nicu", "Olivia", "Petru", "Raisa", "Sorana", "Tania",
                        "Victor"]
        for client_id in range(1, 21):
            client_name = client_names[random.randint(0, 19)]
            self.add_client(str(client_id), client_name)
