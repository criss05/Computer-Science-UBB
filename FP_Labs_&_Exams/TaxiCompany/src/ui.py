class UI:
    def __init__(self, service):
        self.__service = service

    @staticmethod
    def diaplay_taxis(taxis):
        for taxi in taxis:
            print(taxi)

    @staticmethod
    def is_integer(number: str):
        if not number.isnumeric():
            raise ValueError("The input must be numeric!")
        return int(number)

    @staticmethod
    def number_between_not100_100(number: int):
        if number < -100 or number > 100:
            raise ValueError("Invalid input!")

    @staticmethod
    def number_is_positive(number: int):
        if number < 0:
            raise ValueError("Invalid input!")

    @staticmethod
    def at_least_3_charcters(string: str):
        if len(string) < 3:
            raise ValueError("Invalid input!")

    def add_taxi(self):
        taxi_id = input("Please give the taxi id: ")
        name = input("Please give the name: ")
        number = input("Please give the taxi number: ")
        x = input("x: ")
        y = input("y: ")
        try:
            taxi_id = self.is_integer(taxi_id)
            self.number_is_positive(taxi_id)
            self.at_least_3_charcters(name)
            number = self.is_integer(number)
            self.number_is_positive(number)
            self.number_between_not100_100(number)
            x = self.is_integer(x)
            self.number_between_not100_100(x)
            y = self.is_integer(y)
            self.number_between_not100_100(y)
            self.__service.add_taxi(taxi_id, name, number, x, y)
        except ValueError as error:
            print(error)

    def find_all_taxis_having_distance_at_most_d_to_position_given(self):
        distance = input(" distace: ")
        x = input("x: ")
        y = input("y: ")
        try:
            distance = self.is_integer(distance)
            x = self.is_integer(x)
            self.number_between_not100_100(x)
            y = self.is_integer(y)
            self.number_between_not100_100(y)
            taxis_found = self.__service.find_taxis_having_given_distance_from_given_position(distance, x, y)
            self.diaplay_taxis(taxis_found)
        except ValueError as error:
            print(error)

    def find_minimum_address(self):
        min_x, min_y = self.__service.find_min_distance()
        print(min_x, " ", min_y)

    @staticmethod
    def print_menu():
        print("1. Add adress.\n"
              "2. Display adress.\n"
              "3. Where to put station.\n"
              "4. Determine the minim position.\n"
              "5. Exit.\n")

    def menu_aplication(self):
        while True:
            option = input("Choose an option: ")
            add = '1'
            display = '2'
            station = '3'
            minim = '4'
            exit_ = '5'
            if option == add:
                self.add_taxi()
            elif option == display:
                self.diaplay_taxis(self.__service.get_all_taxis())
            elif option == station:
                self.find_all_taxis_having_distance_at_most_d_to_position_given()
            elif option == minim:
                self.find_minimum_address()
            elif option == exit_:
                print("Exiting...")
                break
            else:
                print("Invalid input!")
