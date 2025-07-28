using Lab10.DataAbstractionLayer;
using Lab10.Models;
using Microsoft.AspNetCore.Http;
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
        public IActionResult Login(string username, int password)
        {
            if (string.IsNullOrEmpty(username))
            {
                ViewBag.Error = "Username and password are required.";
                return View();
            }
            User user = dal.GetUser(username, password);

            if(user.Id != 0 && !string.IsNullOrEmpty(user.Username))
            {
                HttpContext.Session.SetInt32("id", user.Id);
                HttpContext.Session.SetString("username", user.Username);
                HttpContext.Session.SetInt32("password", user.Password);
                return RedirectToAction("Index", "Main");
            }

            return View();
        }
    }
}
