from collections import deque, defaultdict


def is_dag_and_topological_sort(graph, num_vertices):
    in_degree = [0] * num_vertices
    for u in graph:
        for v in graph[u]:
            in_degree[v] += 1

    queue = deque([u for u in range(num_vertices) if in_degree[u] == 0])
    topo_order = []

    while queue:
        u = queue.popleft()
        topo_order.append(u)

        for v in graph[u]:
            in_degree[v] -= 1
            if in_degree[v] == 0:
                queue.append(v)

    if len(topo_order) == num_vertices:
        return True, topo_order
    else:
        return False, []


def count_paths_dag(graph, topo_order, start, end):
    num_vertices = len(topo_order)
    dp = [0] * num_vertices
    dp[start] = 1

    for u in topo_order:
        if dp[u] != 0:
            for v in graph[u]:
                dp[v] += dp[u]

    return dp[end]


def main():
    input_file = input("Give the file name: ")

    with open(input_file, 'r') as file:
        lines = file.readlines()

    num_vertices, num_edges = map(int, lines[0].strip().split())

    graph = defaultdict(list)
    edge_lines = lines[1:num_edges + 1]

    for line in edge_lines:
        u, v = map(int, line.strip().split())
        graph[u].append(v)

    start_vertex, end_vertex = map(int, lines[num_edges].strip().split())

    is_dag, topo_order = is_dag_and_topological_sort(graph, num_vertices)

    if is_dag:
        print("The graph is a DAG.")
        print("Topological Sorting Order:", topo_order)
        num_paths = count_paths_dag(graph, topo_order, start_vertex, end_vertex)
        print(f"Number of distinct paths from {start_vertex} to {end_vertex}: {num_paths}")
    else:
        print("The graph is not a DAG.")


if __name__ == "__main__":
    main()
