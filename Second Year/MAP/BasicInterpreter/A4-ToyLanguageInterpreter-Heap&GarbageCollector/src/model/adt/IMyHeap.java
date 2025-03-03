package model.adt;
import exception.KeyNotFoundException;

import java.util.Map;

public interface IMyHeap <K,V>{
    Integer insert(V value);
    V getValue(K key) throws KeyNotFoundException;
    void remove(K key) throws KeyNotFoundException;
    boolean contains(K key);
    String toString();
    void update(K key, V value);
    void setMap(Map<K, V> map);
    Map<K, V> getMap();
}
