document.addEventListener('DOMContentLoaded', () => {
    const form = document.querySelector('form');

    form.addEventListener('submit', async (event) => {
        event.preventDefault(); // prevent default form submission

        const formData = new FormData(form);
        const ingredients = [];

        document.querySelectorAll('input[name="ingredients[]"]:checked').forEach(input => {
            ingredients.push(input.value);
        });

        const data = {
            author: formData.get('author'),
            name: formData.get('name'),
            type: formData.get('type'),
            description: formData.get('description'),
            ingredients: ingredients
        };

        try {
            const response = await fetch('../api/recipes.php', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(data)
            });

            const result = await response.json();

            if (response.ok) {
                form.reset();
            } else {
                alert(result.error || 'Failed to add recipe.');
            }
        } catch (error) {
            console.error('Error:', error);
            alert('Network error while adding recipe.');
        }
    });
});
