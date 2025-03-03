package model.types;

import model.value.IValue;

public interface IType {
    boolean equals(IType obj);
    String toString();
    IValue defaultValue();
    IType deepcopy();
}
