import Controller.Controller;
import Model.Apple;
import Model.Cherry;
import Model.IEntity;
import Model.Pear;
import Repository.IRepo;
import Repository.Repo;


public class Main {
    public static void main(String[] args) {
        IRepo repo=new Repo(10);
        Controller controller=new Controller(repo);

        Apple a1 = new Apple(4, 20);
        Cherry c1=new Cherry(2, 5);
        Apple a2 = new Apple(8, 100);
        Pear p1=new Pear(1, " de vara");
        Cherry c2 = new Cherry(5, 10);
        Cherry c3=new Cherry(9, 12);
        Cherry c4=new Cherry(2, 4);
        Pear p2=new Pear(5, "rosii");
        Apple a3=new Apple(3, 90);
        Pear p3=new Pear(3, "verzi");
        Apple a4=new Apple(4, 30);

        controller.writeEntity(a1);
        controller.writeEntity(c1);
        controller.writeEntity(a2);
        controller.writeEntity(p1);
        controller.writeEntity(c2);
        controller.writeEntity(c3);
        controller.writeEntity(c4);
        controller.writeEntity(p2);
        controller.writeEntity(a3);
        controller.writeEntity(p3);
        controller.writeEntity(a4);

        IEntity[] entity = controller.GetOlderTrees(3);
        for(IEntity e: entity)
            if(e!=null)
                System.out.println(e);
        controller.readEntity(23);
    }
}