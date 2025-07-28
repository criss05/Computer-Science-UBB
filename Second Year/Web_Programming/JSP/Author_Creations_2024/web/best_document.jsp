<%--
  Created by IntelliJ IDEA.
  User: Criss
  Date: 6/15/2025
  Time: 8:50 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Best document</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
    <h1>Best document</h1>
    <div id="documentContainer"></div>

    <script>
        document.addEventListener("DOMContentLoaded", async()=>{
            const response = await fetch("DocumentController?action=bestDocument");
            const data = await response.json();

            const documentContainer = document.getElementById("documentContainer");
            documentContainer.innerHTML = `
                <h2>\${data.name}</h2>
                <p><strong>Contents:</strong>\${data.contents}</p>
             `
        })
    </script>
</body>
</html>
