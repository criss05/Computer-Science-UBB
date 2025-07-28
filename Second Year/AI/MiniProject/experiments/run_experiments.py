import numpy as np
from tqdm import tqdm
from functions.drop_wave import drop_wave
from functions.eggholder import eggholder
from ga.genertic_algorithms import genetic_algorithm
import pandas as pd


def run_experiments():
    functions = {
        "drop_wave": (drop_wave, [(-5.12, 5.12), (-5.12, 5.12)]),
        "eggholder": (eggholder, [(-512, 512), (-512, 512)])
    }

    mutation_rate = 0.05
    crossover_rate = 0.9
    pop_size = 100
    n_bits = 16
    evaluations = 10000
    runs = 30

    results_df = []

    for fname, (func, bounds) in functions.items():
        for representation in ["binary", "real"]:
            crossover_methods = ["1-point", "2-point"] if representation == "binary" else ["arithmetic", "blx-alpha"]

            for crossover in crossover_methods:
                num_generations = evaluations // pop_size
                fitnesses = []

                for _ in tqdm(range(runs), desc=f"{fname} | {representation} | {crossover}"):
                    best_fitness = genetic_algorithm(
                        fitness_func=func,
                        bounds=bounds,
                        representation=representation,
                        crossover_type=crossover,
                        mutation_rate=mutation_rate,
                        crossover_rate=crossover_rate,
                        pop_size=pop_size,
                        num_generations=num_generations,
                        n_bits=n_bits,
                        alpha=0.5
                    )
                    fitnesses.append(best_fitness)

                for fit in fitnesses:
                    results_df.append({
                        "function": fname,
                        "representation": representation,
                        "crossover": crossover,
                        "fitness": float(fit)
                    })

    df = pd.DataFrame(results_df)
    df.to_csv("ga_results.csv", index=False)
    print("\nExperiment complete. Results saved to ga_results.csv")

if __name__ == "__main__":
    run_experiments()