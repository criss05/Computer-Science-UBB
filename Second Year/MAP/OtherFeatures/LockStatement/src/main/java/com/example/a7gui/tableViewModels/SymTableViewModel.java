package com.example.a7gui.tableViewModels;

import com.example.a7gui.model.value.IValue;

public class SymTableViewModel {
    private String name;
    private String value;

    public SymTableViewModel(String name, IValue value) {
        this.name = name;
        this.value = value.toString();
    }

    public String getSymName() {
        return name;
    }

    public String getSymValue() {
        return value;
    }
}
