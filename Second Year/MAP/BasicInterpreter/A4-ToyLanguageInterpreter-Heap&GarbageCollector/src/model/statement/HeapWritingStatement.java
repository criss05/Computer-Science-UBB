package model.statement;
import exception.*;
import model.expression.IExpression;
import model.state.PrgState;
import model.types.IType;
import model.types.RefType;
import model.value.IValue;
import model.value.RefValue;

public class HeapWritingStatement implements IStatement {
    private String var_name;
    private IExpression expression;

    public HeapWritingStatement(String var_name, IExpression expression) {
        this.var_name = var_name;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        if (!prgState.getSymTable().contains(String.valueOf(this.var_name))) {
            throw new StatementException("The variable does not exists in the heap!");
        }

        IValue var_val=prgState.getSymTable().getValue(this.var_name);
        if (!(var_val.getType() instanceof RefType)) {
            throw new StatementException("The variable is not of type RefType.");
        }

        Integer addr = ((RefValue) var_val).getAddress();
        if(!(prgState.getHeap().contains(addr))){
            throw new StatementException("This variable is not allocated.Please allocate it first");
        }

        IValue eval_value = this.expression.eval(prgState.getSymTable(), prgState.getHeap());
        RefValue ref_value = (RefValue)var_val;
        if(!(eval_value.getType().equals(ref_value.getLocationType()))) {
            throw new StatementException("The value of your expression is not of good type. Try again!");
        }
        prgState.getHeap().update(addr, eval_value);
        return prgState;
    }

    @Override
    public IStatement deepcopy() {
        return new HeapWritingStatement(this.var_name, this.expression.deepcopy());
    }

    @Override
    public String toString() {
        return "write("+this.var_name+","+this.expression.toString()+")";
    }
}
