package com.example.a7gui.model.value;

import com.example.a7gui.model.types.IType;
import com.example.a7gui.model.types.RefType;

public class RefValue implements IValue{
    int address;
    IType locationType;

    public RefValue(int address, IType locationType) {
        this.address=address;
        this.locationType = locationType;
    }

    @Override
    public IType getType() {
        return new RefType(locationType);
    }

    public int getAddress() {
        return address;
    }

    public IType getLocationType() {
        return locationType;
    }

    @Override
    public boolean equals(IValue obj) {
        return obj instanceof RefValue && (((RefValue)obj).getAddress() == this.address && ((RefValue)obj).getLocationType().equals(this.locationType));
    }

    @Override
    public String toString() {
        return "("+this.address+","+this.locationType+")";
    }
}
