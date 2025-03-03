package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.expression.ValueExpression;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.value.IntValue;

public class WaitStatement implements IStatement{
    private Integer number;

    public WaitStatement(Integer number) {
        this.number = number;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        if(number>0){
            prgState.getExeStack().push(new CompStatement(new PrintStatement(new ValueExpression(new IntValue(number))), new WaitStatement(number-1)));
        }
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new WaitStatement(number);
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "wait(" +number + ")";
    }
}
