package model.statement;
import exception.ExpressionException;
import exception.KeyNotFoundException;
import exception.VariableAlreadyExists;
import model.adt.IMyDictionary;
import model.state.PrgState;
import model.types.IType;
import model.value.IValue;

public class VarDeclStatement implements IStatement{
    private String variable;
    private IType type;

    public VarDeclStatement(String variable, IType type) {
        this.variable = variable;
        this.type = type;
    }

    @Override
    public PrgState execute(PrgState prgState) throws VariableAlreadyExists{
        if (prgState.getSymTable().contains((this.variable)))
            throw new VariableAlreadyExists("Variable already exists!");
        IValue value = this.type.defaultValue();

        prgState.getSymTable().insert(this.variable, value);
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return new VarDeclStatement(this.variable, this.type.deepcopy());
    }

    @Override
    public String toString() {
        return this.type + " "+ this.variable;
    }
}
