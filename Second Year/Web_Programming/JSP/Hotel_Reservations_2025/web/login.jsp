<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<html>
<head>
    <title>Login</title>
</head>
<body>
    <form method="post" action="LoginController">
        <label for="username">Username:</label><input type="text" name="username" id="username" required><br><br>
        <label for="password">Password:</label><input type="password" name="password" id="password" required><br><br>
        <input type="submit" value="Login">
    </form>
    <p style="color:red;">
        <%= request.getAttribute("error") != null ? request.getAttribute("error") : "" %>
    </p>
</body>
</html>
