package model.types;

import model.value.IValue;
import model.value.IntValue;

public class IntType implements IType{
    @Override
    public boolean equals(IType obj) {
        return obj instanceof IntType;
    }

    @Override
    public String toString() {
        return "int";
    }
    @Override
    public IValue defaultValue(){
        return new IntValue(0);
    }

    @Override
    public IType deepcopy() {
        return new IntType();
    }
}
