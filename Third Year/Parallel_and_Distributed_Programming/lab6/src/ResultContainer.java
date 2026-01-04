import java.util.List;
import java.util.concurrent.atomic.AtomicReference;

class ResultContainer {
    private final AtomicReference<List<Integer>> solution = new AtomicReference<>(null);

    public void setSolution(List<Integer> path) {
        solution.compareAndSet(null, path);
    }

    public List<Integer> getSolution() {
        return solution.get();
    }

    public boolean isSolved() {
        return solution.get() != null;
    }
}