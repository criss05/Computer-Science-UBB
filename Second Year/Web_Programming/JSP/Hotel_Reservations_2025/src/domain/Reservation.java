package domain;

import java.sql.Date;

public class Reservation {
    private int id;
    private int uId;
    private int rId;
    private Date checkIn;
    private Date checkOut;
    private int guests;
    private int price;

    public Reservation(int id, int uId, int rId, Date checkIn, Date checkOut, int guests, int price) {
        this.id = id;
        this.uId = uId;
        this.rId = rId;
        this.checkIn = checkIn;
        this.checkOut = checkOut;
        this.guests = guests;
        this.price = price;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getuId() {
        return uId;
    }

    public void setuId(int uId) {
        this.uId = uId;
    }

    public int getrId() {
        return rId;
    }

    public void setrId(int rId) {
        this.rId = rId;
    }

    public Date getCheckIn() {
        return checkIn;
    }

    public void setCheckIn(Date checkIn) {
        this.checkIn = checkIn;
    }

    public Date getCheckOut() {
        return checkOut;
    }

    public void setCheckOut(Date checkOut) {
        this.checkOut = checkOut;
    }

    public int getGuests() {
        return guests;
    }

    public void setGuests(int guests) {
        this.guests = guests;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }
}
