package controllers;

import domain.Author;
import domain.Document;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import models.DBUtil;
import org.json.simple.JSONObject;

import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/DocumentController")
public class DocumentController extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("application/json");
        PrintWriter out = response.getWriter();

        String name = request.getParameter("name");
        String contents = request.getParameter("contents");
        int id = Integer.parseInt(request.getParameter("id"));
        String author_name = request.getParameter("author_name");
        String document_list = request.getParameter("document_list");
        String movies_list = request.getParameter("movies_list");

        Author author = new Author(id, author_name, document_list, movies_list);
        Document document = new Document(0, name, contents);

        DBUtil db = new DBUtil();
        boolean result = db.addDocument(author, document);

        JSONObject obj = new JSONObject();
        obj.put("success", result);

        out.println(obj.toJSONString());
        out.flush();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("application/json");
        PrintWriter out = response.getWriter();

        String action = request.getParameter("action");
        if(action!=null && action.equals("getByName")) {
            String name = request.getParameter("name");

            DBUtil db = new DBUtil();
            Document document = db.getDocumentByName(name);

            JSONObject obj = new JSONObject();
            obj.put("id", document.getId());
            obj.put("name", document.getName());
            obj.put("content", document.getContent());

            out.println(obj.toJSONString());
            out.flush();
        }
        else if(action!=null && action.equals("bestDocument")) {
            DBUtil db = new DBUtil();
            Document document = db.getBestDocument();

            JSONObject obj = new JSONObject();
            obj.put("id", document.getId());
            obj.put("name", document.getName());
            obj.put("contents", document.getContent());

            out.println(obj.toJSONString());
            out.flush();
        }
    }
}
