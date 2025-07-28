using Lab10.DataAbstractionLayer;
using Lab10.Models;
using Microsoft.AspNetCore.Mvc;
using System.Xml.Linq;

namespace Lab10.Controllers
{
    public class AuthController : Controller
    {
        private readonly DAL dal = new DAL();

        [HttpGet]
        public IActionResult Login() => View();

        [HttpPost]
        public IActionResult Login(string name)
        {
            if (string.IsNullOrEmpty(name))
            {
                ViewBag.Error = "Name is required.";
                return View();
            }
            User user = dal.GetUser(name);

            if(user.Id != 0 && !string.IsNullOrEmpty(user.Name))
            {
                HttpContext.Session.SetInt32("id", user.Id);
                HttpContext.Session.SetString("name", user.Name);
                HttpContext.Session.SetString("question", user.Question);
                HttpContext.Session.SetString("answer", user.Answer);
                return RedirectToAction("SecretQuestion");
            }

            return View();
        }

        [HttpGet]
        public IActionResult SecretQuestion()
        {
            string name = HttpContext.Session.GetString("name");
            string question = HttpContext.Session.GetString("question");

            if (!string.IsNullOrEmpty(name))
            {
                ViewBag.Question = question;
                return View();
            }

            return RedirectToAction("Login");
        }

        [HttpPost]
        public IActionResult SecretQuestion(string answer)
        {
            string name = HttpContext.Session.GetString("name");
            string question = HttpContext.Session.GetString("question");
            string correct_answer = HttpContext.Session.GetString("answer");

            if (string.IsNullOrEmpty(name))
            { 
                return RedirectToAction("Login");
            }

            if(correct_answer.Equals(answer, System.StringComparison.OrdinalIgnoreCase))
            {
                return RedirectToAction("Index", "Main");
            }

            ViewBag.Error = "Incorrect answer";
            return View();
        }
    }
}
