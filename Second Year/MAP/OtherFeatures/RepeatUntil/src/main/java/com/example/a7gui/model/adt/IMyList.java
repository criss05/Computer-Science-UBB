package com.example.a7gui.model.adt;

import java.util.List;

public interface IMyList <T>{

    void add(T element);
    List<T> getAll();
    String toString();
    List<String> toStringGUI();
}
