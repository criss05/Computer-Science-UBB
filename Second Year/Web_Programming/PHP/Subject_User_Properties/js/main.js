function searchRecipes() {
    const query = document.getElementById('searchInput').value.trim();

    localStorage.setItem("recipeFilter", query);

    fetch(`../api/recipes.php?type=${encodeURIComponent(query)}`)
        .then(res => res.json())
        .then(data => {
            const container = document.getElementById('recipeList');
            container.className = 'container';
            container.innerHTML = '';

            if (data.length === 0) {
                container.innerHTML = '<p>No recipes found.</p>';
            } else {
                data.forEach(recipe => {
                    const recipe_div = document.createElement('div');
                    recipe_div.className = 'recipe';
                    recipe_div.innerHTML = `
                        <h2>${recipe.name}</h2>
                        <p><strong>Author:</strong> ${recipe.author}</p>
                        <p><strong>Type:</strong> ${recipe.type}</p>
                        <p><strong>Description:</strong><br>${recipe.description.replace(/\n/g, "<br>")}</p>
                    `;

                    const delete_button = document.createElement('button');
                    delete_button.textContent = 'X';
                    delete_button.className = 'deleteRecipe'
                    delete_button.onclick = () => {
                        if (confirm(`Are you sure you want to delete the ${recipe.name} recipe?`)) {
                            fetch('../api/recipes.php', {
                                method: "DELETE",
                                headers: { "Content-Type": "application/json" },
                                body: JSON.stringify({ id: recipe.id })
                            }).then(searchRecipes);
                        }
                    }

                    const update_button = document.createElement('button');
                    update_button.textContent = '✎';
                    update_button.className = 'updateRecipe'
                    update_button.onclick = () => {
                        // Redirect to update page with recipe id as query param
                        window.location.href = `update_recipe.php?id=${recipe.id}`;
                    };

                    const details_button = document.createElement('button');
                    details_button.textContent = '🛈';
                    details_button.className = 'detailsRecipe'
                    details_button.onclick = () => {
                        // Redirect to update page with recipe id as query param
                        window.location.href = `details_recipe.php?id=${recipe.id}`;
                    };

                    const buttonContainer = document.createElement('div');
                    buttonContainer.className = 'button-container';

                    buttonContainer.appendChild(details_button);
                    buttonContainer.appendChild(update_button);
                    buttonContainer.appendChild(delete_button);

                    const itemDiv = document.createElement("div");
                    itemDiv.className = "itemDiv";

                    itemDiv.appendChild(recipe_div);
                    itemDiv.appendChild(buttonContainer);
                    container.appendChild(itemDiv);

                });
            }
        })
        .catch(err => {
            console.error(err);
            document.getElementById('recipeList').innerHTML = '<p>Error loading recipes.</p>';
        });
}


document.addEventListener('DOMContentLoaded', () => {
    // Restore filter from localStorage, if available
    const savedQuery = localStorage.getItem("recipeFilter") || "";
    document.getElementById('searchInput').value = savedQuery;
    searchRecipes();
});
