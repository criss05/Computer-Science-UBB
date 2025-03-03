package repository;

import exception.RepoException;
import model.state.PrgState;

import java.util.List;

public interface IRepository {
    void addPrg(PrgState prgState);
    void ClearFile()throws RepoException;
    void logWriteFile(PrgState prgState)throws RepoException;
    List<PrgState> getPrgList();
    void setPrgList(List<PrgState> l);
    //List<PrgState> addAll(List<PrgState> prgList);
}
