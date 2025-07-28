<!DOCTYPE html>
<html >
    <head>
        <title>Recipe Book</title>
        <link rel="stylesheet" href="../css/indexStyle.css">
    </head>
    <body>
        <h1>All Recipes</h1>
        <a href="add_ingredients.php">
            <button>Add Ingredients</button>
        </a>
        <a href="add_recipe.php">
            <button>Add Recipe</button>
        </a>
        <input type="text" id="searchInput" placeholder="Search by type." oninput="searchRecipes()" />
        <p id="filterDisplay"></p>
        
        <div id="recipeList">Loading recipes...</div>

        <script src="../js/main.js"></script>
    </body>
</html>