<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@page session="true"%>
<%
  String user = (String)session.getAttribute("user");
  if (user==null){
    response.sendRedirect("login.jsp");
    return;
  }
%>
<html>
<head>
  <title>View articles</title>
  <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
  <body>
    <h1>My articles</h1>
    <label>Journal name: <input type="text" id="journalInput" placeholder="Journal name..."></label>
    <button id="searchArticles">Search</button>
    <div id="articlesContainer"></div>


    <script>
      async function loadArticles() {
        const articlesContainer = document.getElementById("articlesContainer");
        articlesContainer.innerHTML = '';

        const journal = document.getElementById("journalInput").value;
        const user = "<%=user%>";
        try{
          const response = await fetch(`ArticleController?action=getArticlesByUserAndJournal&user=\${user}&journal=\${journal}`);
          const data = await response.json();

          data.forEach((journal)=>{
            const articleDiv = document.createElement('div');
            articleDiv.innerHTML = `
                    <h2>Article: \${journal.id}</h2>
                    <p><strong>Summary:</strong>\${journal.summary}</p>
                    <p><strong>Date:</strong>\${journal.Date}</p>
                  `
            articlesContainer.appendChild(articleDiv);
          })
        }catch (error) {
          console.error("Error fetching document:", error);
        }
      }

      $(document).ready(function(){
        const searchArticles = document.getElementById("searchArticles");
        searchArticles.addEventListener("click", loadArticles);
      })
    </script>
  </body>
</html>
