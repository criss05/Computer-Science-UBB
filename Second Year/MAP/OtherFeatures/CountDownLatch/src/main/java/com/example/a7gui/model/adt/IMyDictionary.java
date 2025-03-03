package com.example.a7gui.model.adt;
import com.example.a7gui.exception.KeyNotFoundException;

import java.util.List;
import java.util.Map;

public interface IMyDictionary <K, V>{
    void insert(K key, V value);
    V getValue(K key) throws KeyNotFoundException;
    void remove(K key) throws KeyNotFoundException;
    boolean contains(K key);
    String toString();
    Map<K, V> getMap();
    IMyDictionary<K, V> deepcopy();
    List<String> toStringGUI();
}
