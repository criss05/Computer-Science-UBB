package Model;

public class Pear implements IEntity{
    private int age;
    private String type;

    public Pear(int age, String type){
        this.age=age;
        this.type=type;
    }
    public int GetAge(){return this.age;}
    public void SetAge(int age){this.age=age;}
    public String GetType(){return this.type;}
    public void SetType(String type){this.type=type;}

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof Pear)) return false;
        return this.age == ((Pear) obj).GetAge() && this.type.equals(((Pear) obj).GetType());
    }

    @Override
    public String toString() {
        return "apple: age "+age+" type"+type;
    }

    @Override
    public boolean AboveAge(int age) {
        return this.age > age;
    }
}
