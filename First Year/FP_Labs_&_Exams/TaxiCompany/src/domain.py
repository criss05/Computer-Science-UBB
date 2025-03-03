class TaxiDomain:
    def __init__(self, taxi_id, name, number, x, y):
        self.__taxi_id = taxi_id
        self.__name = name
        self.__number = number
        self.__x = x
        self.__y = y

    @property
    def taxi_id(self):
        return self.__taxi_id

    @property
    def name(self):
        return self.__name

    @property
    def number(self):
        return self.__number

    @property
    def x(self):
        return self.__x

    @property
    def y(self):
        return self.__y

    def __str__(self):
        return f"{self.taxi_id}, {self.name}, {self.number}, {self.x}, {self.y}\n"
