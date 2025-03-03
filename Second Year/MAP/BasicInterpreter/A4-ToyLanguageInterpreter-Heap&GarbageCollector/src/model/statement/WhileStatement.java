package model.statement;
import exception.ADTException;
import exception.ExpressionException;
import exception.StatementException;
import exception.VariableAlreadyExists;
import model.expression.IExpression;
import model.state.PrgState;
import model.types.BoolType;
import model.value.BoolValue;
import model.value.IValue;


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
        return prgState;
    }


    @Override
    public IStatement deepcopy() {
        return new WhileStatement(this.expression.deepcopy(), this.statement.deepcopy());
    }

    @Override
    public String toString() {
        return "While("+ this.expression+"){"+this.statement+"}";
    }
}
