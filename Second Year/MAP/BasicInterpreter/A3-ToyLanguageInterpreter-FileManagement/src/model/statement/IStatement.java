package model.statement;

import exception.ADTException;
import exception.ExpressionException;
import exception.StatementException;
import exception.VariableAlreadyExists;
import model.state.PrgState;

public interface IStatement {
    PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists;
    String toString();
    IStatement deepcopy(); //for expressions, types, statement
}
