package com.example.a7gui.model.statement;

import com.example.a7gui.exception.*;
import com.example.a7gui.model.adt.*;
import com.example.a7gui.model.state.PrgState;
import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.value.IValue;
import com.example.a7gui.model.value.StringValue;

import java.io.BufferedReader;

public class ForkStatement implements IStatement{
    private IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, VariableAlreadyExists {
        IMyStack<IStatement> exeStack = new MyExeStack<>();
        exeStack.push(this.statement);
        IMyDictionary<String, IValue> symTable = prgState.getSymTable().deepcopy();
        IMyHeap<Integer, IValue> heap = prgState.getHeap();
        IMyDictionary<StringValue, BufferedReader> fileTable = prgState.getFileTable();
        IMyList<String> output = prgState.getOutput();

        PrgState prgState1 = new PrgState(this.statement);
        prgState1.setExeStack(exeStack);
        prgState1.setSymTable(symTable);
        prgState1.setHeap(heap);
        prgState1.setFileTable(fileTable);
        prgState1.setOutput(output);

        return prgState1;
    }

    @Override
    public IStatement deepcopy() {
        return new ForkStatement(this.statement.deepcopy());
    }

    @Override
    public IMyDictionary<String, IType> typeCheck(IMyDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        this.statement.typeCheck(typeEnv.deepcopy());
        return typeEnv;
    }

    @Override
    public String toString() {
        return "fork("+this.statement+")";
    }
}
