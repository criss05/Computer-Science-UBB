<%--
  Created by IntelliJ IDEA.
  User: Criss
  Date: 5/24/2025
  Time: 5:49 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page session="true" %>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
  <title>Ships Game</title>
  <link rel="stylesheet" href="styles.css">
  <script>
    let placingShips = true;
    let shipsPlaced = 0;

    function drawGrid() {
      const grid = document.getElementById("grid");
      grid.innerHTML = "";
      for (let i = 0; i < 100; i++) {
        const cell = document.createElement("div");
        cell.className = "grid-cell";
        cell.dataset.x = i % 10;
        cell.dataset.y = Math.floor(i / 10);
        cell.onclick = () => cellClicked(cell);
        grid.appendChild(cell);
      }
    }

    function cellClicked(cell) {
      const x = cell.dataset.x;
      const y = cell.dataset.y;

      if (placingShips && shipsPlaced < 2) {
        placeShip(x, y, cell);
      } else {
        attack(x, y);
      }
    }

    function placeShip(x, y, cell) {
      fetch("GameServlet", {
        method: "POST",
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: `action=place&x=\${x}&y=\${y}`
      })
              .then(res => res.json())
              .then(data => {
                if (data.status === "ok") {
                  cell.style.backgroundColor = "gray";
                  shipsPlaced++;
                  if (shipsPlaced === 2) {
                    placingShips = false;
                    document.getElementById("status").innerText = "Ships placed. Start attacking!";
                  }
                } else {
                  alert(data.message);
                }
              });
    }

    function attack(x, y) {
      fetch("GameServlet", {
        method: "POST",
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: `action=attack&x=\${x}&y=\${y}`
      })
              .then(res => res.json())
              .then(data => {
                const cell = document.querySelector(`.grid-cell[data-x='\${x}'][data-y='\${y}']`);
                if (data.status === "ok") {
                  cell.style.backgroundColor = data.result === "hit" ? "red" : "blue";

                  if (data.gameOver) {
                      alert("Game Over!");
                  }
                } else {
                  alert(data.message);
                }
              });
    }

    function pollStatus() {
      fetch("GameServlet", {
        method: "POST",
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: "action=status"
      })
              .then(res => res.json())
              .then(data => {
                let msg = "";
                if (data.hit) msg += `Hits: \${data.hit} `;
                if (data.miss) msg += `Misses: \${data.miss}`;
                document.getElementById("stats").innerText = msg;
              });
    }

    window.onload = () => {
      drawGrid();
      setInterval(pollStatus, 3000);
    };
  </script>
</head>
<body>
<h2>Welcome, ${sessionScope.username}</h2>
<div id="status">Place 2 ships by clicking any 2 cells.</div>
<div id="grid" class="grid"></div>
<div id="stats" style="margin-top:10px;"></div>

<form action="LogoutServlet" method="get">
  <input type="submit" value="Logout">
</form>
</body>
</html>
