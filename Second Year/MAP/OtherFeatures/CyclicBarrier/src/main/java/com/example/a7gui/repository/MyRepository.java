package com.example.a7gui.repository;

import com.example.a7gui.exception.RepoException;
import com.example.a7gui.model.state.PrgState;
import javafx.beans.InvalidationListener;
import javafx.beans.Observable;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class MyRepository implements IRepository, Observable{
    private List<PrgState> prgStates;
    private int index=0;
    private String filename;
    private List<InvalidationListener> listeners;


    public MyRepository(String filename) {
        prgStates = new ArrayList<>();
        this.filename=filename;
        this.listeners=new ArrayList<>();
    }

    @Override
    public void addPrg(PrgState prgState) {
        prgStates.add(prgState);
    }

    @Override
    public void ClearFile()throws RepoException{
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.filename, false)));
            logFile.write("");
        }catch(IOException err){
            throw new RepoException("Could not clear the file.");
        }
    }

    @Override
    public List<PrgState> getPrgList() {
        return this.prgStates;
    }

    @Override
    public void setPrgList(List<PrgState> l) {
        prgStates=l;
    }

    @Override
    public void logWriteFile(PrgState prgState) throws RepoException {
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.filename, true)));
            logFile.println(prgState);
            logFile.close();
        }catch(IOException err){
            throw new RepoException("File doesn't exists!");
        }
    }

    @Override
    public void addListener(InvalidationListener listener) {
        this.listeners.add(listener);
    }

    @Override
    public void removeListener(InvalidationListener invalidationListener) {
        this.listeners.remove(invalidationListener);
    }

    @Override
    public void notifyListener() {
        for(InvalidationListener l : this.listeners){
            l.invalidated(this);
        }
    }
}
