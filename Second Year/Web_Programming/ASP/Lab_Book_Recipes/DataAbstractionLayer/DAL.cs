using Lab10.Models;
using MySql.Data.MySqlClient;

namespace Lab10.DataAbstractionLayer
{
    public class DAL
    {
        public List<Ingredient> GetIngredientsForRecipe(int recipeId)
        {
            MySqlConnection conn;
            string myConnectionString = "server=localhost;uid=root;pwd=;database=recipe_book";

            List<Ingredient> ingredients = new List<Ingredient>();

            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT i.id, i.name FROM ingredients i " +
                    "JOIN recipe_ingredients ri ON i.id = ri.ingredient_id " +
                    "WHERE ri.recipe_id = @recipeId";
                cmd.Parameters.AddWithValue("@recipeId", recipeId);
                query += ";";
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    Ingredient ingredient = new Ingredient();
                    ingredient.Id = reader.GetInt32("id");
                    ingredient.Name = reader.GetString("name");

                    ingredients.Add(ingredient);
                }

                reader.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }

            return ingredients;
        }

        public List<Ingredient> GetAllIngredients()
        {
            MySqlConnection conn;
            string myConnectionString = "server=localhost;uid=root;pwd=;database=recipe_book";

            List<Ingredient> ingredients = new List<Ingredient>();

            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM ingredients;";
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    Ingredient ingredient = new Ingredient();
                    ingredient.Id = reader.GetInt32("id");
                    ingredient.Name = reader.GetString("name");

                    ingredients.Add(ingredient);
                }

                reader.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }

            return ingredients;
        }

        public List<Recipe> GetRecipes(string searchQuery)
        {
            MySqlConnection conn;
            string myConnectionString = "server=localhost;uid=root;pwd=;database=recipe_book";

            List<Recipe> recipes = new List<Recipe>();

            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "SELECT * FROM recipes";
                if (!string.IsNullOrEmpty(searchQuery))
                {
                    query += " WHERE type LIKE @searchQuery";
                    cmd.Parameters.AddWithValue("@searchQuery", "%" + searchQuery + "%");
                }
                query += ";";
                cmd.CommandText = query;

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    Recipe recipe = new Recipe();
                    recipe.Id = reader.GetInt32("id");
                    recipe.Name = reader.GetString("name");
                    recipe.Author = reader.GetString("author");
                    recipe.Type = reader.GetString("type");
                    recipe.Description = reader.GetString("description");
                    recipe.Ingredients = GetIngredientsForRecipe(recipe.Id);

                    recipes.Add(recipe);
                }

                reader.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return recipes;
        }

        public Recipe GetRecipeById(int id)
        {
            MySqlConnection conn;
            string myConnectionString = "server=localhost;uid=root;pwd=;database=recipe_book";
            Recipe recipe = new Recipe();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();
                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                string query = "SELECT * FROM recipes WHERE id=" + id + ";";
                cmd.CommandText = query;
                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    recipe.Id = reader.GetInt32("id");
                    recipe.Name = reader.GetString("name");
                    recipe.Author = reader.GetString("author");
                    recipe.Type = reader.GetString("type");
                    recipe.Description = reader.GetString("description");
                    recipe.Ingredients = GetIngredientsForRecipe(recipe.Id);
                }
                reader.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            return recipe;
        }

        public void DeleteRecipe(int id)
        {
            MySqlConnection conn;
            string myConnectionString = "server=localhost;uid=root;pwd=;database=recipe_book";

            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;

                string query = "DELETE FROM recipes WHERE id=" + id + ";";
                cmd.CommandText = query;

                cmd.ExecuteNonQuery();
                conn.Close();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
        }

        public void UpdateRecipe(int id, string author, string name, string type, string description, List<Ingredient> ingredients)
        {
            string connectionString = "server=localhost;uid=root;pwd=;database=recipe_book";

            try
            {
                using (MySqlConnection conn = new MySqlConnection(connectionString))
                {
                    conn.Open();

                    // Update the main recipe details
                    using (MySqlCommand cmd = new MySqlCommand())
                    {
                        cmd.Connection = conn;
                        cmd.CommandText = "UPDATE recipes SET author = @Author, name = @Name, type = @Type, description = @Description WHERE id = @Id";
                        cmd.Parameters.AddWithValue("@Author", author);
                        cmd.Parameters.AddWithValue("@Name", name);
                        cmd.Parameters.AddWithValue("@Type", type);
                        cmd.Parameters.AddWithValue("@Description", description);
                        cmd.Parameters.AddWithValue("@Id", id);
                        cmd.ExecuteNonQuery();
                    }

                    // Remove all existing ingredients for the recipe
                    using (MySqlCommand cmd = new MySqlCommand())
                    {
                        cmd.Connection = conn;
                        cmd.CommandText = "DELETE FROM recipe_ingredients WHERE recipe_id = @RecipeId";
                        cmd.Parameters.AddWithValue("@RecipeId", id);
                        cmd.ExecuteNonQuery();
                    }

                    // Add the new ingredients
                    using (MySqlCommand cmd = new MySqlCommand())
                    {
                        cmd.Connection = conn;
                        cmd.CommandText = "INSERT INTO recipe_ingredients (recipe_id, ingredient_id) VALUES (@RecipeId, @IngredientId)";
                        foreach (Ingredient ingredient in ingredients)
                        {
                            cmd.Parameters.Clear();
                            cmd.Parameters.AddWithValue("@RecipeId", id);
                            cmd.Parameters.AddWithValue("@IngredientId", ingredient.Id);
                            cmd.ExecuteNonQuery();
                        }
                    }
                }
            }
            catch (MySqlException ex)
            {
                Console.WriteLine($"Error updating recipe: {ex.Message}");
            }
        }

        public void SaveRecipe(int id, string author, string name, string type, string description, List<Ingredient> ingredients)
        {
            string connectionString = "server=localhost;uid=root;pwd=;database=recipe_book";

            try
            {
                using (MySqlConnection conn = new MySqlConnection(connectionString))
                {
                    conn.Open();

                    int insertedRecipeId;

                    // Update the main recipe details
                    using (MySqlCommand cmd = new MySqlCommand())
                    {
                        cmd.Connection = conn;
                        cmd.CommandText = "INSERT INTO recipes(author, name, type, description) VALUES (@Author, @Name, @Type, @Description)";
                        cmd.Parameters.AddWithValue("@Author", author);
                        cmd.Parameters.AddWithValue("@Name", name);
                        cmd.Parameters.AddWithValue("@Type", type);
                        cmd.Parameters.AddWithValue("@Description", description);
                        cmd.ExecuteNonQuery();

                        insertedRecipeId = (int)cmd.LastInsertedId;
                    }



                    // Add the new ingredients
                    using (MySqlCommand cmd = new MySqlCommand())
                    {
                        cmd.Connection = conn;
                        cmd.CommandText = "INSERT INTO recipe_ingredients (recipe_id, ingredient_id) VALUES (@RecipeId, @IngredientId)";
                        foreach (Ingredient ingredient in ingredients)
                        {
                            cmd.Parameters.Clear();
                            cmd.Parameters.AddWithValue("@RecipeId", insertedRecipeId);
                            cmd.Parameters.AddWithValue("@IngredientId", ingredient.Id);
                            cmd.ExecuteNonQuery();
                        }
                    }
                }
            }
            catch (MySqlException ex)
            {
                Console.WriteLine($"Error saved recipe: {ex.Message}");
            }
        }

        public void AddIngredient(string name)
        {
            string connectionString = "server=localhost;uid=root;pwd=;database=recipe_book";
            using var conn = new MySqlConnection(connectionString);
            conn.Open();

            using var cmd = new MySqlCommand("INSERT INTO ingredients(name) VALUES(@Name)", conn);
            cmd.Parameters.AddWithValue("@Name", name);
            cmd.ExecuteNonQuery();
        }
    }
}
