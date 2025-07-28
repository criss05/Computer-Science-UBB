namespace Lab10.Models
{
    public class Recipe
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Author { get; set; }
        public string Type { get; set; }
        public string Description { get; set; }
        public List<Ingredient> Ingredients { get; set; }

    }
}
