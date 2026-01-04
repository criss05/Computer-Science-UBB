import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.ForkJoinTask;
import java.util.concurrent.RecursiveAction;

class ForkJoinHamiltonianSolver implements HamiltonianSolver {

    @Override
    public List<Integer> solve(Graph graph, int startVertex) {
        ForkJoinPool pool = new ForkJoinPool();
        ResultContainer result = new ResultContainer();
        boolean[] visited = new boolean[graph.getNumVertices()];
        List<Integer> path = new ArrayList<>();

        path.add(startVertex);
        visited[startVertex] = true;

        HamiltonianTask rootTask = new HamiltonianTask(graph, startVertex, startVertex, visited, path, result);
        pool.invoke(rootTask);

        return result.getSolution();
    }

    // Inner RecursiveTask class
    private static class HamiltonianTask extends RecursiveAction {
        private final Graph graph;
        private final int current;
        private final int startNode;
        private final boolean[] visited;
        private final List<Integer> path;
        private final ResultContainer result;

        public HamiltonianTask(Graph graph, int current, int startNode, boolean[] visited, List<Integer> path, ResultContainer result) {
            this.graph = graph;
            this.current = current;
            this.startNode = startNode;
            this.visited = visited;
            this.path = path;
            this.result = result;
        }

        @Override
        protected void compute() {
            if (result.isSolved()) return;

            if (path.size() == graph.getNumVertices()) {
                if (graph.getNeighbors(current).contains(startNode)) {
                    List<Integer> fullCycle = new ArrayList<>(path);
                    fullCycle.add(startNode);
                    result.setSolution(fullCycle);
                }
                return;
            }

            List<Integer> neighbors = graph.getNeighbors(current);
            List<ForkJoinTask<Void>> tasks = new ArrayList<>();

            for (int neighbor : neighbors) {
                if (!visited[neighbor]) {
                    boolean[] newVisited = visited.clone();
                    newVisited[neighbor] = true;
                    List<Integer> newPath = new ArrayList<>(path);
                    newPath.add(neighbor);

                    HamiltonianTask task = new HamiltonianTask(graph, neighbor, startNode, newVisited, newPath, result);
                    tasks.add(task);
                }
            }

            invokeAll(tasks);
        }
    }
}