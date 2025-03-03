package repository;

import exception.RepoException;
import model.state.PrgState;

public interface IRepository {
    PrgState getCrtPrg();
    void addPrg(PrgState prgState);
    void ClearFile()throws RepoException;
    void logWriteFile()throws RepoException;
}
