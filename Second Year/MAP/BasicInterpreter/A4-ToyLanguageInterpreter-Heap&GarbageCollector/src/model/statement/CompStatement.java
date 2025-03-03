package model.statement;
import model.state.PrgState;

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
        return prgState;
    }

    @Override
    public IStatement deepcopy() {
        return new CompStatement(this.statement1.deepcopy(), this.statement2.deepcopy());
    }

    @Override
    public String toString() {
        return this.statement1.toString() + "; " + this.statement2.toString();
    }
}
