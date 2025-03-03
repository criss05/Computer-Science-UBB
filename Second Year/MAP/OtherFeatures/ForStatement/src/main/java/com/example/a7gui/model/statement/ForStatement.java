package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.expression.IExpression;
import com.example.a7gui.model.expression.RelationalExpression;
import com.example.a7gui.model.expression.RelationalOperator;
import com.example.a7gui.model.expression.VariableExpression;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.types.IntType;
import com.example.a7gui.model.value.IValue;

public class ForStatement implements IStatement{
    private String var;
    private IExpression exp1;
    private IExpression exp2;
    private IExpression exp3;
    private IStatement statement;

    public ForStatement(String var,IExpression exp1, IExpression exp2, IExpression exp3, IStatement statement) {
        this.var=var;
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.exp3 = exp3;
        this.statement=statement;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        IStatement st = new VarDeclStatement(this.var, new IntType());
        st.execute(prgState);
        IValue value1 = this.exp1.eval(prgState.getSymTable(), prgState.getHeap());
        IValue value2 = this.exp2.eval(prgState.getSymTable(), prgState.getHeap());
        IValue value3 = this.exp3.eval(prgState.getSymTable(), prgState.getHeap());

        if(!value1.getType().equals(new IntType())){
            throw new StatementException("For statement: first expression is not int.");
        }
        if(!value2.getType().equals(new IntType())){
            throw new StatementException("For statement: second expression is not int.");
        }
        if(!value3.getType().equals(new IntType())){
            throw new StatementException("For statement: third expression is not int.");
        }

        IStatement newStatement = new CompStatement(new AssignmentStatement(this.var, this.exp1),
                        new WhileStatement(new RelationalExpression(new VariableExpression(this.var), RelationalOperator.LESS, this.exp2), new CompStatement(this.statement, new AssignmentStatement(this.var, this.exp3))));
        prgState.getExeStack().push(newStatement);
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new ForStatement(this.var,this.exp1.deepcopy(), this.exp2.deepcopy(), this.exp3.deepcopy(), this.statement.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        typeEnv.insert(this.var, new IntType());
        IType typeExp1 = this.exp1.typeCheck(typeEnv);
        IType typeExp2 = this.exp2.typeCheck(typeEnv);
        IType typeExp3 = this.exp3.typeCheck(typeEnv);
        if(typeExp1.equals(new IntType()) && typeExp2.equals(new IntType()) && typeExp3.equals(new IntType())) {
            return typeEnv;
        }
        throw new StatementException("For statement: the expressions don't have int type.");
    }

    @Override
    public String toString() {
        return "for("+ this.var +"=" + this.exp1 + "; "+ this.var + "<" + this.exp2 + "; " + this.var + "=" + this.exp3 +')' + this.statement;
    }
}
