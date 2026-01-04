import java.util.HashSet;
import java.util.Random;
import java.util.Set;

public class GraphGenerator {
    public static Graph generateRandomGraph(int numVertices, int numEdges) {
        long maxEdges = (long) numVertices * (numVertices - 1);
        if (numEdges > maxEdges) {
            throw new IllegalArgumentException("Too many edges for a graph with " + numVertices + " vertices.");
        }

        Graph graph = new Graph(numVertices);
        Random random = new Random();

        Set<String> existingEdges = new HashSet<>();

        int edgesCount = 0;

        while (edgesCount < numEdges) {
            int u = random.nextInt(numVertices);
            int v = random.nextInt(numVertices);

            if (u != v && !existingEdges.contains(u + "-" + v)) {
                graph.addEdge(u, v);
                existingEdges.add(u + "-" + v);
                edgesCount++;
            }
        }

        return graph;
    }
}