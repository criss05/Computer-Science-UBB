<%@ page import="domain.User" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@page session="true"%>
<%
  User u = (User) session.getAttribute("user");
  if (u==null){
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
    <h1>Welcome>!</h1>
    <div style="display:flex; flex-direction: column; justify-content: space-between;">
        <button id="reserveRoom" onclick="ReserveRoom()">Reserve room</button>
        <button id="checkGuests" onclick="CheckGuests()">Check guests</button>
        <button id="viewReservations" onclick="ViewReservations()">View reservations</button>
    </div>

    <script>
        function ReserveRoom(){
            window.location.href = "reserve_room.jsp";
        }

        function CheckGuests(){
            window.location.href = "check_guests.jsp";
        }

        function ViewReservations(){
            window.location.href = "view_reservation.jsp";
        }
    </script>
</body>
</html>
