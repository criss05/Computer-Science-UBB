package com.example.a7gui.model.expression;

import com.example.a7gui.exception.ADTException;
import com.example.a7gui.exception.ExpressionException;
import com.example.a7gui.exception.KeyNotFoundException;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.adt.IMyHeap;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.value.IValue;

public class VariableExpression implements IExpression{
    private String variable;

    public VariableExpression(String variable) {
        this.variable=variable;
    }

    @Override
    public IValue eval(IMyDictionary<String, IValue> map, IMyHeap<Integer, IValue> heap) throws ADTException {
        return map.getValue(variable);
    }

    @Override
    public IExpression deepcopy() {
        return new VariableExpression(this.variable);
    }

    @Override
    public IType typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException {
        return typeEnv.getValue(this.variable);
    }

    @Override
    public String toString() {
        return this.variable;
    }
}
