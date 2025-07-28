package models;
import domain.*;

import java.sql.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class DBUtil {
    private Statement stmt;
    private Connection conn;

    public DBUtil() {
        connect();
    }

    public void connect() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            this.conn = DriverManager.getConnection("jdbc:mysql://localhost/calculator_db", "root", "");
            this.stmt = conn.createStatement();
        } catch (Exception ex) {
            System.out.println("Error Connecting to Database" + ex.getMessage());
            ex.printStackTrace();
        }
    }

    public User authenticate(String username, int password) {
        ResultSet rs;
        User user = null;
        String query = "SELECT * FROM users WHERE username=? AND password=?";

        try (PreparedStatement ps = conn.prepareStatement(query)) {
            ps.setString(1, username);
            ps.setInt(2, password);

            rs = ps.executeQuery();
            if (rs.next()) {
                user = new User(rs.getInt("id"), rs.getString("username"), rs.getInt("password"));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return user;
    }

    public List<Room> getRoomsByDates(Date checkIn, Date checkOut) {
        List<Room> rooms = new ArrayList<>();
        ResultSet rs;
        String query = "SELECT r.id, r.number, r.capacity, r.price " +
                "FROM rooms r LEFT JOIN reservations re ON r.id = re.r_id " +
                "WHERE NOT(re.check_in <= ? AND re.check_out >= ?) OR (re.check_in IS NULL AND re.check_out IS NULL)";
        try {
            PreparedStatement ps = conn.prepareStatement(query);
            ps.setDate(1, checkOut);
            ps.setDate(2, checkIn);

            rs = ps.executeQuery();
            while (rs.next()) {
                rooms.add(new Room(rs.getInt("id"), rs.getString("number"), rs.getInt("capacity"), rs.getInt("price")));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return rooms;
    }

    public boolean addReservation(Reservation reservation){
        int r=0;
        String insert_query = "INSERT INTO reservations (u_id, r_id, check_in, check_out, guests, price) VALUES(?,?, ?, ?, ?, ?)";
        try {
            PreparedStatement ps1 = conn.prepareStatement(insert_query);
            ps1.setInt(1, reservation.getuId());
            ps1.setInt(2, reservation.getrId());
            ps1.setDate(3, reservation.getCheckIn());
            ps1.setDate(4,  reservation.getCheckOut());
            ps1.setInt(5, reservation.getGuests());
            ps1.setInt(6, reservation.getPrice());
            r = ps1.executeUpdate() ;

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return r > 0;
    }

    public int getPrice(Date checkIn, Date checkOut, int roomId){
        ResultSet rs;
        String select_price = "SELECT price FROM rooms WHERE id=?";
        String free_rooms =  "SELECT COUNT(*) AS free " +
                "FROM rooms r LEFT JOIN reservations re ON r.id = re.r_id " +
                "WHERE NOT(re.check_in <= ? AND re.check_out >= ?) OR (re.check_in IS NULL AND re.check_out IS NULL)";
        String total_rooms =  "SELECT COUNT(*) AS total FROM rooms ";

        try{
            PreparedStatement ps = conn.prepareStatement(select_price);
            ps.setInt(1, roomId);
            rs = ps.executeQuery();

            if(rs.next()){
                int base_price = rs.getInt("price");

                ResultSet rs1;
                ResultSet rs2;

                PreparedStatement ps1 = conn.prepareStatement(free_rooms);
                ps1.setDate(1, checkOut);
                ps1.setDate(2, checkIn);
                rs1 = ps1.executeQuery();


                PreparedStatement ps2 = conn.prepareStatement(total_rooms);
                rs2 = ps2.executeQuery();
                if (rs1.next() && rs2.next()) {
                    int free = rs1.getInt("free");
                    int total = rs2.getInt("total");
                    float result = (float) (total - free) / total;
                    if (result <= 0.5) {
                        return base_price;
                    } else if (result > 0.5 && result <= 0.8) {
                        return (int) (base_price + 0.2 * base_price);
                    } else {
                        return (int) (base_price + 0.5 * base_price);
                    }
                }
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return 0;
    }

    public Document getDocumentByName(String name){
        Document document = null;
        ResultSet rs;

        String query = "SELECT * FROM documents WHERE name=?";
        try{
            PreparedStatement ps = conn.prepareStatement(query);
            ps.setString(1, name);

            rs = ps.executeQuery();
            if(rs.next()){
                document = new Document(rs.getInt("id"), rs.getString("name"), rs.getString("contents"));
            }
            rs.close();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return document;
    }

    public Movie getMovieByName(String title){
        Movie movie = null;
        ResultSet rs;

        String query = "SELECT * FROM movies WHERE title=?";
        try{
            PreparedStatement ps = conn.prepareStatement(query);
            ps.setString(1, title);

            rs = ps.executeQuery();
            if(rs.next()){
                movie = new Movie(rs.getInt("id"), rs.getString("title"), rs.getInt("duration"));
            }
            rs.close();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return movie;
    }

    public boolean deleteMovie(int id) throws SQLException {
        int r=0;
        String query = "DELETE FROM movies WHERE id=?";
        String select_query = "SELECT title FROM movies WHERE id=?";
        String movie_name = "";
        String select_authors = "SELECT id, movies_list FROM authors WHERE movies_list LIKE ?";
        String update_authors = "UPDATE authors SET movies_list = ? WHERE id=?";
        String new_movie_list;

        try{
            PreparedStatement ps1 = conn.prepareStatement(select_query);
            ps1.setInt(1, id);
            ResultSet res =  ps1.executeQuery();
            if(res.next()){
                movie_name = res.getString("title");
            }

            PreparedStatement ps2 = conn.prepareStatement(query);
            ps2.setInt(1, id);
            r = ps2.executeUpdate();

            PreparedStatement ps3 = conn.prepareStatement(select_authors);
            ps3.setString(1, "%" + movie_name + "%");
            ResultSet rs3 = ps3.executeQuery();

            while (rs3.next()) {
                int author_id = rs3.getInt("id");
                String movie_list = rs3.getString("movies_list");
                String finalMovie_name = movie_name;
                new_movie_list = Arrays.stream(movie_list.split(", "))
                        .filter(m->!m.equals(finalMovie_name))
                        .collect(Collectors.joining(", "));

                PreparedStatement ps4 = conn.prepareStatement(update_authors);
                ps4.setString(1, new_movie_list);
                ps4.setInt(2, author_id);
                ps4.executeUpdate();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return r > 0;
    }

    public Author getAuthorById(int id){
        Author a = null;
        ResultSet rs;
        String query = "SELECT * FROM authors WHERE id=?";

        try{
            PreparedStatement ps = conn.prepareStatement(query);
            ps.setInt(1, id);
            rs = ps.executeQuery();

            if(rs.next()){
                a = new Author(rs.getInt("id"), rs.getString("name"), rs.getString("document_list"), rs.getString("movies_list"));
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return a;
    }

    public Document getBestDocument(){
        Document document = null;
        ResultSet rs1;
        ResultSet rs2;
        String select_docs = "SELECT * FROM documents";
        String select_authors = "SELECT COUNT(*) AS count FROM authors WHERE document_list LIKE ?";
        int max=0;

        try{
            PreparedStatement ps1 = conn.prepareStatement(select_docs);
            rs1 = ps1.executeQuery();

            while(rs1.next()){
                int count=0;
                PreparedStatement ps2 = conn.prepareStatement(select_authors);
                String name = rs1.getString("name");
                ps2.setString(1, "%" + name + "%");
                rs2 = ps2.executeQuery();
                if (rs2.next()) {
                    count = rs2.getInt("count");
                    if (count > max) {
                        max = count;
                        document = new Document(rs1.getInt("id"), rs1.getString("name"), rs1.getString("contents"));
                    }
                }
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return document;
    }
}
