package model.expression;

import exception.ADTException;
import model.adt.IMyDictionary;
import model.value.IValue;

public class VariableExpression implements IExpression{
    private String variable;

    public VariableExpression(String variable) {
        this.variable=variable;
    }

    @Override
    public IValue eval(IMyDictionary<String, IValue> map) throws ADTException {
        return map.getValue(variable);
    }

    @Override
    public IExpression deepcopy() {
        return new VariableExpression(new String(this.variable));
    }

    @Override
    public String toString() {
        return this.variable;
    }
}
