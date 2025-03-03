from Graph_Algorithms.CoveringOfEdgesByVertices.src_GenericAlgorithm.Graph import Graph, GeneticAlgorithmForVertexCover
import random


class UI:
    def __init__(self):
        self.__graph = Graph()
        self.__copy_graph = Graph()

    @staticmethod
    def print_menu():
        print("0. Read the graph from file\n"
              "1. Random Graph.\n"
              "2. Get the number of vertices.\n"
              "3. Display the set of vertices.\n"
              "4. Find if there is an edge from a vertex to another.\n"
              "5. Get the in degree for a vertex.\n"
              "6. Get the out degree for a vertex.\n"
              "7. Display the outbound edges of a vertex.\n"
              "8. Display the inbound edges of a vertex.\n"
              "9. Retrieve the cost of an edge.\n"
              "10. Modify the cost of an edge.\n"
              "11. Add edge to graph.\n"
              "12. Remove edge from graph.\n"
              "13. Add vertex to graph.\n"
              "14. Remove vertex from graph.\n"
              "15. Copy Graph.\n"
              "16. Print copy Graph.\n"
              "17. Print the whole graph.\n"
              "18. Print edges.\n"
              "19. Save Graph to file.\n"
              "21. Edge cover.\n"
              "22. Exit.\n")

    def start(self):
        while True:
            try:
                self.print_menu()
                option = input("Please choose an option: ")
                if option == '0':
                    self.read_from_file()
                elif option == '1':
                    self.random_graph()
                elif option == '2':
                    self.num_of_vertices()
                elif option == '3':
                    self.print_vertices()
                elif option == '4':
                    self.find_if_edge()
                elif option == '5':
                    self.in_degree()
                elif option == '6':
                    self.out_degree()
                elif option == '7':
                    self.print_outbounds()
                elif option == '8':
                    self.print_inbounds()
                elif option == '9':
                    self.give_cost()
                elif option == "10":
                    self.modify_cost()
                elif option == '11':
                    self.add_edge()
                elif option == '12':
                    self.remove_edge()
                elif option == '13':
                    self.add_vertex()
                elif option == '14':
                    self.remove_vertex()
                elif option == '15':
                    self.copy_the_graph()
                elif option == '16':
                    self.print_graph(self.__copy_graph)
                elif option == '17':
                    self.print_graph(self.__graph)
                elif option == '18':
                    self.print_edges()
                elif option == '19':
                    self.save_to_file()
                elif option == '21':
                    self.cover_edges()
                elif option == '22':
                    print("Exiting...")
                    break
                else:
                    print("Invalid input!")
            except ValueError as error:
                print(error)

    def cover_edges(self):
        ga = GeneticAlgorithmForVertexCover(self.__graph)
        cover_generic = ga.run()
        print("Generic: ", cover_generic)

    @staticmethod
    def print_graph(graph):
        print("Outbound: ")
        for vertex1 in graph.parse_vertices():
            print(f"{vertex1}: ", end=" ")
            for vertex2 in graph.parse_vertex_out(vertex1):
                print(f"{vertex2}", end=' ')
            print()
        print("Inbound: ")
        for vertex1 in graph.parse_vertices():
            print(f"{vertex1}: ", end=" ")
            for vertex2 in graph.parse_vertex_in(vertex1):
                print(f"{vertex2}", end=' ')
            print()

    def add_vertex(self):
        vertex = input("Give a vertex: ")
        if not vertex.isnumeric():
            raise ValueError(f"Vertex is not numeric!")

        self.__graph.add_vertex(int(vertex))

    def add_edge(self):
        vertex1 = input("Give the first vertex: ")
        if not vertex1.isnumeric():
            raise ValueError(f"Vertex is not numeric!")

        vertex2 = input("Give the second vertex: ")
        if not vertex2.isnumeric():
            raise ValueError(f"Vertex is not numeric!")

        cost = input("Give the cost: ")
        if not cost.isnumeric():
            raise ValueError(f"Cost is not numeric!")

        self.__graph.add_edge(int(vertex1), int(vertex2), int(cost))

    def remove_vertex(self):
        vertex = input("Give the vertex: ")
        if not vertex.isnumeric():
            raise ValueError(f"Vertex is not numeric!")

        self.__graph.remove_vertex(int(vertex))

    def remove_edge(self):
        vertex1 = input("Give the first vertex: ")
        if not vertex1.isnumeric():
            raise ValueError(f"Vertex is not numeric!")

        vertex2 = input("Give the second vertex: ")
        if not vertex2.isnumeric():
            raise ValueError(f"Vertex is not numeric!")

        self.__graph.remove_edge(int(vertex1), int(vertex2))

    def num_of_vertices(self):
        print("Number of vertices is: ", self.__graph.number_vertices)

    def out_degree(self):
        vertex = input("Please give the vertex: ")
        if not vertex.isnumeric():
            raise ValueError(f"Vertex is not numeric!")

        print(f"The out degree of {vertex} is: ", self.__graph.out_degree(int(vertex)))

    def modify_cost(self):
        vertex1 = input("Please give the first vertex: ")
        if not vertex1.isnumeric():
            raise ValueError(f"Vertex is not numeric!")

        vertex2 = input("Please give the second vertex: ")
        if not vertex2.isnumeric():
            raise ValueError(f"Vertex is not numeric!")

        cost = input("Please give the cost: ")
        if not cost.isnumeric():
            raise ValueError(f"Cost is not numeric!")

        self.__graph.modify_cost(int(vertex1), int(vertex2), int(cost))

    def find_if_edge(self):
        vertex1 = input("Please give the first vertex: ")
        if not vertex1.isnumeric():
            raise ValueError(f"Vertex is not numeric!")

        vertex2 = input("Please give the second vertex: ")
        if not vertex2.isnumeric():
            raise ValueError(f"Vertex is not numeric!")

        if self.__graph.is_edge(int(vertex1), int(vertex2)):
            print(f"There exist an edge from {vertex1} to {vertex2}")
        else:
            print(f"There is no an edge from {vertex1} to {vertex2}")

    def in_degree(self):
        vertex = input("Please give the vertex: ")
        if not vertex.isnumeric():
            raise ValueError(f"Vertex is not numeric!")

        print(f"The in degree of {int(vertex)} is: ", self.__graph.in_degree(int(vertex)))

    def give_cost(self):
        vertex1 = input("Please give the first vertex: ")
        if not vertex1.isnumeric():
            raise ValueError(f"Vertex is not numeric!")

        vertex2 = input("Please give the second vertex: ")
        if not vertex2.isnumeric():
            raise ValueError(f"Vertex is not numeric!")

        print(f"The cost of the edge ({vertex1}, {vertex2}) is {self.__graph.get_cost(int(vertex1), int(vertex2))}")

    def print_edges(self):
        for edge, cost in self.__graph.parse_edges():
            vertex1, vertex2 = edge
            print(f"({vertex1}, {vertex2}) : {cost}")

    def print_outbounds(self):
        vertex = input("Please give the vertex: ")
        if not vertex.isnumeric():
            raise ValueError(f"Vertex is not numeric!")

        for vertex1 in self.__graph.parse_vertex_out(int(vertex)):
            print(f"({vertex}, {vertex1})\n")
        print()

    def print_inbounds(self):
        vertex = input("Please give the vertex: ")
        if not vertex.isnumeric():
            raise ValueError(f"Vertex is not numeric!")

        for vertex1 in self.__graph.parse_vertex_in(int(vertex)):
            print(f"({vertex1}, {vertex})\n")
        print()

    def print_vertices(self):
        print("Vertices are: ")
        for vertex in self.__graph.parse_vertices():
            print(vertex, end=' ')
        print()

    def random_graph(self):
        n = input("Please give the number of vertices: ")
        if not n.isnumeric:
            raise ValueError("Number of vertices must be numeric!")
        n = int(n)

        m = input("Please give the number of edges: ")
        if not m.isnumeric:
            raise ValueError("Number of edges must be numeric!")
        m = int(m)

        graph = Graph(n)

        if m > n*(n-1)+n:
            m = n*(n-1)+n
            print("Cannot create a graph like this. Number of vertices is: ", m)
        while m:
            vertex1 = random.randint(0, (n - 1))
            vertex2 = random.randint(0, (n - 1))
            vertex_cost = random.randint(1, 200)
            if not graph.is_edge(vertex1, vertex2):
                graph.add_edge(vertex1, vertex2, vertex_cost)
                m -= 1
        self.__graph = graph

    def read_from_file(self):
        self.__graph = Graph()
        file_name = input("Give the file name: ")
        self.__graph.load_graph_from_file(file_name)

    def save_to_file(self):
        file_name = input("Give the file name: ")
        self.__graph.save_graph_to_file(file_name)

    def copy_the_graph(self):
        for vertex in self.__graph.parse_vertices():
            self.__copy_graph.add_vertex(vertex)
        for edge, cost in self.__graph.parse_edges():
            vertex1, vertex2 = edge
            self.__copy_graph.add_edge(vertex1, vertex2, cost)
        print("Graph was copied!")


ui = UI()
ui.start()
