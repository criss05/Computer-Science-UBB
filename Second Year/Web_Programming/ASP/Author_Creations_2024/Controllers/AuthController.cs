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
        public IActionResult Login(string name, string creation)
        {
            if (string.IsNullOrEmpty(name) && string.IsNullOrEmpty(creation))
            {
                ViewBag.Error = "Name and creation are required.";
                return View();
            }

            Author author = dal.GetAuthor(name, creation);

            if(author.Id < 0)
            {
                return View();
            }

            HttpContext.Session.SetString("name", name);
            return RedirectToAction("Index", "Main");
        }
    }
}
