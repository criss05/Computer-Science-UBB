import math
import os

from Graph import Graph


class ActivitiesScheduler:
    def __init__(self):
        """
        This function initializes the ActivitiesScheduler object.
        """
        self.__activities = Graph()
        self.__durations = {}
        self.__prerequisites = {}
        self.__in_degree = {}

    def init_activities(self, activities_number):
        """
        This function initializes the activities. It creates the dictionaries for prerequisites and in_degree for every
         vertex
        :param activities_number: The number of activities.
        """
        for vertex in range(0, activities_number):
            self.__prerequisites[vertex] = []
            self.__in_degree[vertex] = 0

    def init_durations(self, vertex, duration):
        """
        This function initializes the durations of the activities, and it adds the vertex to the graph.
        :param vertex: The vertex of the activity.
        :param duration: The duration of the activity.
        """
        self.__activities.add_vertex(vertex)
        self.__durations[vertex] = duration

    def init_prerequisites(self, vertex, prerequisite):
        """
        This function initializes the prerequisites of the activities. If the prerequisite is '-', then the activity has
         no prerequisites.
        If the activity has prerequisites, then the prerequisites are added to the list of prerequisites of the activity
        :param vertex: The vertex of the activity.
        :param prerequisite: The prerequisites of the activity.
        """
        if prerequisite != '-':
            self.__prerequisites[vertex].append(prerequisite)
        else:
            self.__prerequisites[vertex] = math.inf

    def init_in_degree(self, vertex):
        """
        Each time a vertex is a prerequisite for another vertex, the in_degree of the vertex is incremented.
        :param vertex:
        """
        self.__in_degree[vertex] += 1

    def build_graph(self):
        """
        This function creates the corresponding graph of the DAG.
        The corresponding graph is a directed graph where the vertices are the activities
        and the edges are the prerequisites.
        """
        # Create an empty graph
        self.__activities = Graph()
        # Add the vertices to the graph
        for vertex in range(0, len(self.__durations)):
            self.__activities.add_vertex(vertex)
        # Add the edges to the graph
        for vertex in range(0, len(self.__durations)):
            if self.__prerequisites[vertex] != math.inf:
                for prerequisite in self.__prerequisites[vertex]:
                    self.__activities.add_edge(prerequisite, vertex, 0)

    def topologically_sort(self):
        """
        This function returns a topological sorting of the activities.
        :return: The topological sorted list of the activities
        """
        # Create an empty list for the sorted activities and a queue for the activities with in_degree 0
        sorted_list = []
        queue = []
        # Represents the number of prerequisites for each activity
        count = {}
        # Initialize the count dictionary and add the activities with in_degree 0 to the queue
        for vertex_x in self.__in_degree:
            count[vertex_x] = self.__in_degree[vertex_x]
            if count[vertex_x] == 0:
                queue.append(vertex_x)
        # While the queue is not empty, pop the first element from the queue and add it to the sorted list
        while len(queue) != 0:
            vertex_x = queue.pop()
            sorted_list.append(vertex_x)
            # For each vertex_y that is an out edge of vertex_x, decrement the count of vertex_y
            for vertex_y in self.__activities.parse_vertex_out(vertex_x):
                count[vertex_y] = count[vertex_y] - 1
                # if the count of vertex_y is 0, then add it to the queue
                if count[vertex_y] == 0:
                    queue.append(vertex_y)
        # If the sorted list has fewer elements than the number of activities, then the graph has a cycle
        if len(sorted_list) < len(self.__durations):
            return None
        # Return the sorted list
        return sorted_list

    def earliest_starting_time(self, sorted_list):
        """
        Function that computes the earliest starting time for each activity.
        :param sorted_list: The topological sorted list of the activities.
        :return: The earliest starting time for each activity.
        """
        # Initialize the earliest starting time for each activity with 0
        earliest_start = {vertex: 0 for vertex in self.__durations}
        # For each activity in the sorted list
        for vertex in sorted_list:
            # if the activity has prerequisites
            if self.__prerequisites[vertex] != math.inf:
                # for each prerequisite of the activity
                for prerequisite in self.__prerequisites[vertex]:

                    # compute the earliest starting time of the activity using the formula given
                    earliest_start[vertex] = max(earliest_start[vertex], earliest_start[prerequisite] +
                                                 self.__durations[prerequisite])
        # Return the earliest starting time for each activity
        return earliest_start

    def latest_starting_time(self, sorted_list, total_project_time):
        """
        Function that computes the latest starting time for each activity.
        :param sorted_list: The topological sorted list of the activities.
        :param total_project_time: The total project time.
        :return: The latest starting time for each activity.
        """
        # Initialize the latest starting time for each activity with the total project time minus its duration
        latest_start = {vertex: total_project_time-self.__durations[vertex] for vertex in self.__durations}
        # For each activity in the reversed sorted list
        for vertex in reversed(sorted_list):
            # if the activity has prerequisites
            if self.__prerequisites[vertex] != math.inf:
                # for each prerequisite of the activity
                for prerequisite in self.__prerequisites[vertex]:

                    # compute the latest starting time of the activity using the formula given
                    latest_start[prerequisite] = min(latest_start[prerequisite],
                                                     latest_start[vertex] - self.__durations[prerequisite])
        # Return the latest starting time for each activity
        return latest_start

    def total_project_time(self, earliest_starting):
        """
        Function that computes the total project time.
        :param earliest_starting: The earliest starting time for each activity.
        :return: The total project time.
        """
        # The total project time is the maximum of the earliest starting time plus the duration of the activity
        total_project_time = max(earliest_starting[vertex] + self.__durations[vertex] for vertex in self.__durations)
        # Return the total project time
        return total_project_time

    def find_critical_activities(self, earliest_start, latest_start):
        """
        Function that finds the critical activities.
        :param earliest_start: The earliest starting time for each activity.
        :param latest_start: The latest starting time for each activity.
        :return: The critical activities.
        """
        # Initialize the list of critical activities
        critical_activities = []
        # For each activity
        for vertex in self.__durations:
            # if the earliest starting time is equal to the latest starting time, then the activity is critical
            if earliest_start[vertex] == latest_start[vertex]:
                critical_activities.append(vertex)
        # Return the critical activities
        return critical_activities

    def read_activities_from_file(self, file_name):
        """
        Function that reads the activities from a file.
        :param file_name: The name of the file.
        :print: The activities, their durations, and their prerequisites, writen from the file.
        """
        if os.path.exists(file_name):
            file = open(file_name, 'r')
            # Read the first line from the file and initialize the activities with the number given
            first_line = file.readline()
            self.init_activities(int(first_line))
            lines = file.readlines()
            # For each line from the file, initialize the durations, prerequisites, and in_degree of the activities
            for line in lines:
                activity, duration, prerequisites = line.strip().split(" ")
                self.init_durations(int(activity), int(duration))
                for prerequisite in prerequisites.split(','):
                    if prerequisite == '-':
                        self.init_prerequisites(int(activity), prerequisite)
                    else:
                        self.init_prerequisites(int(activity), int(prerequisite))
                        self.init_in_degree(int(activity))
            # Print the activities, their durations, and their prerequisites
            for vertex in self.__durations.keys():
                print(vertex, self.__durations[vertex], self.__prerequisites[vertex])
            file.close()

def activities_scheduler():
    file_name = input("please give the file name: ")
    activities = ActivitiesScheduler()
    activities.read_activities_from_file(file_name)
    activities.build_graph()

    sorted_list = activities.topologically_sort()

    if sorted_list is None:
        print('The graph is not directed acyclic')
        return
    else:
        print("The graph is directed acyclic. The topological sorted graph is: ")
        print(sorted_list)

    print("\nThe earliest starting time is: ")
    earliest_starting = activities.earliest_starting_time(sorted_list)
    for activity in sorted_list:
        print(f"{activity}: {earliest_starting[activity]}")

    total_time = activities.total_project_time(earliest_starting)

    print("\nThe latest starting time is: ")
    latest_starting = activities.latest_starting_time(sorted_list, total_time)
    for activity in sorted_list:
        print(f"{activity}: {latest_starting[activity]}")

    print(f"The total time of the project is: {total_time}")

    print("\nThe critical activities are: ")
    critical_activities = activities.find_critical_activities(earliest_starting, latest_starting)
    for activity in critical_activities:
        print(activity, end=", ")
    print()


if __name__ == '__main__':
    activities_scheduler()
    