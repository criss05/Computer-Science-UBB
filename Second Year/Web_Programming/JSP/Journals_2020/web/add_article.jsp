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
      <title>Add article</title>
      <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
  </head>
  <body>
      <h1>Add Article</h1>
      <label>Journal name:
        <input id="journalInput" type="text">
      </label>
      <label>Summary:
        <input id="summaryInput" type="text">
      </label>
      <button id="submitArticle" onclick="SubmitArticle()">Add article</button>


      <script>
        function SubmitArticle(){
          const journalInput = document.getElementById("journalInput").value;
          const summaryInput = document.getElementById("summaryInput").value;

          $.ajax({
            url:'ArticleController',
            method: 'POST',
            data: {
              journal: journalInput,
              user: `<%=user%>`,
              summary: summaryInput
            },
            success: function () {
              alert("Article added!");
              window.location.href = 'home_page.jsp';
            },
            error: function (){
              alert("Failed to add article!");
            }
          })
        }
      </script>
  </body>
</html>
