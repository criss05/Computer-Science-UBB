package com.example.a7gui.tableViewModels;

import java.util.List;

public class BarrierTableViewModel {
    private String index;
    private String value;
    private String list;

    public BarrierTableViewModel(Integer index, Integer value, List<Integer> list) {
        this.index = index.toString();
        this.value = value.toString();
        this.list = list.stream().map(s->s.toString()).reduce((acc, item)-> acc + ", " + item).orElse("");
    }

    public String getBarrierIndex() {
        return index;
    }

    public String getBarrierValue() {
        return value;
    }

    public String getBarrierList() {
        return list;
    }
}
