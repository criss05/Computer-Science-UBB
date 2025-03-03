package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.expression.IExpression;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.types.StringType;
import com.example.a7gui.model.value.IValue;
import com.example.a7gui.model.value.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseRFileStatement implements IStatement{
    IExpression expression;

    public CloseRFileStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        IValue value = this.expression.eval(prgState.getSymTable(), prgState.getHeap());
        if(!value.getType().equals(new StringType())) {
            throw new StatementException("Value type is not string.");
        }
        if(!prgState.getFileTable().contains((StringValue) value)){
            throw new StatementException("File is not opened.");
        }
        try {
            BufferedReader reader = prgState.getFileTable().getValue((StringValue) value);
            reader.close();
            prgState.getFileTable().remove((StringValue) value);
        }
        catch(IOException err){
            throw new StatementException("Could closed buffer.");
        }
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new CloseRFileStatement(this.expression.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        this.expression.typeCheck(typeEnv);
        return typeEnv;
    }

    @Override
    public String toString() {
        return "Close(" + this.expression+")";
    }
}
