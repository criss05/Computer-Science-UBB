package controllers;

import domain.Reservation;
import domain.Room;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import models.DBUtil;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Date;
import java.util.List;

@WebServlet("/ReservationController")
public class ReservationController extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("application/json");
        PrintWriter out = response.getWriter();
        DBUtil db = new DBUtil();

        String action = request.getParameter("action");
        if (action != null && action.equals("reserveRoom")) {
            int userId = Integer.parseInt(request.getParameter("userId"));
            int roomId = Integer.parseInt(request.getParameter("roomId"));
            Date checkIn = Date.valueOf(request.getParameter("checkIn"));
            Date checkOut = Date.valueOf(request.getParameter("checkOut"));
            int guests = Integer.parseInt(request.getParameter("guests"));
            int price = db.getPrice(checkIn, checkOut, roomId);

            Reservation reservation = new Reservation(0, userId, roomId, checkIn, checkOut, guests, price);


            db.addReservation(reservation);

            JSONObject obj = new JSONObject();
            obj.put("success", "true");

            out.println(obj.toJSONString());
            out.flush();
        }
    }
}
