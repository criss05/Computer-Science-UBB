package com.example.a7gui.model.adt;

import com.example.a7gui.exception.KeyNotFoundException;

import java.util.Map;

public interface IMyTable {
    void insert(Integer v);
    Integer getValue(Integer k) throws KeyNotFoundException;
    Boolean contains(Integer k);
    void remove(Integer k) throws KeyNotFoundException;
    Map<Integer, Integer> getMap();
    String toString();
    Integer getFreeLocation();
    void update(Integer k, Integer v);
}
