package model.adt;

import java.util.ArrayList;
import java.util.List;

public class MyList<T> implements IMyList<T>{
    private List<T> list;

    public MyList(){
        this.list = new ArrayList<>();
    }

    @Override
    public void add(T element) {
        this.list.add(element);
    }

    @Override
    public List<T> getAll() {
        return this.list;
    }

    @Override
    public String toString() {
       StringBuilder str = new StringBuilder();
       for(T e: this.list)
           str.append(e).append("\n");
       return "Output:\n" + str+"\n";
    }
}
