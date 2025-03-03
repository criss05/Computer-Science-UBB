class UI:
    def __init__(self, service):
        self.__service = service

    @staticmethod
    def print_menu():
        print("1. Display buses travalling across a certain route.\n"
              "2. How many kilometers a bus has travelled during its service.\n"
              "3. Display all routes.\n"
              "4. Exit. \n")

    def diplay_buses_across_route(self):
        route_code = input("Please give the route code: ")
        to_print_list = self.__service.find_buses_on_route(route_code)
        self.display_objects(to_print_list)

    def how_many_kilometers_bus_travelled(self):
        bus_id = input("Please give the bus id: ")
        bus, distance = self.__service.kilometers_travelled(bus_id)
        print(f"The bus: {bus} has travelled {distance} kilometers")

    def diplay_routes_and_buses_sorted_descending(self):
        routes = self.__service.sort_routes_by_milage()
        for route in routes:
            buses = self.__service.find_buses_on_route(route.route_code)
            print("\n The route is: ", route, "\n The buses on the routes are:")
            self.display_objects(buses)

    @staticmethod
    def display_objects(to_print_list):
        for object_ in to_print_list:
            print(object_)

    def menu_aplication(self):
        buses = self.__service.get_all_buses()
        self.display_objects(buses)
        while True:
            option = input("Please hoose an option from the list above: ")
            display_buses_on_route = '1'
            number_of_kilometers = '2'
            diplay_routes = '3'
            exit_program = '4'
            if option == display_buses_on_route:
                self.diplay_buses_across_route()
            elif option == number_of_kilometers:
                self.how_many_kilometers_bus_travelled()
            elif option == diplay_routes:
                self.diplay_routes_and_buses_sorted_descending()
            elif option == exit_program:
                print("Exiting...")
                break

