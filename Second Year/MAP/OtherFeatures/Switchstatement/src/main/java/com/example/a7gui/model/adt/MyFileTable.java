package com.example.a7gui.model.adt;

import com.example.a7gui.exception.KeyNotFoundException;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MyFileTable<K,V> implements IMyDictionary<K,V>{
    private Map<K,V> map;

    public MyFileTable(){
        this.map = new HashMap<>();
    }

    public MyFileTable(Map<K,V> map){
        this.map = new HashMap<>(map);
    }

    @Override
    public void insert(K key, V value) {
        this.map.put(key, value);
    }

    @Override
    public V getValue(K key) throws KeyNotFoundException {
        if(!this.map.containsKey(key))
            throw new KeyNotFoundException("Key not found!");
        return this.map.get(key);
    }

    @Override
    public void remove(K key) throws KeyNotFoundException {
        if(!this.map.containsKey(key))
            throw new KeyNotFoundException("Key not found!");
        this.map.remove(key);
    }

    @Override
    public boolean contains(K key) {
        return this.map.containsKey(key);
    }

    public Map<K, V> getMap() {
        return map;
    }

    @Override
    public IMyDictionary<K, V> deepcopy() {
        return new MyFileTable<>(this.map);
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        for(K key : this.map.keySet())
            str.append(key).append("\n");
        return "FileTable: \n" + str + "\n";
    }

    @Override
    public List<String> toStringGUI() {
        List<String> fileTable = new ArrayList<>();
        for(K key : this.map.keySet()){
            fileTable.add(key.toString());
        }
        return fileTable;
    }
}
