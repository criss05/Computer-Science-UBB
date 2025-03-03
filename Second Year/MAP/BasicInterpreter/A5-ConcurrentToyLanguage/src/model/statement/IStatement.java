package model.statement;

import exception.*;
import model.adt.IMyDictionary;
import model.state.PrgState;
import model.types.IType;

public interface IStatement {
    PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists;
    String toString();
    IStatement deepcopy(); //for expressions, types, statement
}
