package com.example.a7gui.model.statement;

import com.example.a7gui.exception.ExpressionException;
import com.example.a7gui.exception.KeyNotFoundException;
import com.example.a7gui.exception.StatementException;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;

public class NopStatement implements IStatement {
    @Override
    public PrgState execute(PrgState prgState) {
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new NopStatement();
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "NopStatement";
    }
}
