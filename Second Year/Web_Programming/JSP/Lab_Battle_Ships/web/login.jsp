<%--
  Created by IntelliJ IDEA.
  User: Criss
  Date: 5/24/2025
  Time: 5:32 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<html>
<head>
    <title>Login</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <form method="post" action="LoginServlet">
        <label>Username:</label><input type="text" name="username" required><br>
        <label>Password:</label><input type="password" name="password" required><br>
        <input type="submit" value="Login">
    </form>
    <p style="color:red;">
        <%= request.getAttribute("error") != null ? request.getAttribute("error") : "" %>
    </p>
</body>
</html>
