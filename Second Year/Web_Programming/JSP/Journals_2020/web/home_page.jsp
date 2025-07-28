<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@page session="true"%>
<%
    String user = (String)session.getAttribute("user");
    if (user==null){
        response.sendRedirect("login.jsp");
        return;
    }
%>
<html>
<head>
    <title>Home page</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
    <h1>Welcome!</h1>
    <div style="display:flex; flex-direction: column; justify-content: space-between;">
        <button id="addArticle" onclick="AddArticle()">Add article</button>
        <button id="viewMyArticles" onclick="ViewMyArticles()">View my articles</button>
    </div>

    <script>
        function AddArticle(){
            window.location.href = "add_article.jsp";
        }

        function ViewMyArticles(){
            window.location.href = "view_articles.jsp";
        }
    </script>
</body>
</html>
