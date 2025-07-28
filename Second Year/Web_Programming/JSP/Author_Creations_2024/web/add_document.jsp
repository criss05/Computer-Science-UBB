<%@ page import="domain.Author" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@page session="true"%>
<%
  Author a = (Author) session.getAttribute("author");
  if (a==null){
    response.sendRedirect("login.jsp");
    return;
  }
%>
<html>
  <head>
      <title>Add document</title>
      <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
  </head>
  <body>
      <h1>Add Document</h1>
      <label>Document name:
        <input id="nameInput" type="text">
      </label>
      <label>Document content:
        <input id="contentInput" type="text">
      </label>
      <button id="submitDocument" onclick="SubmitDocument()">Add document</button>


      <script>
        function SubmitDocument(){
          const nameInput = document.getElementById("nameInput").value;
          const contentInput = document.getElementById("contentInput").value;

          $.ajax({
            url:'DocumentController',
            method: 'POST',
            data: {
              name: nameInput,
              contents: contentInput,
              id: <%=a.getId()%>,
              author_name: `<%=a.getName()%>`,
              document_list: `<%=a.getDocumentList()%>`,
              movies_list: `<%=a.getMoviesList()%>`
            },
            success: function () {
              alert("Document added!");
              window.location.href = 'home_page.jsp';
            },
            error: function (){
              alert("Failed to add document!");
            }
          })
        }
      </script>
  </body>
</html>
