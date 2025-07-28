package controllers;

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
        String user = request.getParameter("user");
        RequestDispatcher rd = null;

        DBUtil db = new DBUtil();
        if (user!=null) {
            rd = request.getRequestDispatcher("/home_page.jsp");
            HttpSession session = request.getSession();
            session.setAttribute("user", user);
        } else{
            rd = request.getRequestDispatcher("/error.jsp");
        }

        rd.forward(request, response);
    }
}
