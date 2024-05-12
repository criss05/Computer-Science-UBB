class UI:
    def __init__(self, services):
        self.__services = services

    def add_expense(self):
        day = input("Please enter the day: ")
        amount_of_money = input("Please enter the amount: ")
        type_expenses = input("Please enter the type: ")
        self.__services.add_expense(day, amount_of_money, type_expenses)

    def display_expenses(self):
        expenses = self.__services.get_all_expenses()
        for expense in expenses:
            print(expense)

    def filter_expenses(self):
        given_amount = input("Please give the amount to filter: ")
        self.__services.filter_expense_by_given_value(given_amount)

    def undo(self):
        self.__services.undo()

    @staticmethod
    def print_menu():
        print("1. Add an expense.\n"
              "2. Display the list of expenses.\n"
              "3. Filter the list of expenses so that contains only expenses above a given amount.\n"
              "4. Undo the last operation.\n"
              "5. Exit.\n")

    def menu_application(self):
        if self.__services.is_empty():
            self.__services.generate_10_expenses_for_beginning()
        add_expense = '1'
        display_expenses = '2'
        filter_expenses = '3'
        undo_operation = '4'
        exit_ = '5'
        self.print_menu()
        while True:
            try:
                option = input("Please chose an option: ")
                if option == add_expense:
                    self.add_expense()
                elif option == display_expenses:
                    self.display_expenses()
                elif option == filter_expenses:
                    self.filter_expenses()
                elif option == undo_operation:
                    self.undo()
                elif option == exit_:
                    print("Exiting the program...")
                    break
                else:
                    print("Invalid input!")
            except ValueError as error:
                print('\nError occurred: ', error, '\n')
