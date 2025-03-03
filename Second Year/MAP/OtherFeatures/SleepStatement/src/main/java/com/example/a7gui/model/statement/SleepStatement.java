package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;

public class SleepStatement implements IStatement{
    private Integer number;

    public SleepStatement(Integer number) {
        this.number = number;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        if(number>0){
            prgState.getExeStack().push(new SleepStatement(number-1));
        }
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new SleepStatement(number);
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "sleep(" + number + ")";
    }
}
