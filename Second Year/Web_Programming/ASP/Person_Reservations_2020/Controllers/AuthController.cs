using Lab10.DataAbstractionLayer;
using Microsoft.AspNetCore.Mvc;

namespace Lab10.Controllers
{
    public class AuthController : Controller
    {
        private readonly DAL dal = new DAL();

        [HttpGet]
        public IActionResult Login() => View();

        [HttpPost]
        public IActionResult Login(String name)
        {
            if (string.IsNullOrEmpty(name))
            {
                ViewBag.Error = "Name is required.";
                return View();
            }

            HttpContext.Session.SetString("Name", name);
            return RedirectToAction("Index", "Main");
        }
    }
}
