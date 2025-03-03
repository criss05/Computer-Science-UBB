class Client:
    def __init__(self, client_id, name):
        self._client_id = client_id
        self._name = name

    @property
    def client_id(self):
        return self._client_id

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, new_name):
        self._name = new_name
        
    def __eq__(self, client):
        if not isinstance(client, Client):
            return False
        return self.client_id == client.client_id

    def __str__(self):
        return f"client ID: {self.client_id} | Name: {self.name}"
