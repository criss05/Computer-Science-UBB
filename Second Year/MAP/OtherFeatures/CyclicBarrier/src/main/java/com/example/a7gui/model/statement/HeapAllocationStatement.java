package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.expression.IExpression;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.types.RefType;
import com.example.a7gui.model.value.IValue;
import com.example.a7gui.model.value.RefValue;

public class HeapAllocationStatement implements IStatement{
    private String var_name;
    private IExpression expression;

    public HeapAllocationStatement(String var_name, IExpression expression) {
        this.var_name = var_name;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        if(!prgState.getSymTable().contains(this.var_name)){
            throw new ADTException("The key is not in the SymTable. You need to declare the variable first and then to allocate it!");
        }
        IValue var_value=prgState.getSymTable().getValue(this.var_name);
        if(! (var_value.getType() instanceof RefType)){
            throw new StatementException("The type of the variable is not RefType!");
        }

        IValue value = this.expression.eval(prgState.getSymTable(), prgState.getHeap());
        RefValue ref_value=(RefValue) var_value;
        if(!(value.getType().equals(ref_value.getLocationType()))) {
            throw new StatementException("The new value does not have the same type as the old one.");
        }
        Integer addr = prgState.getHeap().insert(value);
        prgState.getSymTable().insert(this.var_name, new RefValue(addr, value.getType()));
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new HeapAllocationStatement(var_name, this.expression.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typeVar=typeEnv.getValue(this.var_name);
        IType typeExp= this.expression.typeCheck(typeEnv);
        if(typeVar.equals(new RefType(typeExp))){
            return typeEnv;
        }
        else{
            throw new StatementException("The left side does not have the same type as the right side.");
        }
    }

    @Override
    public String toString() {
        return this.var_name+ "=new(" +this.expression+ ")";
    }
}
