package com.example.a7gui.model.statement;

import com.example.a7gui.exception.ExpressionException;
import com.example.a7gui.exception.KeyNotFoundException;
import com.example.a7gui.exception.StatementException;
import com.example.a7gui.exception.VariableAlreadyExists;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.value.IValue;

public class VarDeclStatement implements IStatement{
    private String variable;
    private IType type;

    public VarDeclStatement(String variable, IType type) {
        this.variable = variable;
        this.type = type;
    }

    @Override
    public PrgState execute(PrgState prgState) throws VariableAlreadyExists{
        if (prgState.getSymTable().contains((this.variable)))
            throw new VariableAlreadyExists("Variable already exists!");
        IValue value = this.type.defaultValue();

        prgState.getSymTable().insert(this.variable, value);
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new VarDeclStatement(this.variable, this.type.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        typeEnv.insert(this.variable, this.type);
        return typeEnv;
    }

    @Override
    public String toString() {
        return this.type + " "+ this.variable;
    }
}
