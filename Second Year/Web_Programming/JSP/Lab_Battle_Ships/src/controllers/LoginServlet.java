package controllers;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import models.DBUtil;
import models.GameState;

import java.io.IOException;

@WebServlet("/LoginServlet")
public class LoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (DBUtil.validateUser(username, password)) {
            HttpSession session = request.getSession(true);
            session.setAttribute("username", username);

            if (GameState.addPlayer(username)){
                DBUtil.LoginUser(username);
                response.sendRedirect("waiting.jsp");
            } else {
                session.invalidate();
                request.setAttribute("error", "Only 2 players are allowed.");
                request.getRequestDispatcher("error.jsp").forward(request, response);
            }
        } else{
            request.setAttribute("error", "Invalid username or password.");
            request.getRequestDispatcher("login.jsp").forward(request, response);
        }
    }
}
