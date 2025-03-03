package com.example.a7gui.model.adt;

import com.example.a7gui.exception.KeyNotFoundException;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class MyLatchTable implements IMyTable{
    private Map<Integer, Integer> map;
    private Integer freelocation;
    public Lock lock = new ReentrantLock();

    public MyLatchTable() {this.map = new HashMap<>();this.freelocation=0;}

    @Override
    public void insert(Integer v) {
        lock.lock();
        this.map.put(freelocation, v);
        freelocation+=1;
        lock.unlock();
    }

    @Override
    public Integer getValue(Integer k) {
        lock.lock();
        Integer v = this.map.get(k);
        lock.unlock();
        return v;
    }

    @Override
    public void update(Integer k, Integer v) throws KeyNotFoundException {
        lock.lock();
        if(!map.containsKey(k)){
            lock.unlock();
            throw new KeyNotFoundException("Latch table: couldn't update the key");
        }
        map.put(k,v);
        lock.unlock();
    }

    @Override
    public Integer getFreeLocation() {
        return freelocation;
    }

    @Override
    public Boolean contains(Integer k) {
        lock.lock();
        Boolean b = this.map.containsKey(k);
        lock.unlock();
        return b;
    }

    @Override
    public void remove(Integer k) throws KeyNotFoundException {
        lock.lock();
        if(!map.containsKey(k)){
            lock.unlock();
            throw new KeyNotFoundException("Latch table: couldn't delete the key");
        }
        map.remove(k);
        lock.unlock();
    }

    @Override
    public Map<Integer, Integer> getMap() {
        return this.map;
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        for(Integer key : this.map.keySet())
            str.append(key).append("->").append(this.map.get(key)).append("\n");
        return "Latch Table: \n" + str + "\n";
    }
}
