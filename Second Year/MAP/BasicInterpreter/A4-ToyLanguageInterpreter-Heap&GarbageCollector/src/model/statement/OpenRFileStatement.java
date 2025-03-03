package model.statement;

import exception.ADTException;
import exception.ExpressionException;
import exception.StatementException;
import exception.VariableAlreadyExists;
import model.expression.IExpression;
import model.state.PrgState;
import model.types.StringType;
import model.value.IValue;
import model.value.StringValue;

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
        return prgState;
    }

    @Override
    public IStatement deepcopy() {
        return new OpenRFileStatement(this.expression.deepcopy());
    }

    @Override
    public String toString() {
        return "Open(" + this.expression+")";
    }
}
