package controllers;

import domain.Author;
import jakarta.servlet.RequestDispatcher;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import models.DBUtil;

import java.io.IOException;

@WebServlet("/LoginController")
public class LoginController extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String authorName = request.getParameter("author");
        String creation = request.getParameter("creation");
        RequestDispatcher rd = null;

        DBUtil db = new DBUtil();
        Author author = db.authenticate(authorName, creation);
        if (author!=null) {
            rd = request.getRequestDispatcher("/home_page.jsp");
            HttpSession session = request.getSession();
            session.setAttribute("author", author);
        } else{
            rd = request.getRequestDispatcher("/error.jsp");
        }

        rd.forward(request, response);
    }
}
