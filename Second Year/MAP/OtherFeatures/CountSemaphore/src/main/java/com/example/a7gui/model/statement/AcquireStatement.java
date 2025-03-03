package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.types.IntType;
import com.example.a7gui.model.value.IValue;
import com.example.a7gui.model.value.IntValue;
import javafx.util.Pair;

import java.util.List;

public class AcquireStatement implements IStatement{
    private String var;

    public AcquireStatement(String var){
        this.var=var;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        if(!prgState.getSymTable().contains(this.var)) {
            throw new StatementException("Acquire: The variable is not in the SymTable.");
        }
        if(!prgState.getSymTable().getValue(this.var).getType().equals(new IntType())){
            throw new StatementException("Acquire: The variable is not of type int.");
        }
        Integer foundIndex = ((IntValue) prgState.getSymTable().getValue(this.var)).getValue();

        if(!prgState.getSemTable().contains(foundIndex)){
            throw new StatementException("Acquire: The index is not in the Semaphore table.");
        }

        Pair<Integer, List<Integer>> pair = prgState.getSemTable().getValue(foundIndex);
        List<Integer> list = pair.getValue();
        Integer length = pair.getValue().size();
        Integer n1 = pair.getKey();
        if(n1>length){
            if(!list.contains(prgState.getID())){
                list.add(prgState.getID());
            }
        }
        else{
            prgState.getExeStack().push(new AcquireStatement(this.var));
        }
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new AcquireStatement(this.var);
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typeVar = typeEnv.getValue(this.var);
        if(typeVar.equals(new IntType())) {
            return typeEnv;
        }
        throw new StatementException("Acquire: Variable is not of type int.");
    }

    @Override
    public String toString() {
        return "acquire(" + this.var + ")";
    }
}
