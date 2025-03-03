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
import java.io.FileReader;
import java.io.IOError;
import java.io.IOException;

public class OpenRFileStatement implements IStatement{
    IExpression expression;

    public OpenRFileStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        IValue value = this.expression.eval(prgState.getSymTable(), prgState.getHeap());

        if(!value.getType().equals(new StringType()))
            throw new StatementException("Value type is not a String.");

        if(prgState.getSymTable().contains(value.toString()))
            throw new VariableAlreadyExists("Key already exists!");
        try {
            BufferedReader reader = new BufferedReader(new FileReader(((StringValue)value).toString()));
            prgState.getFileTable().insert((StringValue) value, reader);
        }catch (IOException | IOError err){
            throw new StatementException("File could not be open.");
        }
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new OpenRFileStatement(this.expression.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        this.expression.typeCheck(typeEnv);
        return typeEnv;
    }

    @Override
    public String toString() {
        return "Open(" + this.expression+")";
    }
}
