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
        private int? Id => HttpContext.Session.GetInt32("id");
        private string Username => HttpContext.Session.GetString("username");
        private string Password => HttpContext.Session.GetString("password");

        public IActionResult Index()
        {
            if (Id == null || string.IsNullOrEmpty(Username) || string.IsNullOrEmpty(Password))
            {
                return RedirectToAction("Login", "Auth");
            }
            return View("MainPage");
        }

        [HttpGet]
        public IActionResult GetFreeRooms(DateOnly check_in, DateOnly check_out)
        {
            List<HotelRoom> rooms = dal.GetFreeRooms(check_in, check_out);

            if (rooms.Count == 0)
            {
                return Content("<p>No rooms found</p>");
            }

            var html = "";

            foreach (var room in rooms)
            {
                    html += "<div>";
                    html += "<h2>Room: " + room.RoomNumber + "</h2>";
                    html += "<p>Capacity: " + room.Capacity + "</p>";
                    html += "<p>Price: " + room.Price + "</p>";
                    html += $"<button class='reserve_room' data-id={room.Id}>Reserve</button>";   
                    html += "<br><br></div>";
            }
            return Content(html);
        }


        [HttpPost]
        public IActionResult ReserveRoom(int r_id, DateOnly check_in, DateOnly check_out)
        {
            int u_id = (int)Id;
            if(dal.ReserveRoom(u_id, r_id, check_in, check_out))
            {
                return Ok();
            }
            return BadRequest();
        }


        [HttpGet]
        public IActionResult GetNumberGuests(DateOnly day)
        {
            int nr_guests = dal.GetGuests(day);
            return Ok(nr_guests);
        }

        [HttpGet]
        public IActionResult GetGuestsPage()
        {
            return View("GetGuestsPage");
        }
        
        [HttpGet]
        public IActionResult GetUserReservationsPage()
        {
            return View("UserReservationsPage");
        }

        [HttpGet]
        public IActionResult GetUserReservations()
        {
            int id = (int)Id;
            List<Reservation> reservations = dal.GetUserReservations(id);

            if (reservations.Count == 0)
            {
                return Content("<p>No reservations found</p>");
            }

            var html = "";

            foreach (var reservation in reservations)
            {
                html += "<div>";
                html += "<h2>Room: " + reservation.RoomId + "</h2>";
                html += "<p>CheckIn: " + reservation.CheckIn + "</p>";
                html += "<p>CheckOut: " + reservation.CheckOut + "</p>";
                html += "<p>Guests: " + reservation.Guests + "</p>";
                html += "<p>Price: " + reservation.Price + "</p>";
                html += "<br><br></div>";
            }
            return Content(html);
        }

        //[HttpPost]
        //public IActionResult RemoveBlocks(string message)
        //{
        //    List<string> words = dal.VerifyFeedback(message);

        //    foreach (string word in words)
        //    {
        //        message = message.Replace(word, "");
        //    }
        //    return Content(message);
        //}
    }
}
