package Model;

public class Apple implements IEntity{
    private int age;
    private int height;

    public Apple(int age, int height){
        this.age=age;
        this.height=height;
    }
    public int GetAge(){return this.age;}
    public void SetAge(int age){this.age=age;}
    public int GetHeight(){return this.height;}
    public void SetHeight(int height){this.height=height;}

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof Apple)) return false;
        return this.age == ((Apple) obj).GetAge() && this.height == ((Apple) obj).GetHeight();
    }

    @Override
    public String toString() {
        return "apple: age "+age+" height"+height;
    }

    @Override
    public boolean AboveAge(int age) {
        return this.age > age;
    }
}
