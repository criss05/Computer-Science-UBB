package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.types.IntType;
import com.example.a7gui.model.value.IValue;
import com.example.a7gui.model.value.IntValue;

import javax.swing.plaf.nimbus.State;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class NewLockStatement implements IStatement{
    private String var;
    public Lock lock = new ReentrantLock();

    public NewLockStatement(String var) {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        if(!prgState.getSymTable().contains(this.var)){
            throw new StatementException("New lock: var not in sym table");
        }
        if(!prgState.getSymTable().getValue(this.var).getType().equals(new IntType())){
            throw new StatementException("New lock: var is not of type int.");
        }
        lock.lock();
        Integer free = prgState.getLockTable().getFreeLocation();
        prgState.getLockTable().insert(-1);
        prgState.getSymTable().insert(this.var, new IntValue(free));
        lock.unlock();
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new NewLockStatement(this.var);
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType type = typeEnv.getValue(this.var);
        if(type.equals(new IntType())) {
            return typeEnv;
        }
        throw new StatementException("New lock: var not og type int");
    }

    @Override
    public String toString() {
        return "newLock(" + this.var + ")";
    }
}
