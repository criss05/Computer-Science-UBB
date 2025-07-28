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
    <title>Home page</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
    <h1>Welcome, <%=a.getName()%>!</h1>
    <div style="display:flex; flex-direction: column; justify-content: space-between;">
        <button id="addDocument" onclick="AddDocument()">Add document</button>
        <button id="viewMyCreations" onclick="ViewMyCreations()">View my creations</button>
        <button id="viewMostAuthoredDocument" onclick="ViewMostAuthoredDocument()">View most authored document</button>
    </div>

    <script>
        function AddDocument(){
            window.location.href = "add_document.jsp";
        }

        function ViewMyCreations(){
            window.location.href = "view_creations.jsp";
        }

        function ViewMostAuthoredDocument(){
            window.location.href = "best_document.jsp";
        }
    </script>
</body>
</html>
