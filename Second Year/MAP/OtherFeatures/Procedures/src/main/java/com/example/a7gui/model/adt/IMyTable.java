package com.example.a7gui.model.adt;

import com.example.a7gui.exception.KeyNotFoundException;
import com.example.a7gui.exception.VariableAlreadyExists;
import com.example.a7gui.model.statement.IStatement;
import javafx.util.Pair;
import java.util.List;
import java.util.Map;

public interface IMyTable {
    void insert(String name, Pair<List<String>, IStatement> value)throws VariableAlreadyExists;
    Pair<List<String>, IStatement> getValue(String name)throws KeyNotFoundException;
    Boolean contains(String name);
    void remove(String name) throws KeyNotFoundException;
    Map<String, Pair<List<String>, IStatement>> getMap();
    String toString();
}
