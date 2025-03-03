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

public class AwaitStatement implements IStatement{
    private String var;
    public Lock lock = new ReentrantLock();

    public AwaitStatement(String var) {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        if(!prgState.getSymTable().contains(this.var)){
            throw new StatementException("Await: var not in sym table");
        }
        IValue found = prgState.getSymTable().getValue(this.var);
        if(!found.getType().equals(new IntType())){
            throw new StatementException("Await: found is not int");
        }
        Integer foundIndex = ((IntValue)found).getValue();
        lock.lock();
        if(!prgState.getLatchTable().contains(foundIndex)){
            lock.unlock();
            throw new StatementException("Await: found index not in latch table");
        }
        else if(prgState.getLatchTable().getValue(foundIndex) > 0){
            prgState.getExeStack().push(new AwaitStatement(var));
            lock.unlock();
        }
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new AwaitStatement(var);
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "await(" + this.var + ')';
    }
}
