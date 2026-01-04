import java.util.ArrayList;
import java.util.List;

class ManualThreadSolver implements HamiltonianSolver {
    private final int totalThreads;

    public ManualThreadSolver(int totalThreads) {
        this.totalThreads = totalThreads;
    }

    @Override
    public List<Integer> solve(Graph graph, int startVertex) {
        ResultContainer result = new ResultContainer();
        boolean[] visited = new boolean[graph.getNumVertices()];
        List<Integer> path = new ArrayList<>();

        path.add(startVertex);
        visited[startVertex] = true;

        try {
            search(graph, startVertex, startVertex, visited, path, totalThreads, result);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        return result.getSolution();
    }

    private void search(Graph graph, int current, int startNode, boolean[] visited,
                        List<Integer> path, int threadBudget, ResultContainer result) throws InterruptedException {

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
        List<Integer> validNeighbors = new ArrayList<>();
        for (int n : neighbors) {
            if (!visited[n]) validNeighbors.add(n);
        }

        if (validNeighbors.isEmpty()) return;

        if (threadBudget == 1) {
            for (int nextNode : validNeighbors) {
                if (result.isSolved()) return;

                visited[nextNode] = true;
                path.add(nextNode);
                search(graph, nextNode, startNode, visited, path, 1, result);
                path.remove(path.size() - 1); // Backtrack
                visited[nextNode] = false;
            }
        } else {
            int nSize = validNeighbors.size();
            List<Thread> activeThreads = new ArrayList<>();

            int baseBudget = threadBudget / nSize;
            int remainder = threadBudget % nSize;

            for (int i = 0; i < nSize; i++) {
                int nextNode = validNeighbors.get(i);
                int allocatedBudget = baseBudget + (i < remainder ? 1 : 0);

                boolean[] newVisited = visited.clone();
                newVisited[nextNode] = true;
                List<Integer> newPath = new ArrayList<>(path);
                newPath.add(nextNode);

                if (allocatedBudget > 0) {
                    if (i == nSize - 1) {
                        search(graph, nextNode, startNode, newVisited, newPath, allocatedBudget, result);
                    } else {
                        Thread t = new Thread(() -> {
                            try {
                                search(graph, nextNode, startNode, newVisited, newPath, allocatedBudget, result);
                            } catch (InterruptedException e) {
                                Thread.currentThread().interrupt();
                            }
                        });
                        activeThreads.add(t);
                        t.start();
                    }
                } else {
                    search(graph, nextNode, startNode, newVisited, newPath, 1, result);
                }
            }

            for (Thread t : activeThreads) {
                t.join();
            }
        }
    }
}