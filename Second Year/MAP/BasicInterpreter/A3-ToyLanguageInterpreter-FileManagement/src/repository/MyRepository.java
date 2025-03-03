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
    private String filename;


    public MyRepository(String filename) {
        prgStates = new ArrayList<>();
        this.filename=filename;
    }

    @Override
    public void addPrg(PrgState prgState) {
        prgStates.add(prgState);
    }

    @Override
    public PrgState getCrtPrg() {
        return prgStates.get(index);
    }

    @Override
    public void logWriteFile() throws RepoException {
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.filename, true)));
            logFile.println(this.getCrtPrg().toString());
            logFile.close();
        }catch(IOException err){
            throw new RepoException("File doesn't exists!");
        }
    }
}
