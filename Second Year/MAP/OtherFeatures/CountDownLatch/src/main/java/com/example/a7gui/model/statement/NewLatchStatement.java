package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.expression.IExpression;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.types.IntType;
import com.example.a7gui.model.value.IValue;
import com.example.a7gui.model.value.IntValue;

import javax.security.sasl.SaslException;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class NewLatchStatement implements IStatement{
    private String var;
    private IExpression exp;
    public Lock lock = new ReentrantLock();

    public NewLatchStatement(String var, IExpression exp) {
        this.var = var;
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        IValue value = this.exp.eval(prgState.getSymTable(), prgState.getHeap());
        if(!value.getType().equals(new IntType())){
            throw new StatementException("Expression not of type int");
        }
        Integer number = ((IntValue)value).getValue();
        lock.lock();
        Integer freeLoc = prgState.getLatchTable().getFreeLocation();
        prgState.getLatchTable().insert(number);
        prgState.getSymTable().insert(this.var, new IntValue(freeLoc));
        lock.unlock();
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new NewLatchStatement(var, this.exp.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "newLatch(" + var + ", "+ exp + ')';
    }
}
