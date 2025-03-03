package model.statement;

import exception.ExpressionException;
import exception.KeyNotFoundException;
import exception.StatementException;
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
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "NopStatement";
    }
}
