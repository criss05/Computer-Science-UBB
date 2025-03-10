package com.example.a7gui.controller;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.value.IValue;
import com.example.a7gui.model.value.RefValue;
import com.example.a7gui.repository.IRepository;

import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller {
    private IRepository repo;
    private ExecutorService executor;

    public Controller(IRepository repo) {
        this.repo = repo;
    }


    public void oneStepForAllPrg(List<PrgState> prgList) throws InterruptedException, RuntimeException, RepoException {
        prgList.forEach(prg -> {
            try {
                repo.logWriteFile(prg);
            } catch (RepoException e){
                throw new RuntimeException(e.getMessage());
            }
        });
        List<Callable<PrgState>> callList = prgList.stream().
                map((PrgState p) -> (Callable<PrgState>) (p::oneStep)).
                collect(Collectors.toList());

        List<PrgState> newPrgList = executor.invokeAll(callList).stream().
                map(future->{
                            try {
                                return future.get();
                            } catch (InterruptedException | ExecutionException e) {
                                throw new RuntimeException(e);
                            }
                        }).
                filter(Objects::nonNull).collect(Collectors.toList());

        prgList.addAll(newPrgList);
        prgList.forEach(prg -> {
            try {
                repo.logWriteFile(prg);
            } catch (RepoException e) {
                throw new RuntimeException(e);
            }
        });

        repo.setPrgList(prgList);
    }

    public void allStep() throws InterruptedException, RepoException {
        executor= Executors.newFixedThreadPool(2);
        List<PrgState> prgList = removeCompletePrg(repo.getPrgList());
        while(!prgList.isEmpty()){
            prgList.forEach(prg -> {
                prg.getHeap().setMap(safeGarbageCollector(getAddrFromSymTable(prg.getCurrentSymTable().getMap().values()),getAddrFromHeap(prg.getHeap().getMap().values()), prg.getHeap().getMap()));
            });
            try {
                oneStepForAllPrg(prgList);
            }
            catch(RuntimeException | InterruptedException e){
                throw new RuntimeException(e.getMessage());
            }
           prgList = removeCompletePrg(repo.getPrgList());
        }
        executor.shutdownNow();
        repo.setPrgList(prgList);
    }

    List<PrgState> removeCompletePrg(List<PrgState>inPrgList) {
        return inPrgList.stream().
                filter(PrgState::isNotCompleted).collect(Collectors.toList());
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


    public void startThreads(){
       this.executor = Executors.newFixedThreadPool(2);
    }

    public void endThreads() {
        this.executor.shutdownNow();
    }

    public void oneStepGUI()throws ControllerException{
        List<PrgState> prgList = removeCompletePrg(repo.getPrgList());
        if(!prgList.isEmpty()) {
            prgList.forEach(prg -> {
                prg.getHeap().setMap(safeGarbageCollector(getAddrFromSymTable(prg.getCurrentSymTable().getMap().values()), getAddrFromHeap(prg.getHeap().getMap().values()), prg.getHeap().getMap()));
            });
            try {
                oneStepForAllPrg(prgList);
                this.repo.notifyListener();
            } catch (RuntimeException | InterruptedException | RepoException e) {
                throw new ControllerException(e.getMessage());
            }
            prgList = removeCompletePrg(repo.getPrgList());
        }
        else{
            executor.shutdownNow();
            repo.setPrgList(prgList);
            this.repo.notifyListener();
            throw new ControllerException("Program has ended. Execution Stack is Empty.");
        }
    }
}
