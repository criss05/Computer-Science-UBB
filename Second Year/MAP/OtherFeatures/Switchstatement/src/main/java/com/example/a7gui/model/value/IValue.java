package com.example.a7gui.model.value;

import com.example.a7gui.model.types.IType;

public interface IValue {
    IType getType();
    boolean equals(IValue obj);
    String toString();
}
