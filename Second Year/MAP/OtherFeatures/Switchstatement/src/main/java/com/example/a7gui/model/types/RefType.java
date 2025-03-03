package com.example.a7gui.model.types;

import com.example.a7gui.model.value.IValue;
import com.example.a7gui.model.value.RefValue;

public class RefType implements IType{
    IType inner;

    public RefType(IType inner) {
        this.inner = inner;
    }

    public IType getInner() {
        return inner;
    }

    @Override
    public boolean equals(IType obj) {
        return obj instanceof RefType && this.inner.equals(((RefType)obj).getInner());
    }

    @Override
    public IValue defaultValue() {
        return new RefValue(0, this.inner);
    }

    @Override
    public IType deepcopy() {
        return new RefType(this.inner);
    }

    @Override
    public String toString() {
        return "Ref(" + inner +')';
    }
}
