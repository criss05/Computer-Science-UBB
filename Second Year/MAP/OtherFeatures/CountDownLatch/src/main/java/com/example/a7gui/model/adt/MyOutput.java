package com.example.a7gui.model.adt;

import java.util.ArrayList;
import java.util.List;

public class MyOutput<T> implements IMyList<T>{
    private List<T> list;

    public MyOutput(){
        this.list = new ArrayList<>();
    }

    @Override
    public void add(T element) {
        this.list.add(element);
    }

    @Override
    public List<T> getAll() {
        return this.list;
    }

    @Override
    public String toString() {
       StringBuilder str = new StringBuilder();
       for(T e: this.list)
           str.append(e).append("\n");
       return "Output:\n" + str+"\n";
    }

    @Override
    public List<String> toStringGUI() {
        List<String> output = new ArrayList<>();
        for(T e : this.list){
            output.add(e.toString());
        }
        return output;
    }
}
