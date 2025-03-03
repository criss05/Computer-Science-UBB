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

public class LockStatement implements IStatement{
    private String var;
    public Lock lock = new ReentrantLock();

    public LockStatement(String var) {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        if(!prgState.getSymTable().contains(this.var)){
            throw new StatementException("Lock statement: vr not in sym table");
        }
        IValue found = prgState.getSymTable().getValue(this.var);
        if(!found.getType().equals(new IntType())){
            throw new StatementException("Lock statement: var value is not of type int");
        }
        Integer foundInt = ((IntValue)found).getValue();
        if(!prgState.getLockTable().contains(foundInt)){
            throw new StatementException("Index not in lock table.");
        }
        else if(prgState.getLockTable().getValue(foundInt)==-1){
            lock.lock();
            prgState.getLockTable().update(foundInt, prgState.getID());
            lock.unlock();
        }
        else{
            prgState.getExeStack().push(new LockStatement(this.var));
        }
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new LockStatement(this.var);
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType type = typeEnv.getValue(this.var);
        if(type.equals(new IntType())) {
            return typeEnv;
        }
        throw new StatementException("Lock: var not og type int");
    }

    @Override
    public String toString() {
        return "lock(" + var + ")";
    }
}
