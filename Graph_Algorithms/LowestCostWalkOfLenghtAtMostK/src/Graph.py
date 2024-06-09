import os
import math


class Graph:
    def __init__(self, n=0):
        self.__length = n
        self.__din = {}
        self.__dout = {}
        for i in range(self.__length):
            self.__din[i] = []
            self.__dout[i] = []
        self.__dcost = {}

    def add_vertex(self, vertex):
        """
        Adds a vertex to the graph
        :param vertex: the vertex to be added
        :raises: ValueError if the vertex already exists
        """
        if self.is_vertex(vertex):
            raise ValueError(f"Vertex {vertex} already exists!")
        self.__din[vertex] = []
        self.__dout[vertex] = []
        self.__length += 1

    def is_vertex(self, vertex):
        """
        Checks if a vertex exists in the graph or not
        :param vertex: the vertex to be checked
        :return: true if the vertex exists, false otherwise
        """
        if (vertex in self.__din.keys()) and (vertex in self.__dout.keys()):
            return True
        return False

    def add_edge(self, vertex1, vertex2, cost):
        """
        Adds an edge to the graph
        :param vertex1: the starting vertex
        :param vertex2: the ending vertex
        :param cost: the cost of the edge
        :raises: ValueError if the edge already exists
        """
        if self.is_edge(vertex1, vertex2):
            raise ValueError(f"Edge ({vertex1}, {vertex2}) already exists!")
        self.__din[vertex2].append(vertex1)
        self.__dout[vertex1].append(vertex2)
        self.__dcost[(vertex1, vertex2)] = cost

    def is_edge(self, vertex1, vertex2):
        """
        Checks if an edge exists in the graph or not
        :param vertex1: the starting vertex
        :param vertex2: the ending vertex
        :raises: ValueError if one of the vertices does not exist
        """
        if not self.is_vertex(vertex1):
            raise ValueError(f"Vertex {vertex1} does not exist! Try another one.")
        if not self.is_vertex(vertex2):
            raise ValueError(f"Vertex {vertex2} does not exist! Try another one.")

        if vertex1 in self.__din[vertex2] and vertex2 in self.__dout[vertex1]:
            return True

    def remove_vertex(self, vertex):
        """
        Removes a vertex from the graph
        :param vertex: the vertex to be removed
        :raises: ValueError if the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise ValueError(f"Vertex {vertex} does not exist!")
        for vertex2 in self.parse_vertex_out(vertex):
            self.__din[vertex2].remove(vertex)
            del self.__dcost[(vertex, vertex2)]
        for vertex1 in self.parse_vertex_in(vertex):
            self.__dout[vertex1].remove(vertex)
            del self.__dcost[(vertex1, vertex)]
        del self.__din[vertex]
        del self.__dout[vertex]
        self.__length -= 1

    def remove_edge(self, vertex1, vertex2):
        """
        Removes an edge from the graph
        :param vertex1: the starting vertex
        :param vertex2: the ending vertex
        :raises: ValueError if the edge does not exist
        """
        if not self.is_edge(vertex1, vertex2):
            raise ValueError(f"Edge ({vertex1}, {vertex2}) does not exist!")
        self.__din[vertex2].remove(vertex1)
        self.__dout[vertex1].remove(vertex2)
        del self.__dcost[(vertex1, vertex2)]

    @property
    def number_vertices(self):
        """
        Getter for the number of vertices
        :return: the number of vertices of the graph
        """
        return self.__length

    @number_vertices.setter
    def number_vertices(self, value):
        """
        Setter for the number of vertices
        :param value: the new number of vertices
        """
        self.__length = value

    @property
    def number_edges(self):
        """
        Getter for the number of edges
        :return: the number of edges of the graph
        """
        return len(self.__dcost)

    def get_cost(self, vertex1, vertex2):
        """
        Getter for the cost of an edge
        :param vertex1: the starting vertex
        :param vertex2: the ending vertex
        :return: the cost of the edge
        :raises: ValueError if the edge does not exist
        """
        if not self.is_edge(vertex1, vertex2):
            raise ValueError(f"The edge ({vertex1}, {vertex2}) does not exist!")
        return self.__dcost[(vertex1, vertex2)]

    def modify_cost(self, vertex1, vertex2, new_cost):
        """
        Modifies the cost of an edge
        :param vertex1: the starting vertex
        :param vertex2: the ending vertex
        :param new_cost: the new cost of the edge
        :raises: ValueError if the edge does not exist
        """
        if not self.is_edge(vertex1, vertex2):
            raise ValueError(f"The edge ({vertex1}, {vertex2}) does not exist!")
        self.__dcost[(vertex1, vertex2)] = new_cost

    def parse_vertices(self):
        """
        Parses the vertices of the graph
        :return: the list of vertices
        """
        return list(self.__din.keys())

    def parse_vertex_in(self, vertex):
        """
        Parses the inbound vertices of a vertex
        :param vertex: the vertex to be parsed
        :return: the list of inbound vertices
        :raises: ValueError if the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise ValueError("Vertex does not exist!")
        return list(self.__din[vertex])

    def parse_vertex_out(self, vertex):
        """
        Parses the outbound vertices of a vertex
        :param vertex: the vertex to be parsed
        :return: the list of outbound vertices
        :raises: ValueError if the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise ValueError("Vertex does not exist!")
        return list(self.__dout[vertex])

    def in_degree(self, vertex):
        """
        Computes the in degree of a vertex
        :param vertex: the vertex for whom the in degree is computed
        :return: the in degree of the vertex
        :raises: ValueError if the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise ValueError("Vertex does not exist!")
        return len(self.__din[vertex])

    def out_degree(self, vertex):
        """
        Computes the out degree of a vertex
        :param vertex: the vertex for whom the out degree is computed
        :return: the out degree of the vertex
        :raises: ValueError if the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise ValueError("Vertex does not exist!")
        return len(self.__dout[vertex])

    def parse_outbound_edges(self, vertex1):
        """
        Parses the outbound edges of a vertex
        :param vertex1: the vertex for which the outbound edges are parsed
        :return: the list of outbound edges
        :raises: ValueError if the vertex does not exist
        """
        edges = []
        if not self.is_vertex(vertex1):
            raise ValueError("Vertex does not exist!")
        for vertex2 in self.parse_vertex_out(vertex1):
            edges.append((vertex1, vertex2))
        return list(edges)

    def parse_inbound_edges(self, vertex2):
        """
        Parses the inbound edges of a vertex
        :param vertex2: the vertex for which the inbound edges are parsed
        :return: the list of inbound edges
        :raises: ValueError if the vertex does not exist
        """
        edges = []
        if not self.is_vertex(vertex2):
            raise ValueError("Vertex does not exist!")
        for vertex1 in self.parse_vertex_in(vertex2):
            edges.append((vertex1, vertex2))
        return list(edges)

    def parse_edges(self):
        """
        Parses the edges of the graph
        :return: the list of edges
        """
        return self.__dcost.items()

    def load_graph_from_file(self, file_name):
        """
        Loads a graph from a file
        :param file_name: the name of the file
        :raises: FileNotFoundError if the file does not exist
        """
        if os.path.exists(file_name):
            file = open(file_name, 'r')
            # Read the first line
            first_line = file.readline().split()
            # if the length of the first line is 2, then the graph needs to be read in a way
            if len(first_line) == 2:
                # saving the vertices and edges
                lines = file.readlines()
                for line in lines:
                    vertex1, vertex2, cost = line.strip().split()
                    if not self.is_vertex(int(vertex1)):
                        self.add_vertex(int(vertex1))
                    if not self.is_vertex(int(vertex2)):
                        self.add_vertex(int(vertex2))
                    self.add_edge(int(vertex1), int(vertex2), int(cost))
                for vertex in range(int(first_line[0])):
                    if vertex not in self.parse_vertices():
                        self.add_vertex(vertex)
            # if the length of the first line is 3, then the graph needs to be read in a different way
            elif len(first_line) == 3:
                # saving the first line
                vertex1, vertex2, cost = first_line
                if int(vertex2) == -1:
                    self.add_vertex(int(vertex1))
                else:
                    if not self.is_vertex(int(vertex1)):
                        self.add_vertex(int(vertex1))
                    if not self.is_vertex(int(vertex2)):
                        self.add_vertex(int(vertex2))
                    self.add_edge(int(vertex1), int(vertex2), int(cost))
                lines = file.readlines()
                # taking all the lines
                for line in lines:
                    vertex1, vertex2, cost = line.strip().split()
                    # if the second vertex is -1, then the first vertex is isolated
                    if int(vertex2) == -1:
                        self.add_vertex(int(vertex1))
                    # else we add the vertices and the edge
                    else:
                        if not self.is_vertex(int(vertex1)):
                            self.add_vertex(int(vertex1))
                        if not self.is_vertex(int(vertex2)):
                            self.add_vertex(int(vertex2))
                        self.add_edge(int(vertex1), int(vertex2), int(cost))
            file.close()

    def save_graph_to_file(self, file_name):
        """
        Saves the graph to a file
        :param file_name: the name of the file
        """
        file = open(file_name, 'w')
        found = False
        for vertex1 in self.__dout.keys():
            # if the vertex is isolated, then we write the end vertex and the cost as -1
            if len(self.__dout[vertex1]) == 0 and len(self.__din[vertex1]) == 0:
                found = True
        if found:
            for vertex1 in self.__dout.keys():
                # if the vertex is isolated, then we write the end vertex and the cost as -1
                if len(self.__dout[vertex1]) == 0 and len(self.__din[vertex1]) == 0:
                    file.write(f"{vertex1} {-1} {-1}\n")
                else:
                    # if is not isolated, then we write the edge and the cost
                    for vertex2 in self.__dout[vertex1]:
                        cost = self.__dcost[(vertex1, vertex2)]
                        file.write(f"{vertex1} {vertex2} {cost}\n")
        else:
            file.write(f"{self.__length} {self.number_edges}\n")
            for edge, cost in self.parse_edges():
                vertex1, vertex2 = edge
                file.write(f"{vertex1} {vertex2} {cost}\n")
        file.close()

    def find_min_cost_path(self, start, destination):
        """
        Finds the lowest cost walk from start to destination in the given graph.
        :param graph: The Graph object.
        :param start: The starting vertex.
        :param destination: The destination vertex.
        :return: The cost of the lowest cost walk or a message if there's a negative cycle.
        """
        # Initialize distances
        d  = {vertex: float('inf') for vertex in self.parse_vertices()}
        prev = {vertex: None for vertex in self.parse_vertices()}
        d[start] = 0

        # Relax edges repeatedly
        for length in range(self.number_vertices - 1):
            for (vertex1, vertex2), cost in self.parse_edges():
                if d[vertex1] + cost < d[vertex2]:
                    d[vertex2] = d[vertex1] + cost
                    prev[vertex2] = vertex1

        # Check for negative weight cycles
        for (vertex1, vertex2), cost in self.parse_edges():
            if d[vertex1] + cost < d[vertex2]:
                raise ValueError( "There are negative cost cycles.")

        # Reconstruct the path
        if d[destination] == float('inf'):
            raise ValueError( "No path exists between the given vertices.")
        else:
            path = []
            current_vertex = destination
            while current_vertex is not None:
                path.insert(0, current_vertex)
                current_vertex = prev[current_vertex]

            return d[destination], path
