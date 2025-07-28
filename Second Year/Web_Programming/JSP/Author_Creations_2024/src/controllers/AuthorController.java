package controllers;

import domain.Author;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import models.DBUtil;

import java.io.IOException;

@WebServlet("/AuthorController")
public class AuthorController extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("application/json");

        String action = request.getParameter("action");
        if((action != null) && (action.equals("UpdateSessionAuthor"))) {
            int id = Integer.parseInt(request.getParameter("id"));
            DBUtil db = new DBUtil();
            Author author = db.getAuthorById(id);

            HttpSession session = request.getSession();
            session.setAttribute("author", author);
        }
    }
}
