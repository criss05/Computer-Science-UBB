package com.example.a7gui.model.adt;

import com.example.a7gui.exception.EmptyStackException;
import com.example.a7gui.model.statement.CompStatement;

import java.util.ArrayList;
import java.util.List;
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

    @Override
    public List<String> toStringGUI() {
        List<String> stack = new ArrayList<>();
        for(T element : this.stack){
            stack.addFirst(element.toString());
        }
        return stack;
    }

    @Override
    public List<String> toStringGUI2() {
        List<String> stack = new ArrayList<>();
        for (T e: this.stack.reversed()){
            if (e instanceof CompStatement compElement){
                stack.add(compElement.getStatement1().toString());
                while(compElement.getStatement2() instanceof CompStatement next){
                    compElement=next;
                    stack.add(compElement.getStatement1().toString());
                }
                stack.add(compElement.getStatement2().toString());
            }
            else{
                stack.add(e.toString());
            }
        }
        return stack;
    }
}
