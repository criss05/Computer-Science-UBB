package model.expression;

import exception.ADTException;
import exception.ExpressionException;
import model.adt.IMyDictionary;
import model.adt.IMyHeap;
import model.value.IValue;
import model.value.RefValue;

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
    public String toString() {
        return "read("+this.expression.toString()+")";
    }
}
