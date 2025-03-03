package com.example.a7gui.model.expression;
import com.example.a7gui.exception.ExpressionException;
import com.example.a7gui.exception.KeyNotFoundException;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.adt.IMyHeap;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.value.IValue;

public class ValueExpression implements IExpression{
    private IValue value;

    public ValueExpression(IValue value){
        this.value=value;
    }

    @Override
    public IValue eval(IMyDictionary<String, IValue> map, IMyHeap<Integer, IValue> heap){
        return value;
    }

    @Override
    public IExpression deepcopy() {
        return new ValueExpression(this.value);
    }

    @Override
    public IType typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException {
        return value.getType();
    }

    @Override
    public String toString() {
        return value.toString();
    }
}
