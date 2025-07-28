using Lab10.Models;
using Microsoft.AspNetCore.Mvc;
using System.Text;
using Lab10.DataAbstractionLayer;
using System.Threading.Tasks;
using System.Text.Json;
using System.Threading.Channels;
using System.Xml.XPath;

namespace Lab10.Controllers
{
    public class MainController : Controller
    {
        private readonly DAL dal = new DAL();
        private string Name => HttpContext.Session.GetString("name");

        public IActionResult Index()
        {
            if (string.IsNullOrEmpty(Name))
            {
                return RedirectToAction("Login", "Auth");
            }
            return View("MainPage");
        }

        //[HttpGet]
        //public IActionResult GetProducts()
        //{
        //    List<Product> products = dal.GetProducts();

        //    if (products.Count == 0)
        //    {
        //        return Content("<p>No products found</p>");
        //    }

        //    var html = "";

        //    foreach (var product in products)
        //    {
        //        html += $"<input type=\"checkbox\" class=\"product\" name=\"products[]\" value=\"{product.Id}\" />" +
        //                $"<label> {product.Name}</label><br>";
        //    }
        //    return Content(html);
        //}


        //[HttpPost]
        //public IActionResult SubmitOrder(List<int> products)
        //{
        //    string username = Username;
        //    decimal price = dal.SubmitOrder(username, products);
        //    return Ok("The final price is " + price);
        //}


        [HttpPost]
        public IActionResult AddDocument(string name, string contents)
        {
            string author = Name;
            dal.AddDocument(name, author, contents);
            return Ok("User added successfully");
        }

        [HttpGet]
        public IActionResult GetAddDocumentPage()
        {
            return View("AddDocumentPage");
        }

        [HttpGet]
        public IActionResult GetCreationsPage()
        {
            return View("CreationsPage");
        }

        [HttpGet]
        public IActionResult GetCreations()
        {
            string name = Name;
            List<Movie> movies = dal.GetMovies(Name);
            List<Document> documents = dal.GetDocuments(Name);

            if (movies.Count == 0 || documents.Count == 0)
            {
                return Content("<p>No creations found</p>");
            }

            int m_len = movies.Count;
            int d_len = documents.Count;
            int i = 0;
            int j = 0;
            var html = "";

            while (i<m_len && j<d_len)
            {
                html += "<div>";
                html += "<h2>Movie: " + movies[i].Title + "</h2>";
                html += "<p>Duration: " + movies[i].Duration + "</p>";
                html += $"<button class=\"deleteMovie\" data-id={movies[i].Id}>X</button>";
                html += "<br><br></div>";

                html += "<div>";
                html += "<h2>Document: " + documents[j].Name + "</h2>";
                html += "<p>Contents: " + documents[j].Contents + "</p>";
                html += $"<button class=\"deleteDocument\" data-id={documents[j].Id}>X</button>";
                html += "<br><br></div>";

                i++;
                j++;
            }

            while (i < m_len)
            {
                html += "<div>";
                html += "<h2>Movie: " + movies[i].Title + "</h2>";
                html += "<p>Duration: " + movies[i].Duration + "</p>";
                html += $"<button class=\"deleteMovie\" data-id={movies[i].Id}>X</button>";
                html += "<br><br></div>";
                i++;
            }

            while (j < d_len)
            {
                html += "<div>";
                html += "<h2>Document: " + documents[j].Name + "</h2>";
                html += "<p>Contents: " + documents[j].Contents + "</p>";
                html += $"<button class=\"deleteDocument\" data-id={documents[j].Id}>X</button>";
                html += "<br><br></div>";
                j++;
            }

            return Content(html);
        }

        [HttpGet]
        public IActionResult DeleteDocument(int id)
        {
            string name = Name;
            dal.DeleteDocument(id, name);

            return Ok();
        }

        [HttpGet]
        public IActionResult DeleteMovie(int id)
        {
            string name = Name;
            dal.DeleteMovie(id, name);

            return Ok();
        }

        [HttpGet]
        public IActionResult GetLargestNrAuthorsPage()
        {
            return View("LargestNrAuthors");
        }

        [HttpGet]
        public IActionResult GetLargestNrAuthors()
        {
            string document = dal.GetLargestNrAuthors();

            if (string.IsNullOrEmpty(document))
            {
                return Content("<p>No document found</p>");
            }
            var html = "the document with the largest number of authors is: <strong>" + document + "</strong>";
            return Content(html);
        }
    }
}
