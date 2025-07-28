<%@ page import="domain.Author" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@page session="true"%>
<%
  Author a = (Author) session.getAttribute("author");
  if (a==null){
    response.sendRedirect("login.jsp");
    return;
  }
%>
<html>
<head>
  <title>View creations</title>
  <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
  <body>
    <h1>My creations</h1>
    <div id="creationContainer"></div>

    <script>
      async function deleteMovie(id){
        const response = await fetch(`MovieController?id=\${id}`, {
        method: "DELETE"
        })
        if (response.ok){
          const refresh = await fetch("AuthorController?action=UpdateSessionAuthor&id=<%=a.getId()%>");
          if (refresh.ok){
           location.reload();
          }
        }
      }

      async function loadCreations() {
        const document_list = "<%=a.getDocumentList()%>" || "";
        const movie_list = "<%=a.getMoviesList()%>" || "";
        const creationContainer = document.getElementById("creationContainer");
        creationContainer.innerHTML = '';
        let movies = [];

        if(movie_list!==""){
            movies = movie_list.split(', ');
        }

        let documents=[];
        if(document_list!==""){
            documents = document_list.split(', ');
        }

        const documents_len = documents.length;
        const movies_len = movies.length;
        let i = 0;
        let j = 0;

        while (i < documents_len || j < movies_len) {
          if (i < documents_len) {
            try {
              const response = await fetch(`DocumentController?action=getByName&name=\${documents[i]}`)
              const data = await response.json();
              const documentDiv = document.createElement('div');
              documentDiv.innerHTML = `
                    <h2>\${data.name}</h2>
                    <p><strong>Content:</strong>\${data.content}</p>
                  `
              creationContainer.appendChild(documentDiv);
              i++;
            } catch (error) {
              console.error("Error fetching document:", error);
            }
          }

          if (j < movies_len) {
            try {
              const response = await fetch(`MovieController?action=getByName&title=\${movies[j]}`)
              const data = await response.json();
              const movieDiv = document.createElement('div');
              movieDiv.innerHTML = `
                    <h2>\${data.title}</h2>
                    <p><strong>Duration:</strong>\${data.duration}</p>
                    <button onclick='deleteMovie(\${data.id})'>X</button>
                  `
              creationContainer.appendChild(movieDiv);
              j++;
            } catch (error) {
              console.error("Error fetching movie:", error);
            }
          }
        }
      }

      $(document).ready(function(){
        loadCreations();
      })
    </script>
  </body>
</html>
