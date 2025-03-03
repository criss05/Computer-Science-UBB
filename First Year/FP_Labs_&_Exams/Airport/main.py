def create_flight_dictionary(code: str, duration: int, departure_city: str, destination_city: str) -> dict:
    return {"code": code, "duration": duration, "departure_city": departure_city, "destination_city": destination_city}


def get_flight_code(flight: dict):
    return flight["code"]


def get_flight_duration(flight: dict):
    return flight["duration"]


def get_departure_city(flight: dict):
    return flight["departure_city"]


def get_destination_city(flight: dict):
    return flight["destination_city"]


def find_given_code_flight_and_modify_duration(flight_code: str, flight_duration: int, flights: list):
    for i in range(len(flights)):
        if get_flight_code(flights[i]).lower() == flight_code.lower():
            flights[i]["duration"] = flight_duration
    return flights


def find_destination_city_and_change_it_with_new_one(destination_city: str, new_destination_city: str, flights: list):
    for i in range(len(flights)):
        if destination_city.lower() == get_destination_city(flights[i]).lower():
            flights[i]["destination_city"] = new_destination_city
    return flights


def sort_flights_by_their_duration(flights):
    return sorted(flights, key=lambda flight: flight["duration"])


def sort_flights_by_their_duration2(flights):
    for i in range(len(flights)):
        for j in range(len(flights)):
            if get_flight_duration(flights[i]) >= get_flight_duration(flights[j]):
                flights[i], flights[j] = flights[j], flights[i]
    return flights


# UI
def add_a_flight():
    flight_code = input("Please enter the flight code: ").strip()
    departure_city = input("Please enter the departure city: ").strip()
    destination_city = input("Please enter the destination city: ").strip()
    if len(flight_code) < 3 or len(departure_city) < 3 or len(destination_city) < 3:
        raise ValueError("Strings are too short!")
    flight_duration = input("Please enter the duration for the flight: ").strip()
    if not flight_duration.isnumeric():
        raise ValueError("Flight duration is not valid!")
    if int(flight_duration) < 20:
        raise ValueError("Flight duration is too quick!")
    return create_flight_dictionary(flight_code, int(flight_duration), departure_city, destination_city)


def modify_the_duration_of_given_flight(flights):
    flight_code = input("Please enter the flight code: ").strip()
    flight_duration = int(input("Please enter the new duration for the flight: "))
    return find_given_code_flight_and_modify_duration(flight_code, flight_duration, flights)


def update_rerouted_flight_with_given_destination(flights):
    destination_city = input("Please give the destination city: ").strip()
    new_destination_city = input("Please give the new destination city: ").strip()
    if len(destination_city) < 3 or len(new_destination_city) < 3:
        raise ValueError("The strings are too short!!")
    return find_destination_city_and_change_it_with_new_one(destination_city, new_destination_city, flights)


def display_all_flights_with_given_departure_city(flights):
    departure_city = input("Please enter the departure city: ").strip()
    flights_with_given_departure_city = []
    for i in range(len(flights)):
        if get_departure_city(flights[i]) == departure_city:
            flights_with_given_departure_city.append(flights[i])
    sort_flights_by_their_duration(flights_with_given_departure_city)
    print_flights(flights_with_given_departure_city)


def print_flights(flights):
    for flight in flights:
        print(f"\nFlight code: {get_flight_code(flight)}\n"
              f"Flight duration: {get_flight_duration(flight)}\n"
              f"Departure city: {get_departure_city(flight)}\n"
              f"Destination city: {get_destination_city(flight)}\n")


def add_5_flights_at_the_beginning_of_the_program():
    flights = []
    flights.append(create_flight_dictionary('OB3002', 45, 'Vienna', 'London'))
    flights.append(create_flight_dictionary('P9863F', 90, 'Bucuresti', 'Paris'))
    flights.append(create_flight_dictionary('K03F44', 76, 'Vienna', 'New York'))
    flights.append(create_flight_dictionary('J87CCC', 120, 'Alba-Iulia', 'London'))
    flights.append(create_flight_dictionary('NJ2334', 200, 'Vienna', 'Constanta'))
    return flights


def print_menu():
    print("1. Add a flight.\n"
          "2. Modify the duration of a flight.\n"
          "3. Update the rerouted flight with the new destination.\n"
          "4. Show all flights with the given departure city.")


def menu_application():
    flights = add_5_flights_at_the_beginning_of_the_program()
    add_flight = '1'
    modify_flight_duration = '2'
    update_rerouted_flight = '3'
    show_flights_with_given_departure = '4'
    while True:
        option = input("Give the option from the list above: ")
        try:
            if option == add_flight:
                flights.append(add_a_flight())
                print_flights(flights)
            elif option == modify_flight_duration:
                flights = modify_the_duration_of_given_flight(flights)
                print_flights(flights)
            elif option == update_rerouted_flight:
                flights = update_rerouted_flight_with_given_destination(flights)
                print_flights(flights)
            elif option == show_flights_with_given_departure:
                display_all_flights_with_given_departure_city(flights)
            else:
                print("Invalid option!!")
        except ValueError as validation_error:
            print("Error occurred: %s" % validation_error)


print_menu()
menu_application()
