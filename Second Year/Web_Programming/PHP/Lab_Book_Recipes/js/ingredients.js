document.addEventListener('DOMContentLoaded', () => {
    const container = document.getElementById('ingredientsContainer');

    fetch('../api/ingredients.php')
        .then(response => response.json())
        .then(data => {
            if (!Array.isArray(data)) {
                container.innerHTML = '<p>Error loading ingredients.</p>';
                return;
            }

            data.forEach(ingredient => {
                const label = document.createElement('label');
                label.innerHTML = `
                    <input type="checkbox" name="ingredients[]" value="${ingredient.id}">
                    ${ingredient.name}
                `;
                container.appendChild(label);
            });
        })
        .catch(error => {
            console.error('Failed to load ingredients:', error);
            container.innerHTML = '<p>Error loading ingredients.</p>';
        });
});
