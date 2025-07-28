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
        private int? Tasks => HttpContext.Session.GetInt32("tasks");

        public IActionResult Index()
        {
            //if (Id == null || string.IsNullOrEmpty(Username))
            //{
            //    return RedirectToAction("Login", "Auth");
            //}
            return View("TaskPage");
        }

        //[HttpGet]
        //public IActionResult GetTasks()
        //{
        //    List<Models.Task> todo_tasks = dal.GetToDoTasks();
        //    List<Models.Task> done_tasks = dal.GetDoneTasks();
        //    List<Models.Task> in_progress_tasks = dal.GetInProgressTasks();

        //    var html = "<div class=\"column\"> <h1>To Do</h1>";

        //    foreach (var task in todo_tasks)
        //    {
        //            html += "<div>";
        //            html += "<h2>Title: " + task.Title + "</h2>";
        //            html += "<p>assignd to: " + task.UserId + "</p>";
        //            html += "<p>Last updated: " + task.Updated + "</p>";
        //            html += $" <button id=\"MoveDone\" data-id={task.Id}>Move to done</button>";
        //            html += $" <button id=\"MoveProgress\" data-id={task.Id}>Move to in progress</button>";
        //            html += "</div>";
        //    }
        //    html += "</div>";

        //    html += "<div class=\"column\"> <h1>In Progress</h1>";

        //    foreach (var task in in_progress_tasks)
        //    {
        //        html += "<div>";
        //        html += "<h2>Title: " + task.Title + "</h2>";
        //        html += "<p>assignd to: " + task.UserId + "</p>";
        //        html += "<p>Last updated: " + task.Updated + "</p>";
        //        html += $" <button id=\"MoveDone\" data-id={task.Id}>Move to done</button>";
        //        html += $" <button id=\"MoveTODO\" data-id={task.Id}>Move to todo</button>";
        //        html += "</div>";
        //    }
        //    html += "</div>";

        //    html += "<div class=\"column\"> <h1>Done</h1>";

        //    foreach (var task in done_tasks)
        //    {
        //        html += "<div>";
        //        html += "<h2>Title: " + task.Title + "</h2>";
        //        html += "<p>assignd to: " + task.UserId + "</p>";
        //        html += "<p>Last updated: " + task.Updated + "</p>";
        //        html += $" <button id=\"MoveProgress\" data-id={task.Id}>Move to in progress</button>";
        //        html += $" <button id=\"MoveTODO\" data-id={task.Id}>Move to todo</button>";
        //        html += "</div>";
        //    }
        //    html += "</div>";
        //    return Content(html);
        //}

        //[HttpGet]
        //public IActionResult GetTasksPage()
        //{
        //    return View("TaskPage");
        //}

        //[HttpPost]
        //public IActionResult MovetoDone(int id)
        //{
        //    int tasks = (int)Tasks;
        //    HttpContext.Session.SetInt32("tasks", tasks+1);
        //    int user =(int) Id;
        //    dal.InsertLog(id, user,"done");
        //    dal.UpdateStatus("done", id);
        //    return Ok();
        //}

        //[HttpPost]
        //public IActionResult MovetoProgress(int id)
        //{
        //    int tasks = (int)Tasks;
        //    HttpContext.Session.SetInt32("tasks", tasks + 1);
        //    int user = (int)Id;
        //    dal.InsertLog(id, user,"in_progress");
        //    dal.UpdateStatus("in_progress", id);
        //    return Ok();
        //}

        //[HttpPost]
        //public IActionResult MovetoTODO(int id)
        //{
        //    int tasks = (int)Tasks;
        //    HttpContext.Session.SetInt32("tasks", tasks + 1);
        //    int user = (int)Id;
        //    dal.InsertLog(id, user,"todo");
        //    dal.UpdateStatus("todo", id);
        //    return Ok();
        //}

        //[HttpGet]
        //public IActionResult GetNrTasks()
        //{
        //    return Ok(Tasks);
        //}

        //[HttpGet]
        //public IActionResult GetLastModifiedUser()
        //{
        //    return Ok(dal.GetLastModifiedUser());
        //}

        //[HttpPost]
        //public IActionResult RemoveBlocks(string message)
        //{
        //    List<string> words = dal.VerifyFeedback(message);

        //    foreach(string word in words)
        //    {
        //        message = message.Replace(word, "");
        //    }
        //    return Content(message);
        //}

        //[HttpGet]
        //public IActionResult GetSubscribedChannels()
        //{
        //    string name = Name;
        //    List<Channels> channels = dal.GetChannels(name);

        //    if (channels.Count == 0)
        //    {
        //        return Content("<p>No channels found</p>");
        //    }

        //    var html = "";

        //    foreach (var channel in channels)
        //    {
        //        html += "<div>";
        //        html += "<h2>Channel: " + channel.Name + "</h2>";
        //        html += "<p>Description: " + channel.Description + "</p>";
        //        html += "<br><br></div>";
        //    }
        //    return Content(html);
        //}

        //[HttpGet]
        //public IActionResult GetSubscribedChannelsPage()
        //{
        //    return View("SubscribedChannelsPage");
        //}

        //[HttpGet]
        //public IActionResult AddSubscription(string channel)
        //{
        //    string name = Name;
        //    dal.AddSubscription(name, channel);

        //    return Ok();
        //}

        //[HttpGet]
        //public IActionResult SubscribePage()
        //{
        //    return View("SubscribePage");
        //}

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
