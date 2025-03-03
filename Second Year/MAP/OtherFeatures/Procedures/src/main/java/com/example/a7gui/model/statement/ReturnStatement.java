package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;

public class ReturnStatement implements IStatement{
    public ReturnStatement() {}

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        prgState.getSymTableStack().pop();
        prgState.setCurrentSymTable();
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new ReturnStatement();
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "return";
    }
}
