package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.expression.IExpression;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.types.IntType;
import com.example.a7gui.model.types.StringType;
import com.example.a7gui.model.value.IValue;
import com.example.a7gui.model.value.IntValue;
import com.example.a7gui.model.value.StringValue;
import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements IStatement{
    IExpression expression;
    String var_name;

    public ReadFileStatement(IExpression expression, String var_name) {
        this.expression = expression;
        this.var_name = var_name;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        if(!prgState.getCurrentSymTable().contains(this.var_name))
            throw new StatementException("Variable is not in the SymTable.");
        if(!prgState.getCurrentSymTable().getValue(this.var_name).getType().equals(new IntType()))
            throw new StatementException("Variable is not an int.");

        IValue value = this.expression.eval(prgState.getCurrentSymTable(), prgState.getHeap());
        if(!value.getType().equals(new StringType()))
            throw new StatementException("Value is not an string.");

        if(!prgState.getFileTable().contains((StringValue) value))
            throw new StatementException("File is not open.");
        try {
            BufferedReader reader = prgState.getFileTable().getValue((StringValue) value);
            String line = reader.readLine();
            IntValue intValue;
            if(line.isEmpty()){
                intValue = new IntValue(0);
            }
            else{
                intValue =  new IntValue(Integer.parseInt(line));
            }
            prgState.getCurrentSymTable().insert(this.var_name, intValue);
        }catch (IOException error) {
            throw new StatementException("Line can not be read.");
        }
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new ReadFileStatement(this.expression.deepcopy(), this.var_name);
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typeVar= typeEnv.getValue(this.var_name);
        IType typeExp=this.expression.typeCheck(typeEnv);
        if(typeVar instanceof IntType){
            if(typeExp instanceof StringType) {
                return typeEnv;
            }else{
                throw new StatementException("Expression is not of int type");
            }
        }
        else{
            throw new StatementException("Variable type is not string");
        }
    }

    @Override
    public String toString() {
        return "Read " + this.expression + "->" + this.var_name;
    }
}
