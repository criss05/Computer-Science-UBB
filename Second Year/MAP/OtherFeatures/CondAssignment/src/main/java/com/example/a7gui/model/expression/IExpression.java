package com.example.a7gui.model.expression;

import com.example.a7gui.exception.ADTException;
import com.example.a7gui.exception.ExpressionException;
import com.example.a7gui.exception.KeyNotFoundException;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.adt.IMyHeap;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.value.IValue;

public interface IExpression {
    IValue eval(IMyDictionary<String, IValue> map, IMyHeap<Integer, IValue>heap) throws ExpressionException, ADTException;
    String toString();
    IExpression deepcopy();
    IType typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException,ExpressionException;
}
