package com.example.a7gui.model.adt;

import com.example.a7gui.exception.EmptyStackException;

import java.util.List;

public interface IMyStack<T> {
    void push(T element);
    T pop() throws EmptyStackException;
    int size();
    boolean isEmpty();

    List<String> toStringGUI();
    List<String> toStringGUI2();
}
