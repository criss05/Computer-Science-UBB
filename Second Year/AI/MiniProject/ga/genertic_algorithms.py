import numpy as np
import random


# Binary decoding helper
def binary_to_real(binary, bounds, n_bits):
    max_int = 2**n_bits - 1
    real = []
    for i in range(0, len(binary), n_bits):
        substring = binary[i:i+n_bits]
        value = int("".join(map(str, substring)), 2)
        min_b, max_b = bounds[i // n_bits]
        real_value = min_b + (max_b - min_b) * value / max_int
        real.append(real_value)
    return real

# Initialization
def initialize_population(pop_size, bounds, representation, n_bits=16):
    if representation == "binary":
        return [np.random.randint(0, 2, size=n_bits*len(bounds)).tolist() for _ in range(pop_size)]
    elif representation == "real":
        return [np.random.uniform(low=b[0], high=b[1], size=len(bounds)).tolist() for b in [bounds] * pop_size]
    return None


# Selection (Tournament)
def tournament_selection(pop, fitnesses, k=3):
    selected = random.sample(list(zip(pop, fitnesses)), k)
    return max(selected, key=lambda x: x[1])[0]

# Binary Crossover
def crossover_binary(p1, p2, method):
    if method == "1-point":
        point = random.randint(1, len(p1) - 1)
        return p1[:point] + p2[point:], p2[:point] + p1[point:]
    elif method == "2-point":
        pt1, pt2 = sorted(random.sample(range(1, len(p1)), 2))
        return (
            p1[:pt1] + p2[pt1:pt2] + p1[pt2:],
            p2[:pt1] + p1[pt1:pt2] + p2[pt2:]
        )
    return None


# Real-valued Crossover
def crossover_real(p1, p2, method, alpha=0.5):
    if method == "arithmetic":
        return [(x + y) / 2 for x, y in zip(p1, p2)], [(x + y) / 2 for x, y in zip(p2, p1)]
    elif method == "blx-alpha":
        offspring1, offspring2 = [], []
        for x, y in zip(p1, p2):
            c_min, c_max = min(x, y), max(x, y)
            I = c_max - c_min
            low = c_min - alpha * I
            high = c_max + alpha * I
            offspring1.append(random.uniform(low, high))
            offspring2.append(random.uniform(low, high))
        return offspring1, offspring2
    return None


# Binary Mutation
def mutate_binary(individual, mutation_rate):
    return [(bit if random.random() > mutation_rate else 1 - bit) for bit in individual]

# Real-valued Mutation
def mutate_real(individual, mutation_rate, bounds):
    return [
        x + np.random.normal(0, 0.1*(b[1]-b[0])) if random.random() < mutation_rate else x
        for x, b in zip(individual, bounds)
    ]

# GA Framework
def genetic_algorithm(
    fitness_func,
    bounds,
    representation='real',
    crossover_type='arithmetic',
    mutation_rate=0.01,
    crossover_rate=0.8,
    pop_size=50,
    num_generations=100,
    n_bits=16,
    alpha=0.5
):
    population = initialize_population(pop_size, bounds, representation, n_bits)
    best_solution = None
    best_fitness = float('-inf')

    for gen in range(num_generations):
        decoded = []
        if representation == 'binary':
            decoded = [binary_to_real(ind, bounds, n_bits) for ind in population]
        else:
            decoded = population

        fitnesses = [fitness_func(*ind) for ind in decoded]
        next_gen = []

        for _ in range(pop_size // 2):
            parent1 = tournament_selection(population, fitnesses)
            parent2 = tournament_selection(population, fitnesses)

            # Crossover
            if random.random() < crossover_rate:
                if representation == "binary":
                    child1, child2 = crossover_binary(parent1, parent2, crossover_type)
                else:
                    child1, child2 = crossover_real(parent1, parent2, crossover_type, alpha)
            else:
                child1, child2 = parent1[:], parent2[:]

            # Mutation
            if representation == "binary":
                child1 = mutate_binary(child1, mutation_rate)
                child2 = mutate_binary(child2, mutation_rate)
            else:
                child1 = mutate_real(child1, mutation_rate, bounds)
                child2 = mutate_real(child2, mutation_rate, bounds)

            next_gen.extend([child1, child2])

        population = next_gen

        # Update best
        gen_best_idx = np.argmax(fitnesses)
        if fitnesses[gen_best_idx] > best_fitness:
            best_fitness = fitnesses[gen_best_idx]
            best_solution = decoded[gen_best_idx]

        print(f"Generation {gen+1} | Best Fitness: {best_fitness:.5f}")

    return best_fitness
