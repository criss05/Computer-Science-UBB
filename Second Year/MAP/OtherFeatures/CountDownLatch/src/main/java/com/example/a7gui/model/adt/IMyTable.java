package com.example.a7gui.model.adt;

import com.example.a7gui.exception.KeyNotFoundException;

import java.util.Map;

public interface IMyTable {
    void insert(Integer v);
    Integer getValue(Integer k);
    void update(Integer k, Integer v) throws KeyNotFoundException;
    Integer getFreeLocation();
    Boolean contains(Integer k);
    void remove(Integer k) throws KeyNotFoundException;
    Map<Integer, Integer> getMap();
    String toString();
}
