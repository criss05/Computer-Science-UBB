package com.example.a7gui.tableViewModels;

import java.util.List;

public class SemaphoreTableViewModel {
    private String index;
    private String value;
    private String list;

    public SemaphoreTableViewModel(Integer index, Integer value, List<Integer> list){
        this.index=index.toString();
        this.value=value.toString();
        this.list = list.stream().map(i->i.toString()).reduce((acc, item)->acc+","+item).orElse("");
    }

    public String getIndex() {
        return index;
    }

    public String getValue() {
        return value;
    }

    public String getList() {
        return list;
    }
}
