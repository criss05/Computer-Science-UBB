package com.example.a7gui.model.adt;

import com.example.a7gui.exception.KeyNotFoundException;
import javafx.util.Pair;
import java.util.List;
import java.util.Map;

public interface ISemaphoreTable {
    void insert(Integer key, Pair<Integer, List<Integer>> value);
    Pair<Integer, List<Integer>> getValue(Integer key) throws KeyNotFoundException;
    Boolean contains(Integer key);
    String toString();
    Map<Integer, Pair<Integer, List<Integer>>> getMap();
    public Integer getFreeLoc();
}
