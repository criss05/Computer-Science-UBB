package model.state;
import exception.ADTException;
import exception.ExpressionException;
import exception.StatementException;
import exception.VariableAlreadyExists;
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
    private IMyHeap<Integer, IValue> heap;
    private int id;
    private static int last_index;

    public PrgState(IStatement originalProgram) {
        this.originalProgram = originalProgram;
        this.id=getId();
    }

    private synchronized int getId(){
        last_index++;
        return last_index;
    }

    public IMyHeap<Integer, IValue> getHeap() {
        return heap;
    }

    public void setHeap(IMyHeap<Integer, IValue> heap) {
        this.heap = heap;
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
        return "ID:"+ this.id +this.exeStack+"\n"+this.symTable+"\n"+this.output+"\n"+this.fileTable+"\n"+this.heap+"\n----------------------------------------------------------------------";
    }

    public Boolean isNotCompleted(){
        return !this.exeStack.isEmpty();
    }

    public PrgState oneStep()throws ADTException, ExpressionException, StatementException, VariableAlreadyExists {
        if (exeStack.isEmpty()) throw new ADTException("Stack is empty.");
        IStatement statement = this.exeStack.pop();
        return statement.execute(this);
    }

    public void init(){
        this.exeStack = new MyExeStack<>();
        this.symTable = new MySymTable<>();
        this.output = new MyOutput<>();
        this.fileTable = new MyFileTable<>();
        this.heap = new MyHeap<>();
        exeStack.push(this.originalProgram);
        originalProgram = originalProgram.deepcopy();
    }
}