from src.repository.repository_exceptions import RepositoryException
from src.services.undo_service import UndoRedoException

class UI:
    def __init__(self, service_client, service_book, service_rental, undo_service):  # , service_rental
        self.__service_client = service_client
        self.__service_book = service_book
        self.__service_rental = service_rental
        self.__undo_service = undo_service

    def add_book(self):
        try:
            book_id = input("Please give the book ID: ")
            title = input("Please give the title of the book: ")
            author = input("Please give the author: ")
            self.__service_book.add_book(book_id, title, author)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def add_client(self):
        try:
            client_id = input("Please give the Client ID: ")
            name = input("Please give the Client's name: ")
            self.__service_client.add_client(client_id, name)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def remove_book(self):
        try:
            book_id = input("Please give the book ID: ")
            self.__service_book.remove_book(book_id)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def remove_client(self):
        try:
            client_id = input("Please give the Client ID: ")
            self.__service_client.remove_client(client_id)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def update_book(self):
        try:
            book_id = input("Please give the book id you want to update: ")
            title = input("Please give the new title of the book: ")
            author = input("Please give the new author of the book: ")
            self.__service_book.update_book(book_id, title, author)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def update_client(self):
        try:
            client_id = input("Please give the client id you want to update: ")
            name = input("Please give the new name of the client: ")
            self.__service_client.update_client(client_id, name)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def display_clients(self):
        clients = self.__service_client.get_clients()
        for client in clients:
            print(client)

    def display_book(self):
        books = self.__service_book.get_books()
        for book in books:
            print(book)

    @staticmethod
    def display_rentals(rentals):
        for rental in rentals:
            print(rental)

    def rent_book(self):
        try:
            book_id = input("Please give the book id: ")
            client_id = input("Please give the client id: ")
            rented_date = input("Please give the rented_date: ")
            self.__service_rental.rent_book(book_id, client_id, rented_date)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def return_book(self):
        try:
            book_id = input("Please give the book id: ")
            returned_date = input("Please give the returnes date: ")
            self.__service_rental.return_book(book_id, returned_date)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def list_clients(self, clients):
        for client in clients:
            print(client)

    def search_client_by_id(self):
        client_id = input("Please give the client id: ")
        try:
            to_be_printed = self.__service_client.search_client_by_id(client_id)
            self.list_clients(to_be_printed)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def search_client_by_name(self):
        client_name = input("Please give the client name: ")
        try:
            to_be_printed = self.__service_client.search_client_by_name(client_name)
            self.list_clients(to_be_printed)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def list_books(self, books):
        for book in books:
            print(book)

    def search_book_by_id(self):
        book_id = input("Please give the book id: ")
        try:
            to_be_printed = self.__service_book.search_book_by_id(book_id)
            self.list_books(to_be_printed)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def search_book_by_title(self):
        book_title = input("Please give the book title: ")
        try:
            to_be_printed = self.__service_book.search_book_by_title(book_title)
            self.list_books(to_be_printed)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def search_book_by_author(self):
        book_author = input("Please give the book author: ")
        try:
            to_be_printed = self.__service_book.search_book_by_author(book_author)
            self.list_books(to_be_printed)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def search_rental_by_rental_id(self):
        rental_id = input("Please give the rental id: ")
        try:
            to_be_printed = self.__service_rental.search_rental_by_id(rental_id)
            self.display_rentals(to_be_printed)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def search_rental_by_book_id(self):
        book_id = input("Please give the book id: ")
        try:
            to_be_printed = self.__service_rental.search_rental_by_book_id(book_id)
            self.display_rentals(to_be_printed)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def search_rental_by_client_id(self):
        client_id = input("Please give the client id: ")
        try:
            to_be_printed = self.__service_rental.search_rental_by_client_id(client_id)
            self.display_rentals(to_be_printed)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def search_rental_by_rented_date(self):
        rented_date = input("Please give the rented date: ")
        try:
            to_be_printed = self.__service_rental.search_rental_by_rented_date(rented_date)
            self.display_rentals(to_be_printed)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def search_rental_by_returned_date(self):
        returned_date = input("Please give the returned date: ")
        try:
            to_be_printed = self.__service_rental.search_rental_by_returned_date(returned_date)
            self.display_rentals(to_be_printed)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def statistic_most_rented_books(self):
        try:
            to_be_printed = self.__service_rental.statistic_most_rented_books()
            self.display_rentals(to_be_printed)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def statistic_most_active_clients(self):
        try:
            to_be_printed = self.__service_rental.statistic_most_active_clients()
            self.display_rentals(to_be_printed)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def statistic_most_rented_authors(self):
        try:
            to_be_printed = self.__service_rental.statistic_most_rented_author()
            self.display_rentals(to_be_printed)
        except RepositoryException as repo_exception:
            print(repo_exception)
        except Exception as exception:
            print(exception)

    def undo_command(self):
        try:
            self.__undo_service.undo()
        except UndoRedoException as exception:
            print(exception)
        except Exception as exception:
            print(exception)

    def redo_command(self):
        try:
            self.__undo_service.redo()
        except UndoRedoException as exception:
            print(exception)
        except Exception as exception:
            print(exception)

    @staticmethod
    def print_initial_menu():
        print("\n1. Manage clients and books.\n"
              "2. Rent or return a book\n"
              "3. Search for clients or books.\n"
              "4. Create statistics.\n"
              "5. Unod/Redo.\n"
              "6. Exit.")

    @staticmethod
    def print_menu_for_managing_clients_and_books():
        print("\n1. Add a client.\n"
              "2. Add a book.\n"
              "3. Remove a client.\n"
              "4. Remove a book.\n"
              "5. Update a client\n"
              "6. Update a book\n"
              "7. Display clients list.\n"
              "8. Display books list.\n"
              "9. Go back to principal menu.\n")

    @staticmethod
    def print_menu_for_rent_or_return_a_book():
        print("\n1. Rent a book.\n"
              "2. Return a book.\n"
              "3. Display rentals.\n"
              "4. Go back to principal menu.\n")

    @staticmethod
    def print_menu_for_searching_clients_or_books():
        print("\n1. Search for a client using its id.\n"
              "2. Search for a client using its name.\n"
              "3. Search for a book using its id.\n"
              "4. Search for a book using its title.\n"
              "5. Search for a book using its author.\n"
              "6. Search for a rental by rental id.\n"
              "7. Search for a rental by book id.\n"
              "8. Search for a rental by client id.\n"
              "9. Search for rental by rented date.\n"
              "10. Search for rental by returned date.\n"
              "11. Go back to principal menu.\n")

    @staticmethod
    def print_menu_for_creating_statistics():
        print("\n1. Most rented books.\n"
              "2. Most active clients.\n"
              "3. Most rented author.\n"
              "4. Go back to principal menu.\n")

    def print_menu_for_undo_redo(self):
        print("\n1. Undo.\n"
              "2. Redo.\n"
              "3. Go back.\n")

    def menu_application(self):
        if len(self.__service_client.get_clients()) == 0:
            self.__service_client.generate_20_clients()
        if len(self.__service_book.get_books()) == 0:
            self.__service_book.generate_20_books()
        # self.__service_rental.generate_20_rentals()
        manage_clients_and_books = '1'
        rent_or_return_book = '2'
        search_for_clients_or_books = '3'
        create_statistics = '4'
        undo_redo = '5'
        exit_ = '6'

        while True:
            self.print_initial_menu()
            option = input("Please choose an option from the list above:")
            if option == manage_clients_and_books:
                while True:
                    self.print_menu_for_managing_clients_and_books()
                    add_client = '1'
                    add_book = '2'
                    remove_client = '3'
                    remove_book = '4'
                    update_client = '5'
                    update_book = '6'
                    display_clients = '7'
                    display_books = '8'
                    go_back = '9'
                    secondary_option = input("Please chose an option from the second list: ")
                    if secondary_option == add_client:
                        self.add_client()
                    elif secondary_option == add_book:
                        self.add_book()
                    elif secondary_option == remove_client:
                        self.remove_client()
                    elif secondary_option == remove_book:
                        self.remove_book()
                    elif secondary_option == update_client:
                        self.update_client()
                    elif secondary_option == update_book:
                        self.update_book()
                    elif secondary_option == display_clients:
                        self.display_clients()
                    elif secondary_option == display_books:
                        self.display_book()
                    elif secondary_option == go_back:
                        break
                    else:
                        print("Invalid input!")

            elif option == rent_or_return_book:
                while True:
                    self.print_menu_for_rent_or_return_a_book()
                    rent_book = '1'
                    return_book = '2'
                    display_rentals = '3'
                    go_back = '4'
                    secondary_option = input("Please chose an option from the second list: ")
                    if secondary_option == rent_book:
                        self.rent_book()
                    elif secondary_option == return_book:
                        self.return_book()
                    elif secondary_option == display_rentals:
                        self.display_rentals(self.__service_rental.get_rentals())
                    elif secondary_option == go_back:
                        break
                    else:
                        print("Invalid input!")

            elif option == search_for_clients_or_books:
                while True:
                    self.print_menu_for_searching_clients_or_books()
                    search_client_id = '1'
                    search_client_name = '2'
                    search_book_id = '3'
                    search_book_title = '4'
                    search_book_author = '5'
                    search_rental_id = '6'
                    search_rental_book_id = '7'
                    search_rental_client_id = '8'
                    search_rented_date = '9'
                    search_returned_date = '10'
                    go_back = '11'
                    secondary_option = input("Please chose an option from the second list: ")
                    if secondary_option == search_client_id:
                        self.search_client_by_id()
                    elif secondary_option == search_client_name:
                        self.search_client_by_name()
                    elif secondary_option == search_book_id:
                        self.search_book_by_id()
                    elif secondary_option == search_book_title:
                        self.search_book_by_title()
                    elif secondary_option == search_book_author:
                        self.search_book_by_author()
                    elif secondary_option == search_rental_id:
                        self.search_rental_by_rental_id()
                    elif secondary_option == search_rental_book_id:
                        self.search_rental_by_book_id()
                    elif secondary_option == search_rental_client_id:
                        self.search_rental_by_client_id()
                    elif secondary_option == search_rented_date:
                        self.search_rental_by_rented_date()
                    elif secondary_option == search_returned_date:
                        self.search_rental_by_returned_date()
                    elif secondary_option == go_back:
                        break
                    else:
                        print("Invalid input!")

            elif option == create_statistics:
                while True:
                    self.print_menu_for_creating_statistics()
                    the_most_rented_books = '1'
                    the_most_active_clients = '2'
                    the_most_rented_author = '3'
                    go_back = '4'
                    secondary_option = input("Please chose an option from the second list: ")
                    if secondary_option == the_most_rented_books:
                        self.statistic_most_rented_books()
                    elif secondary_option == the_most_active_clients:
                        self.statistic_most_active_clients()
                    elif secondary_option == the_most_rented_author:
                        self.statistic_most_rented_authors()
                    elif secondary_option == go_back:
                        break
                    else:
                        print("Invalid input!")
            elif option == undo_redo:
                while True:
                    self.print_menu_for_undo_redo()
                    undo = '1'
                    redo = '2'
                    go_back = '3'
                    secondary_option = input("Please chose an option from the second list: ")
                    if secondary_option == undo:
                        self.undo_command()
                    elif secondary_option == redo:
                        self.redo_command()
                    elif secondary_option == go_back:
                        break
                    else:
                        print("Invalid input!")
            elif option == exit_:
                print("Exiting the program...")
                break

            else:
                print("Invalid input!")
