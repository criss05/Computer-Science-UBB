using Lab10.Models;
using Microsoft.AspNetCore.Mvc;
using System.Text;
using Lab10.DataAbstractionLayer;
using System.Threading.Tasks;
using System.Text.Json;
using System.Threading.Channels;

namespace Lab10.Controllers
{
    public class MainController : Controller
    {
        private readonly DAL dal = new DAL();
        private string Username => HttpContext.Session.GetString("username");

        public IActionResult Index()
        {
            if (string.IsNullOrEmpty(Username))
            {
                return RedirectToAction("Login", "Auth");
            }
            return View("MainPage");
        }

        [HttpGet]
        public IActionResult GetProducts()
        {
            List<Product> products = dal.GetProducts();

            if (products.Count == 0)
            {
                return Content("<p>No products found</p>");
            }

            var html = "";

            foreach (var product in products)
            {
                html += $"<input type=\"checkbox\" class=\"product\" name=\"products[]\" value=\"{product.Id}\" />" +
                        $"<label> {product.Name}</label><br>";
            }
            return Content(html);
        }


        [HttpPost]
        public IActionResult SubmitOrder(List<int> products)
        {
            string username = Username;
            decimal price = dal.SubmitOrder(username, products);
            return Ok("The final price is " + price);
        }


        [HttpPost]
        public IActionResult VerifyOrder(int product)
        {
            string username = Username;
            bool warn = dal.VerifyOrder(product, username);
            if (warn)
            {
                return Ok("No diversity in your orders");
            }
            return Ok();
        }

        //    [HttpGet]
        //    public IActionResult GetGuestsPage()
        //    {
        //        return View("GetGuestsPage");
        //    }

        //    [HttpGet]
        //    public IActionResult GetUserReservationsPage()
        //    {
        //        return View("UserReservationsPage");
        //    }

        //    [HttpGet]
        //    public IActionResult GetUserReservations()
        //    {
        //        int id = (int)Id;
        //        List<Reservation> reservations = dal.GetUserReservations(id);

        //        if (reservations.Count == 0)
        //        {
        //            return Content("<p>No reservations found</p>");
        //        }

        //        var html = "";

        //        foreach (var reservation in reservations)
        //        {
        //            html += "<div>";
        //            html += "<h2>Room: " + reservation.RoomId + "</h2>";
        //            html += "<p>CheckIn: " + reservation.CheckIn + "</p>";
        //            html += "<p>CheckOut: " + reservation.CheckOut + "</p>";
        //            html += "<p>Guests: " + reservation.Guests + "</p>";
        //            html += "<p>Price: " + reservation.Price + "</p>";
        //            html += "<br><br></div>";
        //        }
        //        return Content(html);
        //    }

        //    //[HttpPost]
        //    //public IActionResult RemoveBlocks(string message)
        //    //{
        //    //    List<string> words = dal.VerifyFeedback(message);

        //    //    foreach (string word in words)
        //    //    {
        //    //        message = message.Replace(word, "");
        //    //    }
        //    //    return Content(message);
        //    //}
    }
}
