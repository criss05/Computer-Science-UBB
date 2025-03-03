package model.value;

import model.types.IType;

public interface IValue {
    IType getType();
    boolean equals(IValue obj);
    String toString();
}
