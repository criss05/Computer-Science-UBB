package model.statement;

import exception.ExpressionException;
import exception.KeyNotFoundException;
import model.adt.IMyDictionary;
import model.state.PrgState;
import model.types.IType;

public class NopStatement implements IStatement {
    @Override
    public PrgState execute(PrgState prgState) {
        return null;
    }

    @Override
    public IStatement deepcopy() {
        return null;
    }



    @Override
    public String toString() {
        return "NopStatement";
    }
}
