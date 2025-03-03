package model.expression;

import exception.ExpressionException;
import model.adt.IMyDictionary;
import model.value.IValue;

public class ValueExpression implements IExpression{
    private IValue value;

    public ValueExpression(IValue value){
        this.value=value;
    }

    @Override
    public IValue eval(IMyDictionary<String, IValue> map){
        return value;
    }

    @Override
    public IExpression deepcopy() {
        return new ValueExpression(this.value);
    }

    @Override
    public String toString() {
        return value.toString();
    }
}
