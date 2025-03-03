package model.expression;

import exception.ADTException;
import exception.ExpressionException;
import model.adt.IMyDictionary;
import model.adt.IMyHeap;
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
    public IValue eval(IMyDictionary<String, IValue> map, IMyHeap<Integer, IValue> heap) throws ExpressionException, ADTException {
        IValue leftVal = this.leftExp.eval(map, heap);
        IValue rightVal = this.rightExp.eval(map, heap);

        if(!leftVal.getType().equals(new IntType()))
            throw new ExpressionException("Left expression is not an int.");
        if(!rightVal.getType().equals(new IntType()))
            throw new ExpressionException("Right expression is not an int.");

        IntValue intLeftVal = (IntValue) leftVal;
        IntValue intRightVal = (IntValue) rightVal;

        return switch (operator) {
            case LESS -> new BoolValue(intLeftVal.getValue() < intRightVal.getValue());
            case LESS_EQUAL -> new BoolValue(intLeftVal.getValue() <= intRightVal.getValue());
            case EQUAL -> new BoolValue(intLeftVal.getValue() == intRightVal.getValue());
            case DIFFERENT -> new BoolValue(intLeftVal.getValue() != intRightVal.getValue());
            case GRATER -> new BoolValue(intLeftVal.getValue() > intRightVal.getValue());
            case GRATER_EQUAL -> new BoolValue(intLeftVal.getValue() >= intRightVal.getValue());
        };
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
