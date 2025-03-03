package model.statement;

import exception.ADTException;
import exception.ExpressionException;
import exception.StatementException;
import model.expression.IExpression;
import model.state.PrgState;
import model.value.IValue;

public class AssignmentStatement implements IStatement{
    private String variableName;
    private IExpression expression;

    public AssignmentStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException {
        if(!prgState.getSymTable().contains((this.variableName)))
            throw new StatementException("Variable was not found!");

        IValue value = prgState.getSymTable().getValue(this.variableName);
        IValue evalValue = this.expression.eval(prgState.getSymTable());
        if (!value.getType().equals(evalValue.getType())){
            throw new StatementException("Value type is not ok.");
        }
        prgState.getSymTable().insert(this.variableName, evalValue);
        return prgState;
    }

    @Override
    public IStatement deepcopy() {
        return new AssignmentStatement(new String(this.variableName), this.expression.deepcopy());
    }

    @Override
    public String toString() {
        return this.variableName + "=" + this.expression.toString();
    }
}
