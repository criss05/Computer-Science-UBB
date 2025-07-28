<%--
  Created by IntelliJ IDEA.
  User: Criss
  Date: 5/24/2025
  Time: 5:45 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
  <title>Error</title>
</head>
<body>
<h3 style="color:red;">Error: <%= request.getAttribute("error") %></h3>
<a href="login.jsp">Go Back</a>
</body>
</html>
