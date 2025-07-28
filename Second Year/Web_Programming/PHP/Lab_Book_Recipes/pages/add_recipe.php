<!DOCTYPE html>
<html lang="en">
<head>
    <title>Add New Recipe</title>
    <link rel="stylesheet" href="../css/recipeStyle.css">
</head>
<body>
    <h1>Add New Recipe</h1>

    <form id="addRecipeForm">
        <label>Author:
            <input type="text" name="author" required>
        </label>

        <label>Name:
            <input type="text" name="name" required>
        </label>

        <label>Type:
            <input type="text" name="type" required>
        </label>

        <label>Description:
            <textarea name="description" rows="5" required></textarea>
        </label>

        <label>Ingredients:</label>
        <div id="ingredientsContainer" class="ingredients-list">
        </div>

        <button type="submit">Save Recipe</button>
    </form>

    <script src="../js/ingredients.js"></script>
    <script src="../js/add_recipe.js"></script>
</body>
</html>
