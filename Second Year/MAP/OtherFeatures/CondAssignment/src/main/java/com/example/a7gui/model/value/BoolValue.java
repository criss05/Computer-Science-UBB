package com.example.a7gui.model.value;

import com.example.a7gui.model.types.BoolType;
import com.example.a7gui.model.types.IType;

public class BoolValue implements IValue{
    private boolean value;

    public BoolValue(boolean value) {
        this.value=value;
    }

    public BoolValue(){
        this.value=false;
    }

    public boolean getValue() {
        return value;
    }

    @Override
    public IType getType() {
        return new BoolType();
    }

    @Override
    public String toString() {
        return String.valueOf(this.value);
    }

    @Override
    public boolean equals(IValue obj) {
        return obj instanceof BoolValue && ((BoolValue)obj).value == this.value;
    }
}
