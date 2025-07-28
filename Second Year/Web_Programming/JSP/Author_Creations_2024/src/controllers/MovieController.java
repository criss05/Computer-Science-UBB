package controllers;

import domain.Document;
import domain.Movie;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import models.DBUtil;
import org.json.simple.JSONObject;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;

@WebServlet("/MovieController")
public class MovieController extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("application/json");
        PrintWriter out = response.getWriter();

        String action = request.getParameter("action");
        if (action != null && action.equals("getByName")) {
            String title = request.getParameter("title");

            DBUtil db = new DBUtil();
            Movie movie = db.getMovieByName(title);

            JSONObject obj = new JSONObject();
            obj.put("id", movie.getId());
            obj.put("title", movie.getTitle());
            obj.put("duration", movie.getDuration());

            out.println(obj.toJSONString());
            out.flush();
        }
    }

    protected void doDelete(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("application/json");
        PrintWriter out = response.getWriter();

        int id = Integer.parseInt(request.getParameter("id"));
        DBUtil db = new DBUtil();
        boolean result = false;
        try {
            result = db.deleteMovie(id);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        JSONObject obj = new JSONObject();
        obj.put("success", result);

        out.println(obj.toJSONString());
        out.flush();
    }
}
