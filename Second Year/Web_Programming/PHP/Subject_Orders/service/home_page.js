


document.addEventListener('DOMContentLoaded', async () =>{
    const urlParams = new URLSearchParams(window.location.search);
    const user_name = urlParams.get('name');
    const form = document.querySelector('form');

    form.addEventListener('submit', async (event) => {
        event.preventDefault(); // prevent default form submission

        const formData = new FormData(form);
        const products = [];

        document.querySelectorAll('input[name="products[]"]:checked').forEach(input => {
            products.push(input.value);
        });

        const data = {
            user: user_name,
            products: products
        };

        try {
            const response = await fetch('../api/products.php', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(data)
            });

            const result = await response.json();
            if (response.ok) {
                alert("Price before discount: " + result.totalPrice);
                if(!result.warning){
                    alert("No diversity");
                }
                form.reset();
            } else {
                alert(result.error || 'Failed to add order.');
            }
        } catch (error) {
            console.error('Error:', error);
            alert('Network error while adding order.');
        }
    });

});