package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.types.IntType;
import com.example.a7gui.model.value.IValue;
import com.example.a7gui.model.value.IntValue;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class CountDownStatement implements IStatement{
    private String var;
    public Lock lock = new ReentrantLock();

    public CountDownStatement(String var) {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        if(!prgState.getSymTable().contains(this.var)){
            throw new StatementException("CountDown: var not in sym table");
        }
        IValue found = prgState.getSymTable().getValue(this.var);
        if(!found.getType().equals(new IntType())){
            throw new StatementException("CountDown: found is not int");
        }
        Integer foundIndex = ((IntValue)found).getValue();
        lock.lock();
        if(!prgState.getLatchTable().contains(foundIndex)){
            lock.unlock();
            throw new StatementException("CountDown: found index not in latch table");
        }
        else if(prgState.getLatchTable().getValue(foundIndex) > 0){
            prgState.getLatchTable().update(foundIndex, prgState.getLatchTable().getValue(foundIndex)-1);
            lock.unlock();
        }
        prgState.getOutput().add(((Integer)prgState.getID()).toString());
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new CountDownStatement(var);
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "countDown(" + var + ')';
    }
}
