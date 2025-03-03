package model.statement;

import exception.*;
import model.adt.IMyDictionary;
import model.expression.IExpression;
import model.state.PrgState;
import model.types.IType;
import model.types.StringType;
import model.value.IValue;
import model.value.StringValue;

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
    public String toString() {
        return "Close(" + this.expression+")";
    }
}
