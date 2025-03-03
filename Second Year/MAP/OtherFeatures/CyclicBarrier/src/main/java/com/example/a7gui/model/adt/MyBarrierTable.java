package com.example.a7gui.model.adt;

import com.example.a7gui.exception.KeyNotFoundException;
import javafx.util.Pair;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class MyBarrierTable implements IMyTable{
    private Map<Integer, Pair<Integer, List<Integer>>> map;
    private Lock lock = new ReentrantLock();
    private Integer freelocation;

    public MyBarrierTable() {
        this.freelocation=0;
        this.map = new HashMap<>();
    }

    @Override
    public void insert(Pair<Integer, List<Integer>> value) {
        lock.lock();
        this.map.put(this.freelocation, value);
        this.freelocation+=1;
        lock.unlock();
    }

    public Integer getFreeLocation(){
        return this.freelocation;
    }

    @Override
    public Pair<Integer, List<Integer>> getValue(Integer k) throws KeyNotFoundException {
        lock.lock();
        Pair<Integer, List<Integer>> v = this.map.get(k);
        lock.unlock();
        return v;
    }

    @Override
    public void remove(Integer k) throws KeyNotFoundException {
        lock.lock();
        if(!this.map.containsKey(k)){
           lock.unlock();
           throw new KeyNotFoundException("Barrier table: k could nto be removed.");
        }
        this.map.remove(k);
        lock.unlock();
    }

    @Override
    public Boolean contains(Integer k) {
        lock.lock();
        Boolean b = this.map.containsKey(k);
        lock.unlock();
        return b;
    }

    @Override
    public Map<Integer, Pair<Integer, List<Integer>>> getMap() {
        return this.map;
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        for(Integer key : this.map.keySet())
            str.append(key).append("->").append(this.map.get(key)).append("\n");
        return "Barrier Table: \n" + str + "\n";
    }
}
