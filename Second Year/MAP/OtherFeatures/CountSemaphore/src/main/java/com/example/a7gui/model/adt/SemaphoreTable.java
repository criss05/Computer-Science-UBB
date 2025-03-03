package com.example.a7gui.model.adt;

import com.example.a7gui.exception.KeyNotFoundException;
import javafx.util.Pair;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SemaphoreTable implements ISemaphoreTable{
    private Map<Integer, Pair<Integer, List<Integer>>> semTab;
    public static Lock lock = new ReentrantLock();
    private Integer freelocation;


    public SemaphoreTable(){ this.semTab=new HashMap<>(); this.freelocation=0;}

    @Override
    public void insert(Integer key, Pair<Integer, List<Integer>> value) {
        lock.lock();
        this.semTab.put(key, value);
        this.freelocation+=1;
        lock.unlock();
    }

    public Integer getFreeLoc(){return this.freelocation;}

    @Override
    public Pair<Integer, List<Integer>> getValue(Integer key) throws KeyNotFoundException {
        lock.lock();
        if(!this.semTab.containsKey(key))
            throw new KeyNotFoundException("Semaphore Table: Key wasn't found.");
        Pair<Integer, List<Integer>> value = this.semTab.get(key);
        lock.unlock();
        return value;
    }

    @Override
    public Boolean contains(Integer key) {
        return this.semTab.containsKey(key);
    }

    @Override
    public Map<Integer, Pair<Integer, List<Integer>>> getMap() {
        return this.semTab;
    }

    @Override
    public String toString() {
        StringBuilder str=new StringBuilder();
        for(Integer k: this.semTab.keySet()){
            str.append(k).append("->").append(this.semTab.get(k)).append("\n");
        }
        return "SemaphoreTable " + str + "\n";
    }
}
