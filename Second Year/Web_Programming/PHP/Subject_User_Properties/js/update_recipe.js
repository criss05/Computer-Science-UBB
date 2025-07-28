document.addEventListener('DOMContentLoaded', async () => {
    const urlParams = new URLSearchParams(window.location.search);
    const recipeId = urlParams.get('id');
    const form = document.getElementById('addRecipeForm');

    if (!recipeId) {
        alert('No recipe ID provided.');
        return;
    }

    // Fetch ingredients first so we can check them later
    let allIngredients = [];
    try {
        const res = await fetch('../api/ingredients.php');
        allIngredients = await res.json();

        const container = document.getElementById('ingredientsContainer');
        container.innerHTML = '';

        allIngredients.forEach(ingredient => {
            const label = document.createElement('label');
            label.innerHTML = `
                <input type="checkbox" name="ingredients[]" value="${ingredient.id}">
                ${ingredient.name}
            `;
            container.appendChild(label);
        });
    } catch (err) {
        console.error('Failed to load ingredients:', err);
        document.getElementById('ingredientsContainer').innerHTML = '<p>Error loading ingredients.</p>';
        return;
    }

    // Fetch recipe data
    try {
        const res = await fetch(`../api/recipes.php?id=${recipeId}`);
        const recipe = await res.json();

        if (recipe.error) {
            alert(recipe.error);
            return;
        }

        form.elements['author'].value = recipe.author;
        form.elements['name'].value = recipe.name;
        form.elements['type'].value = recipe.type;
        form.elements['description'].value = recipe.description;

        // Check ingredients
        const ingredientIds = recipe.ingredients.map(i => String(i.id));
        document.querySelectorAll('input[name="ingredients[]"]').forEach(input => {
            if (ingredientIds.includes(input.value)) {
                input.checked = true;
            }
        });

    } catch (err) {
        console.error('Failed to fetch recipe:', err);
        alert('Error loading recipe details.');
    }

    // Submit updated data
    form.addEventListener('submit', async (event) => {
        event.preventDefault();

        const formData = new FormData(form);
        const selectedIngredients = [];
        document.querySelectorAll('input[name="ingredients[]"]:checked').forEach(input => {
            selectedIngredients.push(input.value);
        });

        const data = {
            id: recipeId,
            author: formData.get('author'),
            name: formData.get('name'),
            type: formData.get('type'),
            description: formData.get('description'),
            ingredients: selectedIngredients
        };

        try {
            const response = await fetch('../api/recipes.php', {
                method: 'PUT',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(data)
            });

            const result = await response.json();

            if (response.ok) {
                alert('Recipe updated successfully!');
                // Redirect or reload
                window.location.href = 'index.php';
            } else {
                alert(result.error || 'Failed to update recipe.');
            }
        } catch (error) {
            console.error('Error updating recipe:', error);
            alert('Network error while updating recipe.');
        }
    });
});
