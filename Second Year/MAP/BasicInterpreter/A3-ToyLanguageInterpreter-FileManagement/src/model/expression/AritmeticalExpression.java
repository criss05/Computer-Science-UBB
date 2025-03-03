package model.expression;

import exception.ADTException;
import exception.ExpressionException;
import model.adt.IMyDictionary;
import model.types.IntType;
import model.value.IValue;
import model.value.IntValue;

public class AritmeticalExpression implements IExpression{
    private IExpression leftExp, rightExp;
    private AritmeticalOperator operator;

    public AritmeticalExpression(IExpression leftExp, AritmeticalOperator operator, IExpression rightExp) {
        this.leftExp = leftExp;
        this.operator = operator;
        this.rightExp = rightExp;
    }

    @Override
    public IValue eval(IMyDictionary<String, IValue> map) throws ExpressionException, ADTException {
        IValue leftValue = this.leftExp.eval(map);
        IValue rightValue = this.rightExp.eval(map);

        if(!leftValue.getType().equals(new IntType()))
            throw new ExpressionException("Left expression is not an int.");
        if(!rightValue.getType().equals(new IntType()))
            throw new ExpressionException("Right expression is not an int.");

        IntValue leftIntValue = (IntValue) leftValue;
        IntValue rightIntValue = (IntValue) rightValue;

        switch (operator){
            case ADD:
                return new IntValue(leftIntValue.getValue()+rightIntValue.getValue());
            case SUBTRACT:
                return new IntValue(leftIntValue.getValue()-rightIntValue.getValue());
            case DIVIDE: {
                if (rightIntValue.getValue()==0)
                    throw new ExpressionException("Division by zero.");
                return new IntValue(leftIntValue.getValue() / rightIntValue.getValue());
            }
            case MULTIPLY:
                return new IntValue(leftIntValue.getValue()*rightIntValue.getValue());
            default:
                throw new ExpressionException("Unknown operator.");
        }
    }

    @Override
    public IExpression deepcopy() {
        return new AritmeticalExpression(this.leftExp.deepcopy(),this.operator, this.rightExp.deepcopy());
    }

    @Override
    public String toString() {
        return this.leftExp+" "+ operator+ " "+ this.rightExp;
    }
}
