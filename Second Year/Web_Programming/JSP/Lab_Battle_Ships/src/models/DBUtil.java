package models;

import java.sql.*;

public class DBUtil {

    private static final String DB_URL = "jdbc:mysql://localhost/ships_db";
    private static final String DB_USER = "root";
    private static final String DB_PASS = "";

    public static Connection getConnection() throws SQLException, ClassNotFoundException {
        Class.forName("com.mysql.cj.jdbc.Driver");
        return DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
    }

    public static boolean validateUser(String username, String password) {
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement("SELECT * FROM users WHERE username=? AND password=?")) {
            ps.setString(1, username);
            ps.setString(2, password);
            ResultSet rs = ps.executeQuery();
            return rs.next();
        } catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void LoginUser(String username){
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement("INSERT INTO players (username) VALUES (?)")){
            ps.setString(1, username);
            ps.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static boolean areTwoPlayersReady() {
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement("SELECT COUNT(*) FROM players");
             ResultSet rs = ps.executeQuery()) {
            rs.next();
            return rs.getInt(1) == 2;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static int getShipCount(String username) throws Exception {
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement("SELECT COUNT(*) FROM ships WHERE username=?")) {
            ps.setString(1, username);
            ResultSet rs = ps.executeQuery();
            rs.next();
            return rs.getInt(1);
        }
    }

    public static void placeShip(String username, int x, int y) throws Exception {
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement("INSERT INTO ships (username, x, y) VALUES (?, ?, ?)")) {
            ps.setString(1, username);
            ps.setInt(2, x);
            ps.setInt(3, y);
            ps.executeUpdate();
        }
    }

    public static String getOpponent(String currentUser) throws SQLException, ClassNotFoundException {
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement("SELECT username FROM players WHERE username != ?")) {
            ps.setString(1, currentUser);
            ResultSet rs = ps.executeQuery();
            if (rs.next()) return rs.getString("username");
        }
        return null;
    }

    public static boolean attack(String attacker, String opponent, int x, int y) throws Exception {
        try (Connection con = getConnection()) {
            boolean hit;
            try (PreparedStatement ps = con.prepareStatement(
                    "SELECT * FROM ships WHERE username = ? AND x = ? AND y = ?")) {
                ps.setString(1, opponent);
                ps.setInt(2, x);
                ps.setInt(3, y);
                ResultSet rs = ps.executeQuery();
                hit = rs.next();
            }

            try (PreparedStatement ps = con.prepareStatement(
                    "INSERT INTO game_moves (username, target_x, target_y, result) VALUES (?, ?, ?, ?)")) {
                ps.setString(1, attacker);
                ps.setInt(2, x);
                ps.setInt(3, y);
                ps.setString(4, hit ? "hit" : "miss");
                ps.executeUpdate();
            }

            if (hit) {
                try (PreparedStatement ps = con.prepareStatement(
                        "DELETE FROM ships WHERE username = ? AND x = ? AND y = ?")) {
                    ps.setString(1, opponent);
                    ps.setInt(2, x);
                    ps.setInt(3, y);
                    ps.executeUpdate();
                }
            }

            return hit;
        }
    }

    public static int getRemainingShips(String username) throws Exception {
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement("SELECT COUNT(*) FROM ships WHERE username = ?")) {
            ps.setString(1, username);
            ResultSet rs = ps.executeQuery();
            rs.next();
            return rs.getInt(1);
        }
    }

    public static void clearGame() throws Exception {
        try (Connection con = getConnection()) {
            con.setAutoCommit(false);
            con.prepareStatement("DELETE FROM game_moves").executeUpdate();
            con.prepareStatement("DELETE FROM ships").executeUpdate();
            con.prepareStatement("DELETE FROM players").executeUpdate();
            con.commit();
        }
    }

    public static String getPlayerStats(String username) throws Exception {
        try (Connection con = getConnection();
             PreparedStatement ps = con.prepareStatement(
                     "SELECT result, COUNT(*) as total FROM game_moves WHERE username = ? GROUP BY result")) {
            ps.setString(1, username);
            ResultSet rs = ps.executeQuery();
            StringBuilder json = new StringBuilder("{");
            while (rs.next()) {
                json.append("\"").append(rs.getString("result")).append("\":").append(rs.getInt("total")).append(",");
            }
            if (json.charAt(json.length() - 1) == ',') json.setLength(json.length() - 1);
            json.append("}");
            return json.toString();
        }
    }
}
