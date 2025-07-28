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

            if(user.Id != 0 && !string.IsNullOrEmpty(user.Username))
            {
                HttpContext.Session.SetInt32("id", user.Id);
                HttpContext.Session.SetString("username", user.Username);
                HttpContext.Session.SetInt32("tasks", 0);
                return RedirectToAction("Index", "Main");
            }

            return View();
        }
    }
}
