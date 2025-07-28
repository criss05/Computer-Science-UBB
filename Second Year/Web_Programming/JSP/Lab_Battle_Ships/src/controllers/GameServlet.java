package controllers;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import models.DBUtil;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/GameServlet")
public class GameServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");
        response.setContentType("application/json");
        PrintWriter out = response.getWriter();

        if ("checkPlayers".equals(action)) {
            boolean ready = DBUtil.areTwoPlayersReady();
            out.println("{\"ready\": " + ready + "}");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");
        HttpSession session = request.getSession(false);
        String username = (String) session.getAttribute("username");
        response.setContentType("application/json");
        PrintWriter out = response.getWriter();

        try {
            if (!DBUtil.areTwoPlayersReady()) {
                DBUtil.clearGame();
            }
            switch (action) {
                case "place":
                    int x = Integer.parseInt(request.getParameter("x"));
                    int y = Integer.parseInt(request.getParameter("y"));

                    if (DBUtil.getShipCount(username) >= 2) {
                        out.print("{\"status\":\"error\", \"message\":\"Max 2 ships allowed.\"}");
                        return;
                    }

                    DBUtil.placeShip(username, x, y);
                    out.print("{\"status\":\"ok\"}");
                    break;

                case "attack":
                    int tx = Integer.parseInt(request.getParameter("x"));
                    int ty = Integer.parseInt(request.getParameter("y"));

                    String opponent = DBUtil.getOpponent(username);
                    if (opponent == null) {
                        out.print("{\"status\":\"error\", \"message\":\"No opponent.\"}");
                        return;
                    }

                    boolean hit = DBUtil.attack(username, opponent, tx, ty);
                    int remaining = DBUtil.getRemainingShips(opponent);

                    if (remaining == 0) {
                        DBUtil.clearGame();
                        out.print("{\"status\":\"ok\", \"result\":\"hit\", \"gameOver\":true, \"message\":\"You won!\"}");
                    } else {
                        out.print("{\"status\":\"ok\", \"result\":\"" + (hit ? "hit" : "miss") + "\"}");
                    }

                    if (!DBUtil.areTwoPlayersReady()) {

                    }
                    break;

                case "status":
                    String json = DBUtil.getPlayerStats(username);
                    out.print(json);
                    break;
            }
        } catch (Exception e) {
            e.printStackTrace();
            out.print("{\"status\":\"error\",\"message\":\"" + e.getMessage() + "\"}");
        }
    }
}
