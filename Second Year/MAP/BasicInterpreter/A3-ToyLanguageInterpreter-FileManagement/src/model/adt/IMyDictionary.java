package model.adt;
import exception.KeyNotFoundException;

public interface IMyDictionary <K, V>{
    void insert(K key, V value);
    V getValue(K key) throws KeyNotFoundException;
    void remove(K key) throws KeyNotFoundException;
    boolean contains(K key);
    String toString();
}
