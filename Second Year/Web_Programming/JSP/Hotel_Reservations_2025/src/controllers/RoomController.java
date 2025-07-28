package controllers;

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

@WebServlet("/RoomController")
public class RoomController extends HttpServlet {

        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
            response.setContentType("application/json");
            PrintWriter out = response.getWriter();

            String action = request.getParameter("action");
            if (action != null && action.equals("getRoomsByDate")) {
                Date checkIn = Date.valueOf(request.getParameter("checkIn"));
                Date checkOut = Date.valueOf(request.getParameter("checkOut"));

                DBUtil db = new DBUtil();
                List<Room> rooms = db.getRoomsByDates(checkIn, checkOut);

                JSONArray arr = new JSONArray();
                for(Room room : rooms) {
                    JSONObject obj = new JSONObject();
                    obj.put("id", room.getId());
                    obj.put("number", room.getNumber());
                    obj.put("capacity", room.getCapacity());
                    obj.put("price", room.getPrice());
                    arr.add(obj);
                }

                out.print(arr.toJSONString());
                out.flush();

            }
//            else if (action != null && action.equals("bestDocument")) {
//                DBUtil db = new DBUtil();
//                Document document = db.getBestDocument();
//
//                JSONObject obj = new JSONObject();
//                obj.put("id", document.getId());
//                obj.put("name", document.getName());
//                obj.put("contents", document.getContent());
//
//                out.println(obj.toJSONString());
//                out.flush();
//            }
        }
}
