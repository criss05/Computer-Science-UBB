package controller;

import exception.*;
import model.adt.*;
import model.state.PrgState;
import model.statement.IStatement;
import model.value.IValue;
import model.value.RefValue;
import repository.IRepository;

import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Controller {
    private IRepository repo;

    public Controller(IRepository repo) {
        this.repo = repo;
    }

    public PrgState oneStep(PrgState prgState)throws ADTException, ExpressionException, StatementException, VariableAlreadyExists {
        IMyStack<IStatement> stack = prgState.getExeStack();
        IStatement statement = stack.pop();
        return statement.execute(prgState);
    }

    public void allSteps()throws ADTException, ExpressionException, StatementException, VariableAlreadyExists, RepoException {
        PrgState prgState = this.repo.getCrtPrg();
        repo.ClearFile();
        repo.logWriteFile();
        while (!prgState.getExeStack().isEmpty()){
            this.oneStep(prgState);
            repo.logWriteFile();
            prgState.getHeap().setMap(safeGarbageCollector(getAddrFromSymTable(prgState.getSymTable().getMap().values()),getAddrFromHeap(prgState.getHeap().getMap().values()), prgState.getHeap().getMap()));
        }
        prgState.init();
    }

    Map<Integer, IValue> safeGarbageCollector(List<Integer> symTableAddr, List<Integer> heapAddr,Map<Integer, IValue> heap){
        return heap.entrySet().stream().filter(e->symTableAddr.contains(e.getKey()) || heapAddr.contains(e.getKey())).collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    List<Integer> getAddrFromSymTable(Collection<IValue> symTableValues){
        return symTableValues.stream().
                filter(v->v instanceof RefValue).
                map(v->{RefValue v1 = (RefValue) v; return v1.getAddress();}).
                collect(Collectors.toList());
    }


    List<Integer> getAddrFromHeap(Collection<IValue> heapValues){
        return heapValues.stream().
                filter(v->v instanceof RefValue).
                map(v->{RefValue v1 = (RefValue) v; return v1.getAddress();}).
                collect(Collectors.toList());
    }

}
