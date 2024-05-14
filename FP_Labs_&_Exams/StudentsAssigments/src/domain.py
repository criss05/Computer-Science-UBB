class Assigment:
    def __init__(self, id_, student_name, solution):
        self.__id = id_
        self.__student_name = student_name
        self.__solution = solution

    @property
    def id_(self):
        return self.__id

    @property
    def student_name(self):
        return self.__student_name

    @property
    def solution(self):
        return self.__solution

    def __str__(self):
        return f"{self.id_}, {self.__student_name}, {self.solution}"

