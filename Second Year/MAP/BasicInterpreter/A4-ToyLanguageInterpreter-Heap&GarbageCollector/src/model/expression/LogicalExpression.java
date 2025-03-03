package model.expression;

import exception.ADTException;
import exception.ExpressionException;
import model.adt.IMyDictionary;
import model.adt.IMyHeap;
import model.types.BoolType;
import model.value.BoolValue;
import model.value.IValue;

public class LogicalExpression implements IExpression {
    private IExpression leftExp, rightExp;
    private LogicalOperator operator;

    public LogicalExpression(IExpression leftExp, LogicalOperator operator, IExpression rightExp) {
        this.leftExp = leftExp;
        this.rightExp = rightExp;
        this.operator = operator;
    }

    @Override
    public IValue eval(IMyDictionary<String, IValue> map, IMyHeap<Integer, IValue> heap) throws ExpressionException, ADTException {
        IValue leftValue= this.leftExp.eval(map,heap);
        IValue rightValue=this.rightExp.eval(map,heap);
        if(!(leftValue.getType().equals(new BoolType())))
            throw new ExpressionException("The left expression is not a bool");
        if(!(rightValue.getType().equals(new BoolType())))
            throw new ExpressionException("The right expression is not a bool");

        BoolValue leftBool = (BoolValue) leftValue;
        BoolValue rightBool=(BoolValue) rightValue;
        return switch (operator) {
            case OR -> new BoolValue(leftBool.getValue() || rightBool.getValue());
            case AND -> new BoolValue(leftBool.getValue() && rightBool.getValue());
        };
    }

    @Override
    public IExpression deepcopy() {
        return new LogicalExpression(this.leftExp.deepcopy(), this.operator, this.rightExp.deepcopy());
    }

    @Override
    public String toString(){
        return this.leftExp.toString()+" "+ operator+ " "+ this.rightExp.toString();
    }
}
