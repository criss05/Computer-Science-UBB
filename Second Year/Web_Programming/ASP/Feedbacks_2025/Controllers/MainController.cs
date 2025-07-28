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
        private string Name => HttpContext.Session.GetString("name");
        private string Email => HttpContext.Session.GetString("email");
        private int? Bad_words => HttpContext.Session.GetInt32("bad_words");

        public IActionResult Index()
        {
            if (Id == null || string.IsNullOrEmpty(Name) || string.IsNullOrEmpty(Email))
            {
                return RedirectToAction("Login", "Auth");
            }
            return View("MainPage");
        }

        [HttpGet]
        public IActionResult GetFeedbacks()
        {
            List<Feedback> feedbacks = dal.GetFeedbacks();

            if (feedbacks.Count == 0)
            {
                return Content("<p>No feedbacks found</p>");
            }

            var html = "";

            foreach (var feedback in feedbacks)
            {
                if (feedback.CustomerId == Id)
                {

                    html += "<div style=\"background-color:yellow\">";
                    html += "<h2>Feedback: " + feedback.Id + "</h2>";
                    html += "<p>Customer: " + feedback.CustomerId + "</p>";
                    html += "<p>Message: " + feedback.Message + "</p>";
                    html += "<p>Timestamp: " + feedback.Timestamp + "</p>";
                    html += "<br><br></div>";
                }
                else
                {

                    html += "<div>";
                    html += "<h2>Feedback: " + feedback.Id + "</h2>";
                    html += "<p>Customer: " + feedback.CustomerId + "</p>";
                    html += "<p>Message: " + feedback.Message + "</p>";
                    html += "<p>Timestamp: " + feedback.Timestamp + "</p>";
                    html += "<br><br></div>";
                }

            }
            return Content(html);
        }

        [HttpGet]
        public IActionResult GetFeedbackPage()
        {
            return View("FeedbackPage");
        }

        [HttpPost]
        public IActionResult InsertFeedback(string message)
        {
            int id = (int) Id;
            bool result = dal.AddFeedback(message, id);
            return result ? Ok() : BadRequest();
        }

        [HttpGet]
        public IActionResult VerifyMessage(string message)
        {
            List<string> words = dal.VerifyFeedback(message);
            if (words.Count()<=3)
            {
                InsertFeedback(message);
                return Content("Success");
            }
            else
            {
                HttpContext.Session.SetInt32("bad_words", (int)Bad_words + 1);
                return Content("The following words are blocked: " + String.Join(", ", words));
            }
        }

        [HttpGet]
        public IActionResult GetBadWordsCount()
        {
            return Ok(Bad_words);
        }

        [HttpGet]
        public IActionResult GetInsertFeedbackPage()
        {
            return View("AddFeedbackPage");
        }

        [HttpPost]
        public IActionResult RemoveBlocks(string message)
        {
            List<string> words = dal.VerifyFeedback(message);

            foreach(string word in words)
            {
                message = message.Replace(word, "");
            }
            return Content(message);
        }
    }
}
