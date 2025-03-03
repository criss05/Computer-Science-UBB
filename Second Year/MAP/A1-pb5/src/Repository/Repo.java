package Repository;

import Model.IEntity;
import Model.MyException;

public class Repo implements IRepo{
    private IEntity[] entities;
    private int index;

    public Repo(int capacity){
        this.entities = new IEntity[capacity];
        this.index=0;
    }
    @Override
    public void writeEntity(IEntity e)throws MyException {
        if(index>=entities.length) throw new MyException("The list is full.");
        this.entities[index]=e;
        index++;
    }

    @Override
    public IEntity readEntity(int pos) throws MyException {
        if(pos<1 || pos>index) throw new MyException("The index in out of range.");
        return this.entities[pos];
    }

    @Override
    public IEntity[] getAll() {
        IEntity[] new_list = new IEntity[index];
        int pos=0;
        for(IEntity e: this.entities)
            if(e!=null){
                new_list[pos]=e;
                pos++;
            }
        return new_list;
    }
}
