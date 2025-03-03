package com.example.a7gui.model.types;

import com.example.a7gui.model.value.BoolValue;
import com.example.a7gui.model.value.IValue;

public class BoolType implements IType{

    @Override
    public boolean equals(IType obj) {
        return obj instanceof BoolType;
    }

    @Override
    public String toString() {
        return "bool";
    }

    @Override
    public IValue defaultValue() {
        return new BoolValue(false);
    }

    @Override
    public IType deepcopy() {
        return new BoolType();
    }
}
