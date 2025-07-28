<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<html>
<head>
    <title>Login</title>
</head>
<body>
    <form method="post" action="LoginController">
        <label for="author">Name:</label><input type="text" name="author" id="author" required><br><br>
        <label for="creation">Creation:</label><input type="text" name="creation" id="creation" required><br><br>
        <input type="submit" value="Login">
    </form>
    <p style="color:red;">
        <%= request.getAttribute("error") != null ? request.getAttribute("error") : "" %>
    </p>
</body>
</html>
