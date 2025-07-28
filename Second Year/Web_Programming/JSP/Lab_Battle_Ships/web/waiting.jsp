<%--
  Created by IntelliJ IDEA.
  User: Criss
  Date: 5/24/2025
  Time: 5:47 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page session="true" %>
<!DOCTYPE html>
<html>
<head>
  <title>Waiting Room</title>
  <script>
    setInterval(() => {
      fetch('GameServlet?action=checkPlayers')
              .then(response => response.json())
              .then(data => {
                if (data.ready) {
                  window.location.href = 'game.jsp';
                }
              });
    }, 2000);
  </script>
</head>
<body>
<h2>Waiting for another player...</h2>
</body>
</html>

