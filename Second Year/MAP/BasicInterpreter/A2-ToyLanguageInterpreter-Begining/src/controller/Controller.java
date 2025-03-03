package controller;

import exception.*;
import model.adt.*;
import model.state.PrgState;
import model.statement.IStatement;
import repository.IRepository;

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
        while (!prgState.getExeStack().isEmpty()){
            this.oneStep(prgState);
            System.out.println(prgState);
        }
        prgState.init();
    }

    public void addStatement(IStatement statement){
        PrgState prgState = new PrgState(statement);
        repo.addPrg(prgState);
    }

    public void displayPrgState(){
        PrgState crtState = this.repo.getCrtPrg();
        System.out.println(crtState);
    }
}
