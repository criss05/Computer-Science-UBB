using Lab10.Models;
using Microsoft.AspNetCore.Mvc;
using System.Text;
using Lab10.DataAbstractionLayer;
using System.Threading.Tasks;
using System.Text.Json;
using System.Threading.Channels;
using System.Diagnostics;

namespace Lab10.Controllers
{
    public class MainController : Controller
    {
        private readonly DAL dal = new DAL();
        private string Username => HttpContext.Session.GetString("username");

        private string songs => HttpContext.Session.GetString("songs");

        public IActionResult Index()
        {
            if (string.IsNullOrEmpty(Username))
            {
                return RedirectToAction("Login", "Auth");
            }
            return View("MainPage");
        }

        [HttpGet]
        public IActionResult GetSongs()
        {
            List<Song> songs = dal.GetSongs();

            if (songs.Count == 0)
            {
                return Content("<p>No songs found</p>");
            }

            var html = "";

            foreach (var song in songs)
            {
                html += $"<input type=\"checkbox\" class=\"song\" name=\"songs[]\" value=\"{song.Id}\" />" +
                        $"<label> {song.Title}</label><br>";
            }
            return Content(html);
        }


        [HttpPost]
        public IActionResult SubmitPlaylist()
        {
            string username = Username;
            string s = songs;
            List<int> s_l = new List<int>();
            var arr = s.Split(",");
            string warn_genre = "";
            string warn = "";
            List<string> names = new List<string>();
            foreach (string song in arr)
            {
                if (!string.IsNullOrEmpty(song))
                {
                    string name = dal.GetSong(Int32.Parse(song));
                    names.Add(name);
                }
            }
            foreach (string song in arr)
            {
                if (!string.IsNullOrEmpty(song))
                {
                    s_l.Add(Int32.Parse(song));
                        string err = dal.VerifyPlaylist(Int32.Parse(song), username);
                        if(err!="" && warn_genre == "")
                        {
                            warn_genre += err;
                        }
                        else if(err == "" && (!warn_genre.Contains(".") || warn_genre != ""))
                        {
                            warn_genre = "";
                        }
                        else if (err == "")
                        {
                            warn_genre = ".";
                        }
                }
            }
            if(warn_genre != "" || warn_genre.Contains("."))
            {
               warn += "You've been listening only to " + warn_genre + ". Try mixing it up!";
            }
            warn += dal.SubmitPlaylist(username, s_l);
            HttpContext.Session.SetString("songs", "");
            return Ok(warn);
        }

        [HttpPost]
        public IActionResult AddSong(int song)
        {
            string username = Username;
            string s = songs;
            s += "," + song;
            HttpContext.Session.SetString("songs", s);
            // string warn = dal.VerifyPlaylist(song, username);
            //if (warn != "")
            //{
            //    return Ok(warn);
            //}
            return Ok();
        }

        //[HttpPost]
        //public IActionResult VerifyOrder(int product)
        //{
        //    string username = Username;
        //    bool warn = dal.VerifyOrder(product, username);
        //    if (warn)
        //    {
        //        return Ok("No diversity in your orders");
        //    }
        //    return Ok();
        //}

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
