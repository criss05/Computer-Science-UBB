package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.expression.IExpression;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.value.IValue;

import javax.management.relation.InvalidRoleValueException;


public class SwitchStatement implements IStatement {
    IExpression exp;
    IExpression exp1;
    IExpression exp2;
    IStatement statement1;
    IStatement statement2;
    IStatement statement3;

    public SwitchStatement(IExpression exp, IExpression exp1, IExpression exp2, IStatement statement1, IStatement statement2, IStatement statement3){
        this.exp=exp;
        this.exp1=exp1;
        this.exp2=exp2;
        this.statement1=statement1;
        this.statement2=statement2;
        this.statement3=statement3;
    }


    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        IValue value = this.exp.eval(prgState.getSymTable(), prgState.getHeap());
        IValue value1 =this.exp1.eval(prgState.getSymTable(), prgState.getHeap());
        IValue value2 = this.exp2.eval(prgState.getSymTable(), prgState.getHeap());
        if(!value.getType().equals(value1.getType())){
            throw new StatementException("Expression 1 does not have the same type as the initial expression.");
        }
        if(!value.getType().equals(value2.getType())){
            throw new StatementException("Expression 2 does not have the same type as the initial expression.");
        }
        if(value.equals(value1)){
            prgState.getExeStack().push(statement1);
        }
        else{
            if(value.equals(value2)) {
                prgState.getExeStack().push(statement2);
            }
            else{
                prgState.getExeStack().push(statement3);
            }
        }
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new SwitchStatement(exp.deepcopy(), exp1.deepcopy(), exp2.deepcopy(), statement1.deepcopy(), statement2.deepcopy(), statement3.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
      IType typeExp = this.exp.typeCheck(typeEnv);
      IType typeExp1 = this.exp1.typeCheck(typeEnv);
      IType typeExp2 = this.exp2.typeCheck(typeEnv);
      if(typeExp.equals(typeExp1) && typeExp.equals(typeExp2)){
          this.statement1.typeCheck(typeEnv.deepcopy());
          this.statement2.typeCheck(typeEnv.deepcopy());
          this.statement3.typeCheck(typeEnv.deepcopy());
          return typeEnv;
      }
      else{
          throw new StatementException("The expressions don't have the same type.");
      }
    }

    @Override
    public String toString() {
        return "switch( " + this.exp + " )(case (" + this.exp1 + "):" + this.statement1 + " )(case (" + this.exp2 + "): " + this.statement2 + " )(default: " +this.statement3 +")";
    }
}
