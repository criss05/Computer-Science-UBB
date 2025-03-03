package model.statement;

import model.state.PrgState;

public class NopStatement implements IStatement {
    @Override
    public PrgState execute(PrgState prgState) {
        return prgState;
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
