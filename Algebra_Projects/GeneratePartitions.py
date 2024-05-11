#Bărnuț Cristiana
def print_partition(partition_set):
    """
    The function is printing the partition of the given set
    :param partition_set: Partition of the set
    """
    print("{",end=" ")
    for subset in partition_set:
        print("{", end=" ")
        for element in subset:
            print(element, end=" ")
        print("}", end=" ")
    print("}")


def generates_partitions(initial_set, current_index, partition_set):
    """
    The function generates all partition of the set of given length
    :param initial_set: The given set
    :param current_index: Shows the position of current element in the initial set
    :param partition_set: Saves the partially generated partition until the printing
    """
    if current_index == len(initial_set):
        print("Partition set: ", end=" ")
        print_partition(partition_set)
        # The partition will be printing when the current index will be equal to the length
        from itertools import permutations
        print("The equivalence relation is:", end=" ")
        if len(partition_set) == 1:
            print("AxA")
        # If the partition has just one set then the equivalence relation is AxA
        elif len(partition_set) == set_length:
            print("∆A")
        # If the partition has a number of sets equal with the length then the equivalence relation is ∆A
        else:
            print("∆A U {", end="")
            for subset in range(len(partition_set)):
                if 1 < len(partition_set[subset]) < set_length:
                    relation = permutations(partition_set[subset], 2)
                    # Generates all the arrangements taken 2 by 2 of the subsets of the partition
                    for element in list(relation):
                        print(element, end=" ")
            print("}\n")
            # Prints the equivalence relation for the partition
        return
    for subset in range(len(partition_set)):
        partition_set[subset].append(initial_set[current_index])
        generates_partitions(initial_set, current_index + 1, partition_set)
        partition_set[subset].pop()
        # The partition is completed with a subset
    partition_set.append([initial_set[current_index]])
    generates_partitions(initial_set, current_index + 1, partition_set)
    partition_set.pop()
    # The partition is completed with all the subsets, so we clear the last subset and find another one which fits

print("Made by Bărnuț Cristiana")
set_length = int(input("Give a natural number for the list length: "))
given_set = list(range(1, int(set_length) + 1))
print("\nThis is the set we will work on: ", given_set)
print("\nThe program will do one of the following:\n 1.Returns the number of partitions of our set. \n "
      "2.Returns all the partitions of our set.\n 3. Exit the program.")
bell_number = [1, 1, 2, 5, 15, 52, 203, 877, 4140]
# Searching on Google, The Bell number shows the number of partitions of a set.
# So, as we have the length of the partition less or equal then 8 I took the numbers and put them in a list
# from where I can directly access them and print the correct one for the given length
while True:
    option = int(input("\nEnter a option from the list: "))
    while not (option == 1 or option == 2 or option == 3):
        option = int(input("\nPlease choose a valid option from the list"))
    if option == 1:
        print("\nThe number of partitions of the set is : ", bell_number[set_length])
    elif option == 2:
        print("\nAll partitions generated are:")
        partitions_set = []
        generates_partitions(given_set, 0, partitions_set)
    elif option == 3:
        print("Exiting...")
        break
# Here are the options from the list
