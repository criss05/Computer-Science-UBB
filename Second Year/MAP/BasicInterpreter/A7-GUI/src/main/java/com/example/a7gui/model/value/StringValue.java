package com.example.a7gui.model.value;

import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.types.StringType;

public class StringValue implements IValue{
    private String value;

    public StringValue(String value) {
        this.value = value;
    }

    @Override
    public IType getType() {
        return new StringType();
    }

    public String getValue() {
        return this.value;
    }

    public void setValue(String value) {
        this.value = value;
    }

    @Override
    public boolean equals(IValue obj) {
        return obj.getType().equals(new StringType()) && ((StringValue)obj).getValue().equals(this.value);
    }

    @Override
    public String toString() {
        return value;
    }
}
