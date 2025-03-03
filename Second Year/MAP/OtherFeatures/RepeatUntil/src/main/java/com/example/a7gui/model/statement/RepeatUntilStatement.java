package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.expression.IExpression;
import com.example.a7gui.model.expression.LogicalExpression;
import com.example.a7gui.model.expression.LogicalOperator;
import com.example.a7gui.model.expression.ValueExpression;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.BoolType;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.value.BoolValue;
import com.example.a7gui.model.value.IValue;

public class RepeatUntilStatement implements IStatement{
    private IStatement statement;
    private IExpression expression;

    public RepeatUntilStatement(IStatement statement, IExpression expression) {
        this.statement = statement;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        IValue valueExp = this.expression.eval(prgState.getSymTable(), prgState.getHeap());
        if(!valueExp.getType().equals(new BoolType())){
            throw new StatementException("Repeat until: expression not of bool type.");
        }
        IStatement statement1 = new CompStatement(this.statement,new WhileStatement(new LogicalExpression(this.expression, LogicalOperator.XOR, new ValueExpression(new BoolValue(true))), this.statement));
        prgState.getExeStack().push(statement1);
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new RepeatUntilStatement(this.statement.deepcopy(), this.expression.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "repeat " + statement + " until " + expression;
    }
}
