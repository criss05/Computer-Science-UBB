package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;

public interface IStatement {
    PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists;
    String toString();
    IStatement deepcopy(); //for expressions, types, statement
    IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException;
}
