package repository;

import exception.RepoException;
import model.state.PrgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class MyRepository implements IRepository{
    private List<PrgState> prgStates;
    private int index=0;


    public MyRepository() {
        prgStates = new ArrayList<>();
    }

    @Override
    public void addPrg(PrgState prgState) {
        prgStates.add(prgState);
    }

    @Override
    public PrgState getCrtPrg() {
        return prgStates.get(index);
    }

}
