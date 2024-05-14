class UI:
    def __init__(self, service):
        self.__service = service

    def display_objects(self, objects: list):
        for object_ in objects:
            print(object_)

    def display_all_assigments(self):
        assigments = self.__service.get_all_assigments()
        self.display_objects(assigments)

    def add_assigment(self):
        id_ = input("Please give the assigment id: ")
        if not id_.isnumeric():
            raise ValueError("Id must be numeric!")

        student_name = input("Please give the student name: ")
        if len(student_name) < 3:
            raise ValueError("Student name should have at least 3 characters!")

        solution = input("Please give the solution: ")
        if not solution:
            raise ValueError("Solution must not be an empty string!")

        self.__service.add_assigment(id_, student_name, solution)

    def show_dishonest_student(self):
        dishonest_students, pertange_list = self.__service.dishonesty_check()
        for i in range(len(dishonest_students)):
            print(f"{dishonest_students[i]} -> {dishonest_students[i]}({dishonest_students[i]})\n")

    @staticmethod
    def print_menu():
        print("1. Add assigment.\n"
              "2. Display assigments.\n"
              "3. Dishonestly check.\n"
              "4. Exit\n")

    def menu_aplication(self):
        self.print_menu()
        while True:
            try:
                option = input("Choose an opiton: ")
                add_assigment = '1'
                display_assigments = '2'
                dishonestly_check = '3'
                exit_ = '4'
                if option == add_assigment:
                    self.add_assigment()
                elif option == display_assigments:
                    self.display_all_assigments()
                elif option == dishonestly_check:
                    self.show_dishonest_student()
                elif option == exit_:
                    print("Exiting...")
                    break
                else:
                    print("Invalid input!")
            except ValueError as error:
                print(error)
