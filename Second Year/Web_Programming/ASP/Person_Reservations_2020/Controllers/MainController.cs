using Lab10.Models;
using Microsoft.AspNetCore.Mvc;
using System.Text;
using Lab10.DataAbstractionLayer;
using System.Threading.Tasks;
using System.Text.Json;

namespace Lab10.Controllers
{
    public class MainController : Controller
    {
        private readonly DAL dal = new DAL();
        private string Name => HttpContext.Session.GetString("Name");


        public IActionResult Index()
        {
            if (string.IsNullOrEmpty(Name))
            {
                return RedirectToAction("Login", "Auth");
            }
            return View("MainPage");
        }

        [HttpGet]
        public IActionResult GetChannels(string name)
        {
            List<Channels> channels = dal.GetChannels(name);

            if (channels.Count == 0)
            {
                return Content("<p>No channels found</p>");
            }

            var html = "";

            foreach (var channel in channels)
            {
                html += "<div>";
                html += "<h2>Channel: " +channel.Id + ". " + channel.Name + "</h2>";
                html += "<p>Owner: " + channel.PId + "</p>";
                html += "<p>Description: " + channel.Description + "</p>";
                html += "<p>Subscribers: " + channel.Subscribers + "</p>";
                html += "<br><br></div>";
            }
            return Content(html);
        }

        [HttpGet]
        public IActionResult GetChannelsPage()
        {
            return View("ChannelsPage");
        }


        [HttpGet]
        public IActionResult GetSubscribedChannels()
        {
            string name = Name;
            List<Channels> channels = dal.GetChannels(name);

            if (channels.Count == 0)
            {
                return Content("<p>No channels found</p>");
            }

            var html = "";

            foreach (var channel in channels)
            {
                html += "<div>";
                html += "<h2>Channel: " + channel.Name + "</h2>";
                html += "<p>Description: " + channel.Description + "</p>";
                html += "<br><br></div>";
            }
            return Content(html);
        }

        [HttpGet]
        public IActionResult GetSubscribedChannelsPage()
        {
            return View("SubscribedChannelsPage");
        }

        [HttpGet]
        public IActionResult AddSubscription(string channel)
        {
            string name = Name;
            dal.AddSubscription(name, channel);

            return Ok();
        }

        [HttpGet]
        public IActionResult SubscribePage()
        {
            return View("SubscribePage");
        }

        //    [HttpPost]
        //    public IActionResult ReserveHotel(int hotelId)
        //    {
        //        Reservation reservation = new Reservation
        //        {
        //            Id = 0,
        //            Person = Person,
        //            Type = "Hotel",
        //            ResourceId = hotelId
        //        };

        //        Reservation new_reservation = dal.AddReservation(reservation);

        //        Hotel hotel = dal.GetHotel(hotelId);
        //        hotel.Rooms--;
        //        dal.UpdateHotel(hotel);

        //        string old_reservations = HttpContext.Session.GetString("Reservations");
        //        string new_reservations = string.IsNullOrEmpty(old_reservations)
        //            ? new_reservation.Id.ToString()
        //            : new_reservation.Id.ToString() + "," + old_reservations;
        //        HttpContext.Session.SetString("Reservations", new_reservations);

        //        Console.WriteLine(Reservations);

        //        return Ok();
        //    }

        //    [HttpGet]
        //    public IActionResult CancelReservations()
        //    {
        //        string reservations = Reservations;

        //        List<string> reservationsList = reservations.Split(',')
        //            .Where(r => !string.IsNullOrEmpty(r))
        //            .ToList();
        //        Reservation reservation;

        //        foreach (string r in reservationsList)
        //        {
        //            int r_id = Convert.ToInt32(r);
        //            reservation = dal.GetReservation(r_id);
        //            if (reservation.Type == "Flight")
        //            {
        //                Flight flight = dal.GetFlight(reservation.ResourceId);
        //                flight.Seats++;
        //                dal.UpdateFlight(flight);
        //            }
        //            else if (reservation.Type == "Hotel")
        //            {
        //                Hotel hotel = dal.GetHotel(reservation.ResourceId);
        //                hotel.Rooms++;
        //                dal.UpdateHotel(hotel);
        //            }
        //            dal.DeleteReservation(r_id);
        //        }

        //        HttpContext.Session.SetString("Reservations", "");
        //        return Ok();
        //    }
        //}
    }
}
