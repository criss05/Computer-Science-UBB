package com.example.a7gui.tableViewModels;

import com.example.a7gui.model.value.IValue;

public class HeapTableViewModel {
    private String address;
    private String value;

    public HeapTableViewModel(Integer address, IValue value) {
        this.address = address.toString();
        this.value = value.toString();
    }

    public String getHeapAddress() {
        return address;
    }

    public String getHeapValue() {
        return value;
    }
}
