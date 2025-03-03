package com.example.a7gui.tableViewModels;

public class LockTableViewModel {
    private String location;
    private String value;

    public LockTableViewModel(Integer location, Integer value) {
        this.location = location.toString();
        this.value = value.toString();
    }

    public String getLocation() {
        return location;
    }

    public String getValue() {
        return value;
    }
}
