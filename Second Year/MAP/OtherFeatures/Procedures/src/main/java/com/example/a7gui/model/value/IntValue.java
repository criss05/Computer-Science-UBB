package com.example.a7gui.model.value;

import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.types.IntType;

public class IntValue implements IValue{
    private int value;

    public IntValue(int value) {
        this.value = value;
    }

    public IntValue(){
        this.value=0;
    }

    public int getValue() {
        return this.value;
    }

    @Override
    public IType getType() {
        return new IntType();
    }

    @Override
    public boolean equals(IValue obj) {
        return obj instanceof IntValue && ((IntValue)obj).getValue() == this.value;
    }

    @Override
    public String toString() {
        return String.valueOf(this.value);
    }
}
