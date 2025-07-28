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
      <title>Reserve room</title>
      <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
  </head>
  <body>
      <h1>Reserve room</h1>
      <label>Check in:
        <input id="checkIn" type="date">
      </label>
      <label>Check out:
        <input id="checkOut" type="date">
      </label>
      <button id="searchButton" onclick="SearchRooms()">Search</button>
      <div id="roomDiv"></div>

      <script>
        function SearchRooms(){
          const checkIn = document.getElementById("checkIn").value;
          const checkOut = document.getElementById("checkOut").value;

          $.ajax({
            url:'RoomController',
            method: 'POST',
            data: {
                action: "getRoomsByDate",
                checkIn: checkIn,
                checkOut: checkOut
            },
            success: function (data) {
                const roomDiv = document.getElementById("roomDiv");
                roomDiv.innerHTML = "";
              data.forEach(room=>{
                  const elem = document.createElement('div');
                  elem.innerHTML = `
                        <h2> Number: \${room.number}</h2>
                        <p><strong>Capacity: </strong>\${room.capacity}</p>
                        <p><strong>Base price: </strong>\${room.price}</p>
                        <button data-id="\${room.id}" onclick="Reserve(this)">Reserve</button>
                        <input id="guestsInput" placeholder="Number of guests..." type="number"/>
                        `
                  roomDiv.appendChild(elem);
              })
            },
            error: function (){
              alert("Failed to add document!");
            }
          })
        }

        function Reserve(button){
            const roomId = button.dataset.id;
            const userId = <%=u.getId()%>
            const checkIn = document.getElementById("checkIn").value;
            const checkOut = document.getElementById("checkOut").value;
            const guests = button.nextElementSibling.value;
            $.ajax({
                url:'ReservationController',
                method: 'POST',
                data: {
                    action: "reserveRoom",
                    userId: userId,
                    roomId: roomId,
                    checkIn: checkIn,
                    checkOut: checkOut,
                    guests: guests
                },
                success: function (data) {
                    alert("Reservation added");
                    window.location.href="home_page.jsp";
                },
                error: function (){
                    alert("Failed to add document!");
                }
            })
        }
      </script>
  </body>
</html>
