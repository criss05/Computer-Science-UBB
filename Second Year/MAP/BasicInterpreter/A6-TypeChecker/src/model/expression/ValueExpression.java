package model.expression;
import exception.ExpressionException;
import exception.KeyNotFoundException;
import model.adt.IMyDictionary;
import model.adt.IMyHeap;
import model.types.IType;
import model.value.IValue;

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
