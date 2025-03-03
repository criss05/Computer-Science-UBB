package com.example.a7gui.model.adt;

import com.example.a7gui.exception.KeyNotFoundException;
import com.example.a7gui.exception.VariableAlreadyExists;
import com.example.a7gui.model.statement.IStatement;
import javafx.util.Pair;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MyProcTable implements IMyTable{
    private Map<String, Pair<List<String>, IStatement>> map;

    public MyProcTable() {
        this.map = new HashMap<>();
    }

    @Override
    public void insert(String name, Pair<List<String>, IStatement> value) throws VariableAlreadyExists {
        if(this.map.containsKey(name)){
            throw new VariableAlreadyExists("Proc table: Procedure already exists");
        }
        this.map.put(name, value);
    }

    @Override
    public Pair<List<String>, IStatement> getValue(String name) throws KeyNotFoundException {
        return this.map.get(name);
    }

    @Override
    public Boolean contains(String name) {
        return this.map.containsKey(name);
    }

    @Override
    public void remove(String name) throws KeyNotFoundException {
        if(!this.map.containsKey(name)){
            throw new KeyNotFoundException("Proc table: the name was not found");
        }
        this.map.remove(name);
    }

    @Override
    public Map<String, Pair<List<String>, IStatement>> getMap() {
        return this.map;
    }
}
