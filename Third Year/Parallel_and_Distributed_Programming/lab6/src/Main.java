import java.util.List;

public class Main {
    public static void main(String[] args) {
        // --- 1. Setup Graph ---
        // Creating a simple directed graph that definitely has a cycle
//        int V = 5;
//        Graph graph = new Graph(V);
//
//        // Cycle: 0 -> 1 -> 2 -> 3 -> 4 -> 0
//        // Adding extra edges to make it complex
//        graph.addEdge(0, 1);
//        graph.addEdge(0, 3); // extra
//        graph.addEdge(1, 2);
//        graph.addEdge(1, 4); // extra
//        graph.addEdge(2, 3);
//        graph.addEdge(3, 4);
//        graph.addEdge(4, 0);

        int V1 = 50;
        int E1 = 30;
        System.out.println("Generating graph with " + V1 + " vertices and " + E1 + " edges...");
        Graph graph1 = GraphGenerator.generateRandomGraph(V1, E1);

        int THREADS = 2;
        // --- 2. Run Manual Thread Solver ---
        System.out.println("--- Running Manual Thread Solver---");
        HamiltonianSolver manualSolver = new ManualThreadSolver(THREADS);
        long start = System.currentTimeMillis();
        //List<Integer> path1 = manualSolver.solve(graph, 0);
        List<Integer> path1 = manualSolver.solve(graph1, 0);
        long end = System.currentTimeMillis();

        printResult(path1, end - start);

        // --- 3. Run ForkJoin Solver ---
        System.out.println("\n--- Running ForkJoin Solver ---");
        HamiltonianSolver fjSolver = new ForkJoinHamiltonianSolver();
        start = System.currentTimeMillis();
        // List<Integer> path2 = fjSolver.solve(graph, 0);
        List<Integer> path2 = fjSolver.solve(graph1, 0);
        end = System.currentTimeMillis();

        printResult(path2, end - start);
    }

    private static void printResult(List<Integer> path, long duration) {
        if (path != null) {
            System.out.println("Cycle Found: " + path);
        } else {
            System.out.println("No Hamiltonian Cycle found.");
        }
        System.out.println("Time: " + duration + "ms");
    }
}