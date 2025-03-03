package model.statement;

import exception.ADTException;
import exception.ExpressionException;
import exception.KeyNotFoundException;
import exception.StatementException;
import model.adt.IMyDictionary;
import model.expression.IExpression;
import model.state.PrgState;
import model.types.BoolType;
import model.types.IType;
import model.value.BoolValue;
import model.value.IValue;


public class IfStatement implements IStatement {
    private IExpression expression;
    private IStatement thenStatement;
    private IStatement elseStatement;

    public IfStatement(IExpression expression, IStatement thenStatement, IStatement elseStatement) {
        this.expression = expression;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ExpressionException, ADTException {
        IValue val=expression.eval(prgState.getSymTable(), prgState.getHeap());
        if(!val.getType().equals(new BoolType()))
            throw new StatementException("Expression does not return a bool.");
        BoolValue value = (BoolValue) val;
        if(value.getValue())
            prgState.getExeStack().push(thenStatement);
        else
            prgState.getExeStack().push(elseStatement);
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new IfStatement(this.expression.deepcopy(), this.thenStatement.deepcopy(), this.elseStatement.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typeExp = this.expression.typeCheck(typeEnv);
        if(typeExp.equals(new BoolType())){
            this.thenStatement.typeCheck(typeEnv.deepcopy());
            this.elseStatement.typeCheck(typeEnv.deepcopy());
            return typeEnv;
        }
        else{
            throw new StatementException("The condition of the if statement is not a bool");
        }
    }

    @Override
    public String toString() {
        return "if("+expression+"){"+thenStatement+"}else{"+elseStatement+"}\n";
    }
}
