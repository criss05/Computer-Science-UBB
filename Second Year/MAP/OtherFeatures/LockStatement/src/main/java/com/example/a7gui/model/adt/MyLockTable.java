package com.example.a7gui.model.adt;

import com.example.a7gui.exception.KeyNotFoundException;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class MyLockTable implements IMyTable{
    Map<Integer, Integer> map;
    public Lock lock = new ReentrantLock();
    private Integer freeLocation;

    public MyLockTable() {this.map = new HashMap<>(); this.freeLocation=0;}

    @Override
    public void insert(Integer v) {
        lock.lock();
        this.map.put(freeLocation, v);
        freeLocation+=1;
        lock.unlock();
    }

    public Integer getFreeLocation() {
        return this.freeLocation;
    }

    @Override
    public Integer getValue(Integer k) throws KeyNotFoundException {
        lock.lock();
        Integer v;
        if(!this.map.containsKey(k)) {
            lock.unlock();
            throw new KeyNotFoundException("LockTable: Key was not found");
        }
        v = this.map.get(k);
        lock.unlock();
        return v;
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
        if(!this.map.containsKey(k)){
            lock.unlock();
            throw new KeyNotFoundException("Lock Table: the key was not found.");
        }
        this.map.remove(k);
        lock.unlock();
    }

    @Override
    public void update(Integer k, Integer v) {
        lock.lock();
        this.map.put(k, v);
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
        return "LockTable: \n" + str + "\n";
    }
}
