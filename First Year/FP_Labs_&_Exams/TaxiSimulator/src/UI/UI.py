class UI:
    def __init__(self, taxi_service):
        self._service = taxi_service

    def add_ride(self):
        start_point = input("Please enter the start point: ")
        end_point = input("Please enter the end point: ")
        start_point = start_point[1:-1]
        start_x, start_y = start_point.split(", ")
        end_point = end_point[1:-1]
        end_x, end_y = end_point.split(", ")
        self._service.add_ride((int(start_x), int(start_y)), (int(end_x), int(end_y)))

    def display_all_taxis(self):
        taxis = self._service.sort_taxis_by_total_fare()
        for taxi in taxis:
            print(taxi)

    def simulate_ride(self):
        self._service.simulate_ride()

    @staticmethod
    def print_menu():
        print("1. Add a ride.\n"
              "2. Simulate a ride.\n"
              "3. Exit.\n")

    def menu_aplication(self):
        number_of_taxis = int(input("Please give the number of taxis: "))
        self._service.generate_random_taxis(number_of_taxis)
        self.display_all_taxis()
        while True:
            option = input("Please choose an option from the list above: ")
            add_ride = '1'
            simulate_ride = '2'
            exit_program = '3'
            if option == add_ride:
                self.add_ride()
                self.display_all_taxis()
            elif option == simulate_ride:
                self.simulate_ride()
                self.display_all_taxis()
            elif option == exit_program:
                print("Exiting...")
                break
            else:
                print("Invalid option!")
