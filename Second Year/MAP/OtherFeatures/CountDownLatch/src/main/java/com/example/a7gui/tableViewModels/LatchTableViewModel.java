package com.example.a7gui.tableViewModels;

public class LatchTableViewModel {
    private String location;
    private String value;

    public LatchTableViewModel(Integer location, Integer value) {
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
