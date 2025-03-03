package model.expression;

import exception.ADTException;
import exception.ExpressionException;
import exception.KeyNotFoundException;
import model.adt.IMyDictionary;
import model.adt.IMyHeap;
import model.types.IType;
import model.types.IntType;
import model.value.IValue;
import model.value.IntValue;

public class ArithmeticalExpression implements IExpression{
    private IExpression leftExp, rightExp;
    private ArithmeticalOperator operator;

    public ArithmeticalExpression(IExpression leftExp, ArithmeticalOperator operator, IExpression rightExp) {
        this.leftExp = leftExp;
        this.operator = operator;
        this.rightExp = rightExp;
    }

    @Override
    public IValue eval(IMyDictionary<String, IValue> map, IMyHeap<Integer, IValue> heap) throws ExpressionException, ADTException {
        IValue leftValue = this.leftExp.eval(map, heap);
        IValue rightValue = this.rightExp.eval(map, heap);

        if(!leftValue.getType().equals(new IntType()))
            throw new ExpressionException("Left expression is not an int.");
        if(!rightValue.getType().equals(new IntType()))
            throw new ExpressionException("Right expression is not an int.");

        IntValue leftIntValue = (IntValue) leftValue;
        IntValue rightIntValue = (IntValue) rightValue;

        return switch (operator) {
            case ADD -> new IntValue(leftIntValue.getValue() + rightIntValue.getValue());
            case SUBTRACT -> new IntValue(leftIntValue.getValue() - rightIntValue.getValue());
            case DIVIDE -> {
                if (rightIntValue.getValue() == 0)
                    throw new ExpressionException("Division by zero.");
                yield new IntValue(leftIntValue.getValue() / rightIntValue.getValue());
            }
            case MULTIPLY -> new IntValue(leftIntValue.getValue() * rightIntValue.getValue());
        };
    }

    @Override
    public IExpression deepcopy() {
        return new ArithmeticalExpression(this.leftExp.deepcopy(),this.operator, this.rightExp.deepcopy());
    }

    @Override
    public IType typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException {
        IType type1, type2;
        type1=leftExp.typeCheck(typeEnv);
        type2=rightExp.typeCheck(typeEnv);
        if (type1.equals(new IntType())){
            if(type2.equals(new IntType())){
                return new IntType();
            }
            else {
                throw new ExpressionException("Right expression is not of type int.");
            }
        }
        else {
            throw new ExpressionException("Left expression is not of type int");
        }
    }

    @Override
    public String toString() {
        return this.leftExp+" "+ operator+ " "+ this.rightExp;
    }
}
