package model.statement;
import exception.ExpressionException;
import exception.KeyNotFoundException;
import exception.StatementException;
import model.adt.IMyDictionary;
import model.state.PrgState;
import model.types.IType;

public class CompStatement implements  IStatement{
    private IStatement statement1;
    private IStatement statement2;

    public CompStatement(IStatement statement1, IStatement statement2){
        this.statement1=statement1;
        this.statement2=statement2;
    }

    @Override
    public PrgState execute(PrgState prgState){
        prgState.getExeStack().push(this.statement2);
        prgState.getExeStack().push(this.statement1);
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new CompStatement(this.statement1.deepcopy(), this.statement2.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        return statement2.typeCheck(statement1.typeCheck(typeEnv));
    }

    @Override
    public String toString() {
        return this.statement1.toString() + "; " + this.statement2.toString();
    }
}
