using Lab10.Models;
using Microsoft.AspNetCore.Mvc;
using System.Text;
using Lab10.DataAbstractionLayer;
using System.Threading.Tasks;
using System.Text.Json;

namespace Lab10.Controllers
{
    public class MainController : Controller
    {
        public IActionResult Index()
        {
            return View("MainPage");
        }

        public ActionResult GetRecipes(string searchQuery="")
        {
            DAL dal = new DAL();
            List<Recipe> recipes = dal.GetRecipes(searchQuery);
            
            if(recipes.Count == 0)
            {
                return Content("<p>No recipes found</p>");
            }

            var html = "";

            foreach (var recipe in recipes)
            {
                html += "<div class='recipe'>";
                html += "<h2>" + recipe.Name + "</h2>";
                html += "<p>Author: " + recipe.Author + "</p>";
                html += "<p>Type: " + recipe.Type + "</p>";
                html += "<p>Description: " + recipe.Description + "</p>";

                html += "<div class='button-container'>" +
                        $"<button class = 'detailsButton' data-id={recipe.Id}>🛈 Details</button>" +
                        $"<button class = 'editButton' data-id={recipe.Id}>✎ Edit</button>" +
                        $"<button class = 'deleteButton' data-id={recipe.Id}> X Delete</button>" +
                    "</div>";
                html += "</div>";
            }
            return Content(html);
        }

        public IActionResult GetAllIngredients()
        {
            DAL dal = new DAL();
            List<Ingredient> ingredients = dal.GetAllIngredients();
            return Json(ingredients);
        }

        [HttpDelete]
        public IActionResult DeleteRecipe(int id)
        {
            DAL dal = new DAL();
            dal.DeleteRecipe(id);
            return Ok();
        }

        [HttpGet]
        public IActionResult GetRecipeById(int id)
        {
            DAL dal = new DAL();
            Recipe recipe = dal.GetRecipeById(id);
            return Json(recipe);
        }

        [HttpGet]
        public IActionResult EditRecipe(int id)
        {
            ViewData["recipeId"] = id;
            return View("EditPage");
        }

        [HttpPut]
        public async Task<IActionResult> UpdateRecipe([FromBody] JsonElement rawJson)
        {
            string json = rawJson.GetRawText();

            using var doc = JsonDocument.Parse(json);
            var root = doc.RootElement;

            var recipe = new Recipe();

            var id = root.GetProperty("id").GetString();
            var author = root.GetProperty("author").GetString();
            var name = root.GetProperty("name").GetString();
            var type = root.GetProperty("type").GetString();
            var description = root.GetProperty("description").GetString();
            var ingredients = new List<Ingredient>();
            var ingredientsArray = root.GetProperty("ingredients").EnumerateArray();
            foreach (var ingredient in ingredientsArray)
            {
                var ingredientObj = new Ingredient
                {
                    Id = Convert.ToInt32(ingredient.GetProperty("id").GetString()),
                    Name = ingredient.GetProperty("name").GetString()
                };
                ingredients.Add(ingredientObj);
            }
            recipe.Id = Convert.ToInt32(id);
            recipe.Author = author;
            recipe.Name = name;
            recipe.Type = type;
            recipe.Description = description;
            recipe.Ingredients = ingredients;

            DAL dal = new DAL();
            dal.UpdateRecipe(recipe.Id, recipe.Author, recipe.Name, recipe.Type, recipe.Description, recipe.Ingredients);
            Console.WriteLine("Recipe updated");
            return Ok(new {ok = true});
        }

        [HttpGet]
        public IActionResult AddRecipe(int id)
        {
            ViewData["recipeId"] = id;
            return View("AddPage");
        }

        [HttpPost]
        public async Task<IActionResult> SaveRecipe([FromBody] JsonElement rawJson)
        {
            string json = rawJson.GetRawText();

            using var doc = JsonDocument.Parse(json);
            var root = doc.RootElement;

            var recipe = new Recipe();

            var author = root.GetProperty("author").GetString();
            var name = root.GetProperty("name").GetString();
            var type = root.GetProperty("type").GetString();
            var description = root.GetProperty("description").GetString();
            var ingredients = new List<Ingredient>();
            var ingredientsArray = root.GetProperty("ingredients").EnumerateArray();
            foreach (var ingredient in ingredientsArray)
            {
                var ingredientObj = new Ingredient
                {
                    Id = Convert.ToInt32(ingredient.GetProperty("id").GetString()),
                    Name = ingredient.GetProperty("name").GetString()
                };
                ingredients.Add(ingredientObj);
            }
            recipe.Author = author;
            recipe.Name = name;
            recipe.Type = type;
            recipe.Description = description;
            recipe.Ingredients = ingredients;

            DAL dal = new DAL();
            dal.SaveRecipe(recipe.Id, recipe.Author, recipe.Name, recipe.Type, recipe.Description, recipe.Ingredients);
            Console.WriteLine("Recipe saved");
            return Ok(new { ok = true });
        }

        [HttpGet]
        public IActionResult DetailsRecipe(int id)
        {
            ViewData["recipeId"] = id;
            return View("DetailsPage");
        }

        [HttpPost]
        public IActionResult AddIngredient([FromBody] Ingredient ingredient)
        {
            DAL dal = new DAL();
            dal.AddIngredient(ingredient.Name);
            return Ok();
        }
    }
}
