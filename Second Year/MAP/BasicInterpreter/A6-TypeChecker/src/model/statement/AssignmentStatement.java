package model.statement;

import exception.ADTException;
import exception.ExpressionException;
import exception.KeyNotFoundException;
import exception.StatementException;
import model.adt.IMyDictionary;
import model.expression.IExpression;
import model.state.PrgState;
import model.types.IType;
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
            throw new ADTException("Variable was not found!");

        IValue value = prgState.getSymTable().getValue(this.variableName);
        IValue evalValue = this.expression.eval(prgState.getSymTable(), prgState.getHeap());
        if (!value.getType().equals(evalValue.getType())){
            throw new StatementException("Value type is not ok.");
        }
        prgState.getSymTable().insert(this.variableName, evalValue);
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new AssignmentStatement(this.variableName, this.expression.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typeVar = typeEnv.getValue(this.variableName);
        IType typeExp = this.expression.typeCheck(typeEnv);
        if(typeVar.equals(typeExp)){
            return typeEnv;
        }
        else{
            throw new StatementException("Right side is has not the same type as the left one.");
        }
    }

    @Override
    public String toString() {
        return this.variableName + "=" + this.expression.toString();
    }
}
