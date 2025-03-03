package model.adt;

import exception.EmptyStackException;

public interface IMyStack<T> {
    void push(T element);
    T pop() throws EmptyStackException;
    int size();
    boolean isEmpty();
}
