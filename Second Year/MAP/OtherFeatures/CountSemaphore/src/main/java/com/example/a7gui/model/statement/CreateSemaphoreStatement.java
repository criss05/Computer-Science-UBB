package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.expression.IExpression;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.types.IntType;
import com.example.a7gui.model.value.IValue;
import com.example.a7gui.model.value.IntValue;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


public class CreateSemaphoreStatement implements IStatement{
    private String var;
    private IExpression exp;
    private static Lock lock = new ReentrantLock();

    public CreateSemaphoreStatement(String var, IExpression exp){
        this.var=var;
        this.exp=exp;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        IValue value= this.exp.eval(prgState.getSymTable(), prgState.getHeap());
        if(!value.getType().equals(new IntType())){
            throw new StatementException("CreateSemaphore: The expression is not an int.");
        }
        Integer freelocation = prgState.getSemTable().getFreeLoc();
        if(prgState.getSymTable().contains(var) && prgState.getSymTable().getValue(var).getType().equals(new IntType())){
            prgState.getSymTable().insert(this.var, new IntValue(freelocation));
        }
        else{
            throw new StatementException("The variable is not in symTable or doesn't have the type int.");
        }
        IntValue intVal = (IntValue) value;
        Integer val = intVal.getValue();
        Pair<Integer, List<Integer>> pair = new Pair<>(val, new ArrayList<Integer>());
        lock.lock();
        prgState.getSemTable().insert(freelocation, pair);
        lock.unlock();
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new CreateSemaphoreStatement(var, exp.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typeVar = typeEnv.getValue(this.var);
        IType typeExp = this.exp.typeCheck(typeEnv);
        if(!typeVar.equals(new IntType())){
            throw new StatementException("CreateSem: The variable is not of type int.");
        }
        if(!typeExp.equals(new IntType())){
            throw new StatementException("CreateSem: The expression is not of type int.");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "createSemaphore( " + this.var + ", " + this.exp + ")";
    }
}
