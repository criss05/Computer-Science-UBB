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
        public IActionResult Login(string username)
        {
            if (string.IsNullOrEmpty(username))
            {
                ViewBag.Error = "Username is required.";
                return View();
            }

            HttpContext.Session.SetString("username", username);
            HttpContext.Session.SetString("songs", "");
            return RedirectToAction("Index", "Main");
        }
    }
}
