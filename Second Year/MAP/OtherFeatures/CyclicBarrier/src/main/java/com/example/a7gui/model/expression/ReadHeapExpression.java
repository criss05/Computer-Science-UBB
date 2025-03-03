package com.example.a7gui.model.expression;

import com.example.a7gui.exception.ADTException;
import com.example.a7gui.exception.ExpressionException;
import com.example.a7gui.exception.KeyNotFoundException;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.adt.IMyHeap;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.types.RefType;
import com.example.a7gui.model.value.IValue;
import com.example.a7gui.model.value.RefValue;


public class ReadHeapExpression implements IExpression{
    private IExpression expression;

    public ReadHeapExpression(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public IValue eval(IMyDictionary<String, IValue> map, IMyHeap<Integer, IValue> heap) throws ExpressionException, ADTException {
        IValue value = this.expression.eval(map, heap);
        if(!(value instanceof RefValue)){
            throw new ExpressionException("The type of the expression must be RefType!");
        }
        Integer addr = ((RefValue) value).getAddress();
        if(!heap.contains(addr)){
            throw new ExpressionException("The address of this value is not in the heap.");
        }
        return heap.getValue(addr);
    }

    @Override
    public IExpression deepcopy() {
        return new ReadHeapExpression(this.expression.deepcopy());
    }

    @Override
    public IType typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException {
        IType type=this.expression.typeCheck(typeEnv);
        if (type instanceof RefType){
            return ((RefType) type).getInner();
        }
        else{
            throw new ExpressionException("The expression is not of type Ref");
        }
    }

    @Override
    public String toString() {
        return "read("+this.expression.toString()+")";
    }
}
