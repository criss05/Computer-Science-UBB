from textdistance import Levenshtein

from src.domain import Assigment


class Service:
    def __init__(self, repository):
        self.__repository = repository

    def get_all_assigments(self):
        return self.__repository.get_all_assigments()

    def add_assigment(self, id_, student_name, solution):
        """
        Add assigment
        :param id_: assigment id
        :param student_name: student name
        :param solution: solution
        :return:
        """
        assigment = Assigment(id_, student_name, solution)
        self.__repository.add_assigment(assigment)

    def dishonesty_check(self):
        assigments = self.get_all_assigments()
        dishonest_students = []
        pertange_list = []
        for i in range(len(assigments)):
            solution1 = assigments[i].solution
            for j in range(len(assigments)):
                solution2 = assigments[j].solution
                maxim_length = max(len(solution1), len(solution2))
                distance = len(solution1) - len(solution2)
                similarity_pertange = max((maxim_length - distance),  maxim_length) * 100
                if similarity_pertange >= 20:
                    dishonest_students.append(tuple((assigments[i].student_name, assigments[j].student_name)))
                    pertange_list.append(similarity_pertange)
        return dishonest_students, pertange_list

