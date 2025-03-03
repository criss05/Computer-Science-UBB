package com.example.a7gui.model.statement;

import com.example.a7gui.exception.ADTException;
import com.example.a7gui.exception.ExpressionException;
import com.example.a7gui.exception.KeyNotFoundException;
import com.example.a7gui.exception.StatementException;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.expression.IExpression;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.value.IValue;

public class PrintStatement implements IStatement{
    private IExpression expression;
    public PrintStatement(IExpression expression){
        this.expression=expression;
    }

    @Override
    public PrgState execute(PrgState prgState) throws ADTException, ExpressionException {
        IValue result = this.expression.eval(prgState.getSymTable(),prgState.getHeap());
        prgState.getOutput().add(result.toString());
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new PrintStatement(this.expression.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        expression.typeCheck(typeEnv);
        return typeEnv;
    }

    @Override
    public String toString() {
        return "print(" + this.expression.toString() +")";
    }
}
