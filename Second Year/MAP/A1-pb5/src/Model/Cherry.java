package Model;

public class Cherry implements IEntity{
    private int age;
    private int sweetness;

    public Cherry(int age, int sweetness){
        this.age=age;
        this.sweetness=sweetness;
    }
    public int GetAge(){return this.age;}
    public void SetAge(int age){this.age=age;}
    public int GetSweetness(){return this.sweetness;}
    public void SetSweetness(int sweetness){this.sweetness=sweetness;}

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof Cherry)) return false;
        return this.age == ((Cherry) obj).GetAge() && this.sweetness == ((Cherry) obj).GetSweetness();
    }

    @Override
    public String toString() {
        return "apple: age "+age+" sweetness"+sweetness;
    }

    @Override
    public boolean AboveAge(int age) {
        return this.age > age;
    }
}
