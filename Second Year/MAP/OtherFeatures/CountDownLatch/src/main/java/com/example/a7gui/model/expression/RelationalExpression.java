package com.example.a7gui.model.expression;

import com.example.a7gui.exception.ADTException;
import com.example.a7gui.exception.ExpressionException;
import com.example.a7gui.exception.KeyNotFoundException;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.adt.IMyHeap;
import com.example.a7gui.model.types.BoolType;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.types.IntType;
import com.example.a7gui.model.value.BoolValue;
import com.example.a7gui.model.value.IValue;
import com.example.a7gui.model.value.IntValue;

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
    public IType typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException {
        IType type1, type2;
        type1=this.leftExp.typeCheck(typeEnv);
        type2=this.rightExp.typeCheck(typeEnv);
        if(type1.equals(new IntType())){
            if (type2.equals(new IntType())){
                return new BoolType();
            }
            else{
                throw new ExpressionException("Right expression is not of type int");
            }
        }
        else{
            throw new ExpressionException("Left expression is not of type int");
        }
    }

    @Override
    public String toString() {
        return this.leftExp + " " + this.operator + " " + this.rightExp;
    }
}
