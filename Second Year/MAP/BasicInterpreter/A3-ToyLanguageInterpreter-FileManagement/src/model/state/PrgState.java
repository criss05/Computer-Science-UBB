package model.state;
import model.adt.*;
import model.statement.IStatement;
import model.value.IValue;
import model.value.StringValue;

import java.io.BufferedReader;

public class PrgState {
    private IMyDictionary<String, IValue> symTable;
    private IMyStack<IStatement> exeStack;
    private IMyList<String> output;
    private IStatement originalProgram;
    private IMyDictionary<StringValue, BufferedReader> fileTable;

    public PrgState(IStatement originalProgram) {
        this.originalProgram = originalProgram;
        init();
    }

    public IMyDictionary<String, IValue> getSymTable(){
        return this.symTable;
    }

    public void setSymTable(IMyDictionary<String, IValue> symTable) {
        this.symTable = symTable;
    }

    public IMyStack<IStatement> getExeStack() {
        return this.exeStack;
    }

    public void setExeStack(IMyStack<IStatement> exeStack) {
        this.exeStack = exeStack;
    }

    public IMyList<String> getOutput() {
        return this.output;
    }

    public void setOutput(IMyList<String> output) {
        this.output = output;
    }

    public IMyDictionary<StringValue, BufferedReader> getFileTable() {
        return this.fileTable;
    }

    public void setFileTable(IMyDictionary<StringValue, BufferedReader> fileTable) {
        this.fileTable = fileTable;
    }

    public String toString(){
        return this.exeStack+"\n"+this.symTable+"\n"+this.output+"\n"+this.fileTable+"\n----------------------------------------------------------------------";
    }

    public void init(){
        this.exeStack = new MyStack<>();
        this.symTable = new MyDictionary<>();
        this.output = new MyList<>();
        this.fileTable = new MyFileTable<>();
        exeStack.push(this.originalProgram);
        originalProgram = originalProgram.deepcopy();
    }
}