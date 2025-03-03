package model.adt;

import exception.EmptyStackException;
import java.util.Stack;

public class MyExeStack<T> implements IMyStack<T>{
    private Stack<T> stack;

    public MyExeStack() {
        this.stack = new Stack<>();
    }

    @Override
    public void push(T element) {
        this.stack.push(element);
    }

    @Override
    public T pop() throws EmptyStackException {
        if(this.stack.isEmpty())
            throw new EmptyStackException("Stack is empty!");
        return this.stack.pop();
    }

    @Override
    public int size() {
        return this.stack.size();
    }

    @Override
    public boolean isEmpty() {
        return this.stack.isEmpty();
    }

    public Stack<T> getStack() {
        return stack;
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        for(T e: this.stack)
            str.append(e).append("\n");
        return "ExeStack: \n" + str+ "\n";
    }
}
