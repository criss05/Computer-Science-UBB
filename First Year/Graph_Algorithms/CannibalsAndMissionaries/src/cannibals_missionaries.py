class CannibalsMissionaries:
    def __init__(self, boat, cannibal_left, missionaries_left, cannibal_right, missionaries_right):
        """
        Constructor for the CannibalsMissionaries class.
        :param boat: The side of the river the boat is on.
        :param cannibal_left: The number of cannibals on the left side of the river.
        :param missionaries_left: The number of missionaries on the left side of the river.
        :param cannibal_right: The number of cannibals on the right side of the river.
        :param missionaries_right: The number of missionaries on the right side of the river.
        """
        self.cannibalLeft = cannibal_left
        self.cannibalRight = cannibal_right
        self.missionariesLeft = missionaries_left
        self.missionariesRight = missionaries_right
        self.boat = boat
        self.prev = None

    def goal(self):
        """
        Check if the goal state has been reached. The goal state is when all the cannibals and missionaries are on the
        right side of the river.
        """
        if self.missionariesLeft == 0 and self.cannibalLeft == 0 and self.boat == "right":
            return True
        return False

    def is_valid(self):
        """
        Check if the current state is valid. The state is valid if the number of cannibals is smaller than or equal
        to the number of missionaries on each side of the river.
        :return: true if the state is valid, false otherwise.
        """
        if (self.missionariesLeft >= 0 and self.missionariesRight >= 0 and self.cannibalLeft >= 0 and
                self.cannibalRight >= 0 and
                (self.missionariesLeft == 0 or self.missionariesLeft >= self.cannibalLeft) and
                (self.missionariesRight == 0 or self.missionariesRight >= self.cannibalRight)):
            return True
        return False

    def __eq__(self, other):
        """
        Check if two states are equal. Two states are equal if the number of cannibals and missionaries on each side of
        the bank is the same.
        :return: true if the states are equal, false otherwise.
        """
        if (self.cannibalRight == other.cannibalRight and self.missionariesRight == other.missionariesRight
                and self.boat == other.boat and self.cannibalLeft == other.cannibalLeft and
                self.missionariesLeft == other.missionariesLeft):
            return True
        return False

    def __hash__(self):
        return hash((self.cannibalLeft, self.missionariesLeft, self.boat, self.cannibalRight,
                     self.missionariesRight))


