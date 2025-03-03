package model.statement;

import exception.ADTException;
import exception.ExpressionException;
import model.expression.IExpression;
import model.state.PrgState;
import model.value.IValue;

public class PrintStatement implements IStatement{
    private IExpression expression;
    public PrintStatement(IExpression expression){
        this.expression=expression;
    }

    @Override
    public PrgState execute(PrgState prgState) throws ADTException, ExpressionException {
        IValue result = this.expression.eval(prgState.getSymTable(),prgState.getHeap());
        prgState.getOutput().add(result.toString());
        return prgState;
    }

    @Override
    public IStatement deepcopy() {
        return new PrintStatement(this.expression.deepcopy());
    }

    @Override
    public String toString() {
        return "print(" + this.expression.toString() +")";
    }
}
