package com.example.a7gui.model.statement;
import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.IMyDictionary;
import com.example.a7gui.model.expression.IExpression;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.BoolType;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.value.BoolValue;
import com.example.a7gui.model.value.IValue;


public class WhileStatement implements IStatement{
    IExpression expression;
    IStatement statement;

    public WhileStatement(IExpression expression, IStatement statement) {
        this.expression = expression;
        this.statement=statement;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException {
        IValue value = expression.eval(prgState.getSymTable(), prgState.getHeap());

        // Check if the value is of type BoolType
        if (!value.getType().equals(new BoolType())) {
            throw new StatementException("Condition expression is not a boolean");
        }

        BoolValue boolValue = (BoolValue) value;
        if (boolValue.getValue()) {
            prgState.getExeStack().push(this);
            prgState.getExeStack().push(statement);
        }
        return null;
    }


    @Override
    public IStatement deepcopy() {
        return new WhileStatement(this.expression.deepcopy(), this.statement.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typeExp = this.expression.typeCheck(typeEnv);
        if(typeExp.equals(new BoolType())){
            this.statement.typeCheck(typeEnv.deepcopy());
            return typeEnv;
        }
        throw new StatementException("The condition of the While is not bool");
    }

    @Override
    public String toString() {
        return "While("+ this.expression+"){"+this.statement+"}";
    }
}
