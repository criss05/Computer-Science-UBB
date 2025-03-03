package model.expression;

import exception.ADTException;
import exception.ExpressionException;
import model.adt.IMyDictionary;
import model.types.IntType;
import model.value.BoolValue;
import model.value.IValue;
import model.value.IntValue;

public class RelationalExpression implements IExpression{
    private IExpression leftExp, rightExp;
    private RelationalOperator operator;

    public RelationalExpression(IExpression leftExp, RelationalOperator operator, IExpression rightExp) {
        this.leftExp = leftExp;
        this.rightExp = rightExp;
        this.operator = operator;
    }

    @Override
    public IValue eval(IMyDictionary<String, IValue> map) throws ExpressionException, ADTException {
        IValue leftVal = this.leftExp.eval(map);
        IValue rightVal = this.rightExp.eval(map);

        if(!leftVal.getType().equals(new IntType()))
            throw new ExpressionException("Left expression is not an int.");
        if(!rightVal.getType().equals(new IntType()))
            throw new ExpressionException("Right expression is not an int.");

        IntValue intLeftVal = (IntValue) leftVal;
        IntValue intRightVal = (IntValue) rightVal;

        switch(operator){
            case LESS:
                return new BoolValue(intLeftVal.getValue() < intRightVal.getValue());
            case LESS_EQUAL:
                return new BoolValue(intLeftVal.getValue() <= intRightVal.getValue());
            case EQUAL:
                return new BoolValue(intLeftVal.getValue() == intRightVal.getValue());
            case DIFFERENT:
                return new BoolValue(intLeftVal.getValue() != intRightVal.getValue());
            case GRATER:
                return new BoolValue(intLeftVal.getValue() > intRightVal.getValue());
            case GRATER_EQUAL:
                return new BoolValue(intLeftVal.getValue() >= intRightVal.getValue());
            default:
                throw new ExpressionException("Unknown operator!");
        }
    }

    @Override
    public IExpression deepcopy() {
        return new RelationalExpression(this.leftExp.deepcopy(), this.operator, this.rightExp.deepcopy());
    }

    @Override
    public String toString() {
        return this.leftExp + " " + this.operator + " " + this.rightExp;
    }
}
