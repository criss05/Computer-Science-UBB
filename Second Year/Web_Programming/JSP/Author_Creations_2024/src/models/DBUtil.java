package models;
import domain.Author;
import domain.Document;
import domain.Movie;

import java.sql.*;
import java.util.Arrays;
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
            this.conn = DriverManager.getConnection("jdbc:mysql://localhost/auhtor_creation", "root", "");
            this.stmt = conn.createStatement();
        } catch (Exception ex) {
            System.out.println("Error Connecting to Database" + ex.getMessage());
            ex.printStackTrace();
        }
    }
    public Author authenticate(String author, String creation) {
        ResultSet rs;
        Author a = null;
        String query = "SELECT * FROM authors WHERE name=? AND (document_list LIKE ? OR movies_list LIKE ?)";

        try (PreparedStatement ps = conn.prepareStatement(query)) {
            ps.setString(1, author);
            ps.setString(2, "%"+creation+"%");
            ps.setString(3, "%"+creation+"%");

            rs = ps.executeQuery();
            if (rs.next()) {
                a = new Author(rs.getInt("id"), rs.getString("name"), rs.getString("document_list"), rs.getString("movies_list"));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return a;
    }

    public boolean addDocument(Author author, Document doc){
        int r=0;
        String insert_query = "INSERT INTO documents (name, contents)VALUES(?,?)";
        String update_query = "UPDATE authors SET document_list=CONCAT(document_list, ', ', ?) WHERE id=?";
        try {
            PreparedStatement ps1 = conn.prepareStatement(insert_query);
            ps1.setString(1, doc.getName());
            ps1.setString(2, doc.getContent());

            PreparedStatement ps2 = conn.prepareStatement(update_query);
            ps2.setString(1, doc.getName());
            ps2.setString(2, Integer.toString(author.getId()));

            r = ps1.executeUpdate() + ps2.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return r > 1;
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
