package model.types;

import model.value.BoolValue;
import model.value.IValue;

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
