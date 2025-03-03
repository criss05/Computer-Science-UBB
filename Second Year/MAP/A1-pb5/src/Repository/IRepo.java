package Repository;

import Model.IEntity;
import Model.MyException;

public interface IRepo {
    public void writeEntity(IEntity e)throws MyException;
    public IEntity readEntity(int pos)throws MyException;
    public IEntity[] getAll();
}
