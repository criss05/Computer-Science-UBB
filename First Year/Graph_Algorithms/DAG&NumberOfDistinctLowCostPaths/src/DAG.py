from collections import defaultdict

class Graph:
    def __init__(self, vertices):
        self.vertices = vertices
        self.graph = defaultdict(list)

    def add_edge(self, u, v, cost):
        self.graph[u].append((v, cost))

    def topological_sort_util(self, v, visited, stack):
        visited[v] = True
        for neighbor, _ in self.graph[v]:
            if not visited[neighbor]:
                self.topological_sort_util(neighbor, visited, stack)
        stack.append(v)

    def topological_sort(self):
        visited = [False] * self.vertices
        stack = []
        for i in range(self.vertices):
            if not visited[i]:
                self.topological_sort_util(i, visited, stack)
        return stack[::-1]

    def count_paths(self, s, t):
        dist = [float('inf')] * self.vertices
        paths = [0] * self.vertices
        dist[s] = 0
        paths[s] = 1

        top_order = self.topological_sort()

        for u in top_order:
            for v, cost in self.graph[u]:
                if dist[u] + cost < dist[v]:
                    dist[v] = dist[u] + cost
                    paths[v] = paths[u]
                elif dist[u] + cost == dist[v]:
                    paths[v] += paths[u]

        return paths[t]


def read_graph_from_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
        vertices = int(lines[0])
        graph = Graph(vertices)
        for line in lines[1:]:
            u, v, cost = map(int, line.split())
            graph.add_edge(u, v, cost)
    return graph


def main():
    file_path = input("PLease give the file name: ")
    graph = read_graph_from_file(file_path)

    top_order = graph.topological_sort()
    if len(top_order) == graph.vertices:  # If it's a DAG
        print("Topological Sorting of Activities:")
        print(top_order)
        s = int(input("Enter source vertex: "))
        t = int(input("Enter target vertex: "))
        distinct_paths = graph.count_paths(s, t)
        print(f"Number of distinct lowest cost paths between {s} and {t}: {distinct_paths}")
    else:
        print("The graph is not a Directed Acyclic Graph.")


if __name__ == "__main__":
    main()
