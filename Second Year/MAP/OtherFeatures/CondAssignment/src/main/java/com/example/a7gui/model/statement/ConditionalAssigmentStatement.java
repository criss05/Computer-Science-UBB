package com.example.a7gui.model.statement;


import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.expression.IExpression;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.BoolType;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.value.IValue;

import javax.management.relation.InvalidRoleValueException;

public class ConditionalAssigmentStatement implements IStatement {
    private String var;
    private IExpression exp1;
    private IExpression exp2;
    private IExpression exp3;

    public ConditionalAssigmentStatement(String v, IExpression exp1, IExpression exp2, IExpression exp3) {
        this.var = v;
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.exp3 = exp3;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        IValue valueVar = prgState.getSymTable().getValue(this.var);
        IValue valueExp1 = this.exp1.eval(prgState.getSymTable(), prgState.getHeap());
        IValue valueExp2 = this.exp2.eval(prgState.getSymTable(), prgState.getHeap());
        IValue valueExp3 = this.exp3.eval(prgState.getSymTable(), prgState.getHeap());
        if(!valueExp1.getType().equals(new BoolType())){
            throw new StatementException("Cond Ass: the expression does not have bool type");
        }
        if(!valueVar.getType().equals(valueExp2.getType())){
            throw new StatementException("Cond Ass: variable and exp2 have different types.");
        }
        if(!valueVar.getType().equals(valueExp3.getType())){
            throw new StatementException("Cond Ass: variable and exp3 have different types.");
        }
        IStatement statement = new IfStatement(this.exp1, new AssignmentStatement("v", this.exp2), new AssignmentStatement("v", this.exp3));
        prgState.getExeStack().push(statement);
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new ConditionalAssigmentStatement(var, this.exp1.deepcopy(), this.exp2.deepcopy(), this.exp3.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typeVar = typeEnv.getValue(this.var);
        IType typeExp1 = this.exp1.typeCheck(typeEnv);
        IType typeExp2 = this.exp2.typeCheck(typeEnv);
        IType typeExp3 = this.exp3.typeCheck(typeEnv);
        if(!typeExp1.equals(new BoolType())){
            throw new StatementException("Cond ass: Exp1 doesn't have bool type.");
        }
        if(typeVar.equals(typeExp2) && typeVar.equals(typeExp3)) {
            return typeEnv;
        }
        throw new StatementException("Cond ass: variable, exp2 and exp3 don't have the same type.");
    }

    @Override
    public String toString() {
        return this.var + '='+ this.exp1 +" ? " + this.exp2 + " : " + exp3;
    }
}
