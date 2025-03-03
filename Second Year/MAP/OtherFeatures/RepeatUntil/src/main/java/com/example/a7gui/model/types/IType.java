package com.example.a7gui.model.types;

import com.example.a7gui.model.value.IValue;

public interface IType {
    boolean equals(IType obj);
    String toString();
    IValue defaultValue();
    IType deepcopy();
}
