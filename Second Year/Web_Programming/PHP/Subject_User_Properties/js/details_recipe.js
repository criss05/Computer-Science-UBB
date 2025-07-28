document.addEventListener('DOMContentLoaded', async () => {
    const urlParams = new URLSearchParams(window.location.search);
    const recipeId = urlParams.get('id');
    const detailsDiv = document.getElementById('recipeDetails');

    if (!recipeId) {
        detailsDiv.innerHTML = '<p>Recipe ID is missing.</p>';
        return;
    }

    try {
        const response = await fetch(`../api/recipes.php?id=${recipeId}`);
        const data = await response.json();

        if (data.error) {
            detailsDiv.innerHTML = `<p>${data.error}</p>`;
            return;
        }

        const ingredientList = data.ingredients.map(ing => `<li>${ing.name}</li>`).join('');

        detailsDiv.innerHTML = `
            <h3>${data.name}</h3>
            <p><strong>Author:</strong> ${data.author}</p>
            <p><strong>Type:</strong> ${data.type}</p>
            <p><strong>Description:</strong><br>${data.description.replace(/\n/g, "<br>")}</p>
            <p><strong>Ingredients:</strong></p>
            <ul>${ingredientList}</ul>
        `;

    } catch (error) {
        console.error('Error fetching recipe details:', error);
        detailsDiv.innerHTML = '<p>Error loading recipe details.</p>';
    }
});
