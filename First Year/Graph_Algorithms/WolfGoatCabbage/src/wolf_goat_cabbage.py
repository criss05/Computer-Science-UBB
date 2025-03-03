class Vertex:
    def __init__(self, d):
        self.__states = dict(d)
        self.__elements = ["wolf", "goat", "cabbage", "boat"]

    def __repr__(self):
        return f"{self.__states}"

    def __str__(self):
        return f"{self.__states}"

    def parse_neighbors(self):
        """
        Parse neighbors of the current vertex
        :return: the neighbors of the current vertex if there are valid
        """
        # take every element from the list
        for element in self.__elements:
            d = dict(self.__states)
            # if the element is not boat, and the element does not have the same status as the boat, continue
            if element != "boat":
                if d[element] != d["boat"]:
                    continue
                # else change the status of the element and the boat
                d[element] = not d[element]
            d["boat"] = not d["boat"]
            v = Vertex(d)
            # if the new vertex is valid, yield it
            if v.is_valid():
                yield v

    def get_dict(self):
        return self.__states

    def is_valid(self):
        """
        Check if the current vertex is valid
        A vertex if valid if the goat is not with the wolf, and the goat is not with the cabbage
        :return: true if the vertex is valid, false otherwise
        """
        if self.__states["goat"] == self.__states["boat"]:
            return True
        if self.__states["goat"] == self.__states["wolf"]:
            return False
        if self.__states["goat"] == self.__states["cabbage"]:
            return False
        return True

    def __eq__(self, other):
        if not isinstance(other, Vertex):
            return False
        return self.__states == other.__states

    def __hash__(self):
        value = 0
        for key in self.__elements:
            value = value * 2 + (1 if self.__states[key] else 0)
        return value


class WolfGoatCabbageGraph:
    # We need this class to be able to parse neighbors of a vertex
    def parse_neighbors(self, x):
        return x.parse_neighbors()