def next_move(current_move):
    """
    Generate the next possible moves from the current state.
    :param current_move: the current state.
    :return: the next possible moves from the current state.
    """
    next_mv = []
    # If the boat is on the left side of the river we have 5 options for moving the other elements.
    if current_move.boat == 'left':
        # Move two missionaries from left to right.
        new_move = CannibalsMissionaries('right',current_move.cannibalLeft, current_move.missionariesLeft - 2,
                                          current_move.cannibalRight, current_move.missionariesRight + 2)
        if new_move.is_valid():
            new_move.prev = current_move
            next_mv.append(new_move)

        # Move two cannibals from left to right.
        new_move = CannibalsMissionaries('right',current_move.cannibalLeft - 2, current_move.missionariesLeft,
                                          current_move.cannibalRight + 2, current_move.missionariesRight)
        if new_move.is_valid():
            new_move.prev = current_move
            next_mv.append(new_move)

        # Move one missionary and one cannibal from left to right.
        new_move = CannibalsMissionaries('right',current_move.cannibalLeft - 1, current_move.missionariesLeft - 1,
                                          current_move.cannibalRight + 1, current_move.missionariesRight + 1)
        if new_move.is_valid():
            new_move.prev = current_move
            next_mv.append(new_move)

        # Move one missionary from left to right.
        new_move = CannibalsMissionaries('right',current_move.cannibalLeft, current_move.missionariesLeft - 1,
                                          current_move.cannibalRight, current_move.missionariesRight + 1)
        if new_move.is_valid():
            new_move.prev = current_move
            next_mv.append(new_move)

        # Move one cannibal from left to right.
        new_move = CannibalsMissionaries('right',current_move.cannibalLeft - 1, current_move.missionariesLeft,
                                          current_move.cannibalRight + 1, current_move.missionariesRight)
        if new_move.is_valid():
            new_move.prev = current_move
            next_mv.append(new_move)
        # for every move we check if it is valid and if it is we add it to the next moves list.
    else:
        # if the boat is on the right side of the river we have 5 options for moving the other elements.

        # Move two missionaries from right to left.
        new_move = CannibalsMissionaries('left',current_move.cannibalLeft, current_move.missionariesLeft + 2,
                                          current_move.cannibalRight, current_move.missionariesRight - 2)
        if new_move.is_valid():
            new_move.prev = current_move
            next_mv.append(new_move)

        # Move two cannibals from right to left.
        new_move = CannibalsMissionaries('left',current_move.cannibalLeft + 2, current_move.missionariesLeft,
                                          current_move.cannibalRight - 2, current_move.missionariesRight)
        if new_move.is_valid():
            new_move.prev = current_move
            next_mv.append(new_move)

        # Move one missionary and one cannibal from right to left.
        new_move = CannibalsMissionaries('left',current_move.cannibalLeft + 1, current_move.missionariesLeft + 1,
                                          current_move.cannibalRight - 1, current_move.missionariesRight - 1)
        if new_move.is_valid():
            new_move.prev = current_move
            next_mv.append(new_move)

        # Move one missionary from right to left.
        new_move = CannibalsMissionaries('left',current_move.cannibalLeft, current_move.missionariesLeft + 1,
                                          current_move.cannibalRight, current_move.missionariesRight - 1)
        if new_move.is_valid():
            new_move.prev = current_move
            next_mv.append(new_move)

        # Move one cannibal from right to left.
        new_move = CannibalsMissionaries('left',current_move.cannibalLeft + 1, current_move.missionariesLeft,
                                          current_move.cannibalRight - 1, current_move.missionariesRight)
        if new_move.is_valid():
            new_move.prev = current_move
            next_mv.append(new_move)
    # return the next moves which are valid for the current state.
    return next_mv


def BFS():
    """
    Method to solve the problem using the Breadth First Search algorithm.
    :return: The solution to the problem.
    """
    # initialize the initial state of the problem.
    initial_move = CannibalsMissionaries('left', 3, 3, 0, 0)
    # check if the initial state is the goal state and return it if it is.
    if initial_move.goal():
        return initial_move

    # initialize the queue and the visited set.
    queue = list()
    visited = set()

    # add the initial state to the queue.
    queue.append(initial_move)
    # while the queue is not empty we pop the first element from the queue and check if it is the goal state.
    while queue:
        state = queue.pop(0)
        if state.goal():
            return state
        # if the state is not the goal state we add it to the visited set and generate the next possible moves.
        visited.add(state)
        next_mv = next_move(state)
        # for every move we check if it is in the visited set or in the queue and if it is not we add it to the queue.
        for move in next_mv:
            if (move not in visited) or (move not in queue):
                queue.append(move)
    return None


def print_solution(solution):
    """
    Print the solution to the problem.
    :param solution: the solution to the problem.
    """
    path = [solution]
    prev = solution.prev
    while prev:
        path.append(prev)
        prev = prev.prev

    for move in range(len(path)):
        state = path[len(path) - move - 1]
        print(f"Left: {state.cannibalLeft} cannibals and {state.missionariesLeft} missionaries {', boat' if state.boat == "left" else ''}")
        print(f"Right: {state.cannibalRight} cannibals and {state.missionariesRight} missionaries {', boat' if state.boat == "right" else ''}")
        print()


def main():
    solution = BFS()
    print_solution(solution)


# if called from the command line, call main()
if __name__ == "__main__":
    main()
