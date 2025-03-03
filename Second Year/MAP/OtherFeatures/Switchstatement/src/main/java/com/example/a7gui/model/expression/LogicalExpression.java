package com.example.a7gui.model.expression;

import com.example.a7gui.exception.ADTException;
import com.example.a7gui.exception.ExpressionException;
import com.example.a7gui.exception.KeyNotFoundException;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.adt.IMyHeap;
import com.example.a7gui.model.types.BoolType;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.value.BoolValue;
import com.example.a7gui.model.value.IValue;

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
    public IType typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException {
        IType type1, type2;
        type1=this.leftExp.typeCheck(typeEnv);
        type2=this.rightExp.typeCheck(typeEnv);
        if(type1.equals(new BoolType())){
            if(type2.equals(new BoolType())){
                return new BoolType();
            }
            else{
                throw new ExpressionException("Right expression is not of type bool");
            }
        }
        else{
            throw new ExpressionException("Left expression is not of type bool");
        }
    }

    @Override
    public String toString(){
        return this.leftExp.toString()+" "+ operator+ " "+ this.rightExp.toString();
    }
}
