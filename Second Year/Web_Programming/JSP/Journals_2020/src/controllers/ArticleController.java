package controllers;

import domain.Article;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import models.DBUtil;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

@WebServlet("/ArticleController")
public class ArticleController extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("application/json");
        PrintWriter out = response.getWriter();

        String action = request.getParameter("action");
        if((action != null) && (action.equals("getArticlesByUserAndJournal"))) {
            String user = request.getParameter("user");
            String journal = request.getParameter("journal");
            DBUtil db = new DBUtil();

            List<Article> articles = db.getArticlesByUserAndJournal(user, journal);

            JSONArray arr = new JSONArray();
            for(Article article : articles) {
                JSONObject obj = new JSONObject();
                obj.put("id", article.getId());
                obj.put("user", article.getUser());
                obj.put("j_id", article.getJ_id());
                obj.put("summary", article.getSummary());
                obj.put("date", article.getDate().toString());
                arr.add(obj);
            }

            out.print(arr.toJSONString());
            out.flush();
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("application/json");
        PrintWriter out = response.getWriter();

        String journal = request.getParameter("journal");
        String user = request.getParameter("user");
        String summary = request.getParameter("summary");

        DBUtil db = new DBUtil();
        Article article = db.addArticle(journal, user, summary);

        JSONObject obj = new JSONObject();
        obj.put("id", article.getId());
        obj.put("user", article.getUser());
        obj.put("j_id", article.getJ_id());
        obj.put("summary", article.getSummary());
        obj.put("date", article.getDate().toString());

        out.print(obj.toJSONString());
        out.flush();
    }

}
