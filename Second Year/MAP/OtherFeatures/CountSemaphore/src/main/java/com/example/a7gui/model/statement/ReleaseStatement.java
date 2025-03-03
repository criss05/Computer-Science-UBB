package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.types.IntType;
import com.example.a7gui.model.value.IntValue;
import javafx.util.Pair;

import java.util.List;

public class ReleaseStatement implements IStatement{
    private String var;

    public ReleaseStatement(String var) {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        if(!prgState.getSymTable().contains(this.var)) {
            throw new StatementException("Release: The variable is not in the SymTable.");
        }
        if(!prgState.getSymTable().getValue(this.var).getType().equals(new IntType())){
            throw new StatementException("Release: The variable is not of type int.");
        }
        Integer foundIndex = ((IntValue) prgState.getSymTable().getValue(this.var)).getValue();

        if(!prgState.getSemTable().contains(foundIndex)){
            throw new StatementException("Release: The index is not in the Semaphore table.");
        }

        Pair<Integer, List<Integer>> pair = prgState.getSemTable().getValue(foundIndex);
        List<Integer> list = pair.getValue();
        if(list.contains(prgState.getID())){
            list.removeIf(e->e==prgState.getID());
        }
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new ReleaseStatement(var);
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typeVar = typeEnv.getValue(this.var);
        if(typeVar.equals(new IntType())){
            return typeEnv;
        }
        throw new StatementException("Release: The variable is not of type int.");
    }

    @Override
    public String toString() {
        return "release(" + var + ")";
    }
}
