package com.example.a7gui.model.adt;

import com.example.a7gui.exception.KeyNotFoundException;
import javafx.util.Pair;

import java.util.List;
import java.util.Map;

public interface IMyTable {
    void insert(Pair<Integer, List<Integer>> value);
    Pair<Integer, List<Integer>> getValue(Integer k)throws KeyNotFoundException;
    void remove(Integer k)throws KeyNotFoundException;
    Boolean contains(Integer k);
    Map<Integer, Pair<Integer, List<Integer>>> getMap();
    String toString();
    Integer getFreeLocation();
}
