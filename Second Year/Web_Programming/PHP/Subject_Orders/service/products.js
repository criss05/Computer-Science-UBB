document.addEventListener('DOMContentLoaded', () => {
    const container = document.getElementById('productsContainer');

    fetch('../api/products.php')
        .then(response => response.json())
        .then(data => {
            if (!Array.isArray(data)) {
                container.innerHTML = '<p>Error loading products.</p>';
                return;
            }

            data.forEach(product => {
                const label = document.createElement('label');
                label.innerHTML = `
                    <input type="checkbox" name="products[]" value="${product.id}">
                    ${product.name} ~   ${product.price} RON
                `;
                container.appendChild(label);
            });
        })
        .catch(error => {
            console.error('Failed to load products:', error);
            container.innerHTML = '<p>Error loading products.</p>';
        });
});
