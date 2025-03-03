package com.example.a7gui.model.statement;

import com.example.a7gui.exception.ADTException;
import com.example.a7gui.exception.ExpressionException;
import com.example.a7gui.exception.KeyNotFoundException;
import com.example.a7gui.exception.StatementException;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.expression.IExpression;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.BoolType;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.value.BoolValue;
import com.example.a7gui.model.value.IValue;


public class IfStatement implements IStatement {
    private IExpression expression;
    private IStatement thenStatement;
    private IStatement elseStatement;

    public IfStatement(IExpression expression, IStatement thenStatement, IStatement elseStatement) {
        this.expression = expression;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ExpressionException, ADTException {
        IValue val=expression.eval(prgState.getSymTable(), prgState.getHeap());
        if(!val.getType().equals(new BoolType()))
            throw new StatementException("Expression does not return a bool.");
        BoolValue value = (BoolValue) val;
        if(value.getValue())
            prgState.getExeStack().push(thenStatement);
        else
            prgState.getExeStack().push(elseStatement);
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new IfStatement(this.expression.deepcopy(), this.thenStatement.deepcopy(), this.elseStatement.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typeExp = this.expression.typeCheck(typeEnv);
        if(typeExp.equals(new BoolType())){
            this.thenStatement.typeCheck(typeEnv.deepcopy());
            this.elseStatement.typeCheck(typeEnv.deepcopy());
            return typeEnv;
        }
        else{
            throw new StatementException("The condition of the if statement is not a bool");
        }
    }

    @Override
    public String toString() {
        return "if("+expression+"){"+thenStatement+"}else{"+elseStatement+"}";
    }
}
