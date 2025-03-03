package model.expression;

import exception.ADTException;
import exception.ExpressionException;
import exception.KeyNotFoundException;
import model.adt.IMyDictionary;
import model.value.IValue;

public interface IExpression {
    IValue eval(IMyDictionary<String, IValue> map) throws ExpressionException, ADTException;
    String toString();
    IExpression deepcopy();
}
