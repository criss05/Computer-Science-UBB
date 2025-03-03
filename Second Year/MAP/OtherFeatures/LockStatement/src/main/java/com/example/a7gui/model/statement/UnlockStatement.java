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

public class UnlockStatement implements IStatement{
    private String var;
    public Lock lock = new ReentrantLock();

    public UnlockStatement(String var) {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        if(!prgState.getSymTable().contains(this.var)){
            throw new StatementException("Unlock: var not in sym tab");
        }
        IValue found = prgState.getSymTable().getValue(this.var);
        if(!found.getType().equals(new IntType())){
            throw new StatementException("Unlock: var no of type int");
        }
        Integer foundIndex = ((IntValue) found).getValue();
        if(!prgState.getLockTable().contains(foundIndex)){
            throw new StatementException("Unlock: index not in lock table.");
        }
        else if(prgState.getLockTable().getValue(foundIndex)==prgState.getID()){
            lock.lock();
            prgState.getLockTable().update(foundIndex, -1);
            lock.unlock();
        }
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new UnlockStatement(this.var);
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType type = typeEnv.getValue(this.var);
        if(type.equals(new IntType())) {
            return typeEnv;
        }
        throw new StatementException("Unlock: var not og type int");
    }

    @Override
    public String toString() {
        return "unlock(" + this.var + ")";
    }
}
