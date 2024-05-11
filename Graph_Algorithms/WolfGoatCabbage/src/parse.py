from wolf_goat_cabbage import Vertex, WolfGoatCabbageGraph


class TreeNode:
    def __str__(self):
        return f"parent: {self.parent}, level: {self.level}, children: {self.children}"

    def __repr__(self):
        return f"parent: {self.parent}, level: {self.level}, children: {self.children}"


def bfs(g, s):
    """
    Breadth-first search using a tree node class having parent, level and children as attributes
    :param g: the graph to be searched
    :param s: the starting vertex
    :return: the tree resulted from the search
    """
    # Declare the tree, queue and the head of the queue such that the head is the first element of the queue,
    # the first element of the queue is the starting vertex and the tree has the starting vertex as root
    tree = {}
    queue = [s]
    tree[s] = TreeNode()
    tree[s].parent = None
    tree[s].level = 0
    tree[s].children = []
    head = 0
    # While the head is less than the length of the queue, take the first element of the queue and parse its neighbors
    while head < len(queue):
        # For every neighbor of the current vertex, if the neighbor is not in the tree, add it to the queue
        x = queue[head]
        # Increment the head
        head += 1
        # For every neighbor of the current vertex, if the neighbor is not in the tree, add it to the queue
        for y in g.parse_neighbors(x):
            if y not in tree.keys():
                queue.append(y)
                tree[y] = TreeNode()
                tree[y].parent = x
                tree[y].level = tree[x].level + 1
                tree[y].children = []
                tree[x].children.append(y)
    # Return the tree
    return tree


def shortest_path(g, s, t):
    """
    Find the shortest path between two vertices using BFS
    :param g: the graph to be searched
    :param s: the starting vertex
    :param t: the target vertex
    :return: the shortest path between the two vertices
    """
    # Get the tree resulted from the search
    tree = bfs(g, s)
    start = s
    target = t
    # If the target is not in the tree, return None
    if target not in tree.keys():
        return None
    # Else, reconstruct the path from the target to the start
    path_rev = list()
    while target != start:
        path_rev.append(target)
        target = tree[target].parent
    # Add the start in the path and reverse it
    path_rev.append(start)
    path_rev.reverse()
    # Return the path
    return path_rev


def print_solution(path_printed):
    """
    Print the solution in a nice way
    :param path_printed: the path to be printed
    """
    if path_printed:
        print("Solution found!")
        for i, state in enumerate(path_printed):
            print(f"Step {i}: ")
            print(f"Left side: {'wolf ' if not state.get_dict()["wolf"] else ''}"
                  f"{'goat ' if not state.get_dict()["goat"] else ''}"
                  f" {'cabbage ' if not state.get_dict()['cabbage'] else ''}"
                  f"{'boat' if not state.get_dict()['boat'] else ''}\n",
                  end='')

            print(f"Right side: {'wolf ' if state.get_dict()["wolf"] else ''}"
                  f"{'goat ' if state.get_dict()["goat"]else ''}"
                  f"{'cabbage ' if state.get_dict()['cabbage'] else ''}"
                  f"{'boat' if state.get_dict()['boat'] else ''}\n",
                  end='')

            print()
    else:
        (print
         ("No solution found"))


if __name__ == "__main__":
    graph = WolfGoatCabbageGraph()
    init_state = Vertex({"wolf": False, "goat": False, "cabbage": False, "boat": False, })
    final_state = Vertex({"wolf": True, "goat": True, "cabbage": True, "boat": True, })
    path = shortest_path(graph, init_state, final_state)
    print_solution(path)
