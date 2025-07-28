import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from scipy.stats import ttest_ind, ranksums

def analyze_results(csv_file="ga_results.csv"):
    df = pd.read_csv(csv_file)
    sns.set(style="whitegrid")

    for func in df['function'].unique():
        print(f"\n=== Analyzing function: {func} ===")
        subset = df[df['function'] == func]

        # Summary statistics
        summary = subset.groupby(['representation', 'crossover'])['fitness'].agg(
            mean='mean', std='std', best='min'
        ).reset_index()
        print(summary)
        summary.to_csv(f"summary_stats_{func}.csv", index=False)

        # Plotting
        plt.figure(figsize=(14, 6))
        sns.boxplot(x="representation", y="fitness", hue="crossover", data=subset)
        plt.title(f"Boxplot: Fitness by Representation and Crossover for {func}")
        plt.savefig(f"boxplot_{func}.png")
        plt.close()

        plt.figure(figsize=(14, 6))
        sns.violinplot(x="crossover", y="fitness", hue="representation", data=subset, split=True)
        plt.title(f"Violin Plot: Fitness by Crossover and Representation for {func}")
        plt.savefig(f"violinplot_{func}.png")
        plt.close()

        plt.figure(figsize=(14, 6))
        sns.swarmplot(x="representation", y="fitness", hue="crossover", data=subset, dodge=True)
        plt.title(f"Swarmplot: Fitness by Representation and Crossover for {func}")
        plt.savefig(f"swarmplot_{func}.png")
        plt.close()

        # Get all groups by (representation, crossover)
        groups = subset.groupby(['representation', 'crossover'])['fitness'].apply(list)
        groups_keys = list(groups.index)
        numeric_groups = [list(map(float, vals)) for vals in groups]

        results = []

        # Run pairwise comparisons between all group pairs
        n = len(groups_keys)
        print(f"\nPerforming pairwise tests between all {n} groups:")
        for i in range(n):
            for j in range(i + 1, n):
                g1 = numeric_groups[i]
                g2 = numeric_groups[j]
                key1 = groups_keys[i]
                key2 = groups_keys[j]

                # T-test (independent samples, unequal variance)
                t_stat, p_t = ttest_ind(g1, g2, equal_var=False)
                print(f"T-test between {key1} and {key2}: p = {p_t:.5f}")
                results.append({
                    'test': 'T-test',
                    'groups': f"{key1} vs {key2}",
                    'p_value': p_t
                })

                # Wilcoxon rank-sum test (Mann-Whitney U)
                w_stat, p_w = ranksums(g1, g2)
                print(f"Wilcoxon rank-sum between {key1} and {key2}: p = {p_w:.5f}")
                results.append({
                    'test': 'Wilcoxon rank-sum',
                    'groups': f"{key1} vs {key2}",
                    'p_value': p_w
                })

        # Save all pairwise results to CSV
        if results:
            results_df = pd.DataFrame(results)
            results_df.to_csv(f"stat_tests_pairwise_{func}.csv", index=False)

if __name__ == "__main__":
    analyze_results()
