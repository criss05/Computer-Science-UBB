import os.path

from src.domain import Assigment


class Repository:
    def __init__(self):
        self.__assigments = {}

    def add_assigment(self, assigment):
        if assigment.id_ in self.__assigments:
            raise ValueError("The assigment id already exists!")
        self.__assigments[assigment.id_] = assigment

    def get_all_assigments(self):
        return list(self.__assigments.values())

    def get_solution_by_assigment_id(self, id_):
        return self.__assigments[id_].solution


class FileRepository(Repository):
    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name
        self.load_assigments_from_file()

    def add_assigment(self, assigment):
        """
        Add assigment
        :param assigment: assigement
        :return:
        """
        super().add_assigment(assigment)
        self.save_assigments_from_file()

    def load_assigments_from_file(self):
        if os.path.exists(self.__file_name):
            file_repo = open(self.__file_name, 'r')
            lines = file_repo.readlines()
            for line in lines:
                id_, student_name, solution = line.strip().split(', ')
                assigment = Assigment(id_, student_name, solution)
                self.add_assigment(assigment)
            file_repo.close()

    def save_assigments_from_file(self):
        file_repo = open(self.__file_name, 'w')
        for assigment in self.get_all_assigments():
            file_repo.write(f"{assigment.id_}, {assigment.student_name}, {assigment.solution}\n")
        file_repo.close()
