package models;
import domain.Article;

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
            this.conn = DriverManager.getConnection("jdbc:mysql://localhost/journals_db", "root", "");
            this.stmt = conn.createStatement();
        } catch (Exception ex) {
            System.out.println("Error Connecting to Database" + ex.getMessage());
            ex.printStackTrace();
        }
    }

    public List<Article> getArticlesByUserAndJournal(String user, String journal) {
        List<Article> articles = new ArrayList<>();
        ResultSet rs;
        String query = "SELECT a.id, a.user, a.j_id, a.summary, a.date " +
                "FROM articles a INNER JOIN journals j ON a.j_id = j.id " +
                "WHERE a.user = ? and j.name=?";
        try {
            PreparedStatement ps = conn.prepareStatement(query);
            ps.setString(1, user);
            ps.setString(2, journal);

            rs = ps.executeQuery();
            while (rs.next()) {
                articles.add(new Article(rs.getInt("id"), rs.getDate("date"), rs.getString("summary"), rs.getInt("j_id"), rs.getString("user")));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return articles;
    }

    public Article addArticle(String journal, String user, String summary){
        String insert_journal = "INSERT INTO journals (name) VALUES (?)";
        String insert_article = "INSERT INTO articles (user, j_id, summary)VALUES(?, ?, ?)";
        String select_journal = "SELECT id FROM journals WHERE name = ?";
        String select_article = "SELECT * FROM articles WHERE id = ?";
        Article article = null;
        int j_id = -1;
        ResultSet key_a = null;
        try{
            PreparedStatement ps1 = conn.prepareStatement(select_journal);
            ps1.setString(1, journal);
            ResultSet rs1 = ps1.executeQuery();

            if(rs1.next()) {
                j_id = rs1.getInt("id");
                PreparedStatement ps2 = conn.prepareStatement(insert_article, Statement.RETURN_GENERATED_KEYS);
                ps2.setString(1, user);
                ps2.setInt(2, j_id);
                ps2.setString(3, summary);
                ps2.executeUpdate();
                key_a = ps2.getGeneratedKeys();
            }
            else{
                PreparedStatement ps2 = conn.prepareStatement(insert_journal, Statement.RETURN_GENERATED_KEYS);
                ps2.setString(1, journal);
                int res = ps2.executeUpdate();

                if(res>0){
                    ResultSet key = ps2.getGeneratedKeys();
                    if(key.next()){
                        j_id = key.getInt(1);
                        PreparedStatement ps3 = conn.prepareStatement(insert_article, Statement.RETURN_GENERATED_KEYS);
                        ps3.setString(1, user);
                        ps3.setInt(2, j_id);
                        ps3.setString(3, summary);
                        ps3.executeUpdate();
                        key_a = ps3.getGeneratedKeys();
                    }
                }
            }

            if(key_a != null) {
                if(key_a.next()) {
                    PreparedStatement ps4 = conn.prepareStatement(select_article);
                    ps4.setInt(1, key_a.getInt(1));
                    ResultSet res = ps4.executeQuery();
                    if(res.next()) {
                        article = new Article(res.getInt("id"), res.getDate("date"), res.getString("summary"), res.getInt("j_id"), res.getString("user"));
                    }
                }

            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return article;
    }
}
