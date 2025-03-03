package com.example.a7gui.model.adt;
import com.example.a7gui.exception.KeyNotFoundException;
import java.util.HashMap;
import java.util.Map;


public class MyHeap <K,V>implements IMyHeap<K,V>{
    private Integer freeLocation=1;
    private Map<K,V> map;

    public MyHeap(){
        this.map = new HashMap<>();
    }

    @Override
    public Integer insert(V value){
        this.map.put((K)freeLocation, value);
        this.freeLocation++;
        return this.freeLocation-1;
    }

    @Override
    public V getValue(K key) throws KeyNotFoundException {
        if(!this.map.containsKey(key))
            throw new KeyNotFoundException("Address in the heap was not found!");
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

    @Override
    public void update(K key, V value) {
        if(map.containsKey(key))
            map.put(key, value);
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        for(K key : this.map.keySet())
            str.append(key).append("->").append(this.map.get(key)).append("\n");
        return "Heap: \n" + str + "\n";
    }

    public void setMap(Map<K, V> map) {
        this.map = map;
    }

    public Map<K, V> getMap() {
        return map;
    }
}
