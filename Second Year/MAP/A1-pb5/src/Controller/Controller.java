package Controller;
import Model.IEntity;
import Model.MyException;
import Repository.IRepo;

public class Controller {
    private IRepo repo;
    public Controller(IRepo repo){
        this.repo=repo;
    }

    public void writeEntity(IEntity e){
        try{
            this.repo.writeEntity(e);
        }catch(MyException exception){
            System.out.println(exception.getMessage());
        }
    }
    public IEntity readEntity(int i){
        try {
            return this.repo.readEntity(i);
        }catch(MyException e){
            System.out.println(e.getMessage());
        }
        return null;
    }
    public IEntity[] GetOlderTrees(int max_age){
        IEntity[] list=repo.getAll();
        IEntity[] new_list=new IEntity[list.length];
        int index=0;
        for(IEntity e: list){
            if(e!=null && e.AboveAge(max_age)) {
                new_list[index] = e;
                index++;
            }
        }
        return new_list;
    }
}
