package com.example.a7gui.repository;

import com.example.a7gui.exception.RepoException;
import com.example.a7gui.model.state.PrgState;
import javafx.beans.InvalidationListener;

import java.util.List;

public interface IRepository {
    void addPrg(PrgState prgState);
    void ClearFile()throws RepoException;
    void logWriteFile(PrgState prgState)throws RepoException;
    List<PrgState> getPrgList();
    void setPrgList(List<PrgState> l);
    //List<PrgState> addAll(List<PrgState> prgList);
    void addListener(InvalidationListener listener);
    void notifyListener();
}
