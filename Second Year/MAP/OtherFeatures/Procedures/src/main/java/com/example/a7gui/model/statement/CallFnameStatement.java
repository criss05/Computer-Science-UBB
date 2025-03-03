package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.adt.MySymTable;
import com.example.a7gui.model.expression.IExpression;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.value.IValue;

import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class CallFnameStatement implements IStatement{
    private List<IExpression> expressions;
    private String procName;

    public CallFnameStatement(List<IExpression> expressions, String procName) {
        this.expressions = expressions;
        this.procName = procName;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        if(!prgState.getProcTable().contains(this.procName)){
            throw new StatementException("Call: The procedure is not declared.");
        }
        List<String> params = prgState.getProcTable().getValue(this.procName).getKey();
        IStatement statement = prgState.getProcTable().getValue(this.procName).getValue();
        MySymTable<String, IValue> newSymTable = new MySymTable<>();
        for(int i=0; i<params.size(); i++){
            IValue value = expressions.get(i).eval(prgState.getCurrentSymTable(), prgState.getHeap());
            newSymTable.insert(params.get(i), value);
        }
        prgState.getSymTableStack().push(newSymTable);
        prgState.setCurrentSymTable();
        prgState.getExeStack().push(new ReturnStatement());
        prgState.getExeStack().push(statement);
        return null;
    }

    @Override
    public IStatement deepcopy() {
        List<IExpression> exps = new ArrayList<>();
        for(IExpression e: expressions){
            exps.add(e.deepcopy());
        }
        return new CallFnameStatement(exps, procName);
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        return typeEnv;
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        for(IExpression e: expressions){
            str.append(e).append(", ");
        }
        return "call " + this.procName + "( " + str + ")";
    }
}
