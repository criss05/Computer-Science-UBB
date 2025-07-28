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
        public IActionResult Login(string name, string email)
        {
            if (string.IsNullOrEmpty(name) && string.IsNullOrEmpty(email))
            {
                ViewBag.Error = "Name and email are required.";
                return View();
            }
            Customer customer = dal.GetCustomer(name, email);

            if(customer.Id != 0 && !string.IsNullOrEmpty(customer.Name) && !string.IsNullOrEmpty(customer.Email))
            {
                HttpContext.Session.SetInt32("id", customer.Id);
                HttpContext.Session.SetString("name", customer.Name);
                HttpContext.Session.SetString("email", customer.Email);
                HttpContext.Session.SetInt32("bad_words", 0);
                return RedirectToAction("Index", "Main");
            }

            return View();
        }
    }
}
