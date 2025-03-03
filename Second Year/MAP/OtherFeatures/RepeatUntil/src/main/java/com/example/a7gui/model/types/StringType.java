package com.example.a7gui.model.types;

import com.example.a7gui.model.value.IValue;
import com.example.a7gui.model.value.StringValue;

public class StringType implements IType{
    @Override
    public boolean equals(IType obj) {
        return obj instanceof StringType;
    }

    @Override
    public IValue defaultValue() {
        return new StringValue("");
    }

    @Override
    public IType deepcopy() {
        return new StringType();
    }

    @Override
    public String toString() {
        return "String";
    }
}
