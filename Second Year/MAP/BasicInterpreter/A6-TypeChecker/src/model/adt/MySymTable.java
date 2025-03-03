package model.adt;

import exception.KeyNotFoundException;

import java.util.HashMap;
import java.util.Map;

public class MySymTable<K,V> implements IMyDictionary<K, V>{
    private Map<K,V> map;

    public MySymTable(){
        this.map = new HashMap<>();
    }

    public MySymTable(Map<K,V> map){this.map=new HashMap<>(map);}

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
    public String toString() {
        StringBuilder str = new StringBuilder();
        for(K key : this.map.keySet())
            str.append(key).append("->").append(this.map.get(key)).append("\n");
        return "SymTable: \n" + str + "\n";
    }

    @Override
    public IMyDictionary<K, V> deepcopy() {
        return new MySymTable<>(this.map);
    }
}
