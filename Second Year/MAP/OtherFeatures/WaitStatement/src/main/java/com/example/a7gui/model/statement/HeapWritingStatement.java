package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.expression.IExpression;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.types.RefType;
import com.example.a7gui.model.value.IValue;
import com.example.a7gui.model.value.RefValue;

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
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new HeapWritingStatement(this.var_name, this.expression.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typeVar=typeEnv.getValue(this.var_name);
        IType typeExp=this.expression.typeCheck(typeEnv);
        if(typeVar.equals(new RefType(typeExp))){
            return typeEnv;
        }
        else{
            throw new StatementException("The left side and the right side does not have the same types.");
        }
    }

    @Override
    public String toString() {
        return "write("+this.var_name+","+this.expression.toString()+")";
    }
}
