document.addEventListener("DOMContentLoaded", () => {
    const itemList = document.getElementById("itemList");
    const input = document.getElementById("itemInput");
    const addButton = document.getElementById("addItemButton");

    // Load ingredients from backend
    function loadIngredients() {
        fetch("../api/ingredients.php")
            .then(res => res.json())
            .then(data => {
                ingredientsList.innerHTML = "";
                data.forEach(item => {
                    appendIngredient(item.id, item.name);
                });
            })
            .catch(err => {
                console.error("Error fetching ingredients:", err);
                ingredientsList.innerHTML = "<li>Error loading ingredients.</li>";
            });
    }

    // Add new ingredient
    addIngredientButton.addEventListener("click", () => {
        const name = addIngredientInput.value.trim();
        if (!name) {
            alert("Please enter an ingredient.");
            return;
        }

        fetch("../api/ingredients.php", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ name })
        })
        .then(res => res.json())
        .then(result => {
            if (result.success) {
                loadIngredients(); // Refresh list
                input.value = "";
            } else {
                alert(result.error || "Failed to add ingredient.");
            }
        })
        .catch(err => console.error("Add error:", err));
    });

    // Append item to the list
    function appendIngredient(id, name) {
        const li = document.createElement("li");
        li.textContent = name + " ";

        const delete_button = document.createElement("button");
        delete_button.textContent = "X";
        delete_button.className='deleteIngredientButton'
        delete_button.addEventListener("click", () => {
            if (!confirm(`Do you want to delete "${name}"?`)) return;

            fetch("../api/ingredients.php", {
                method: "DELETE",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify({ id })
            })
            .then(res => res.json())
            .then(result => {
                if (result.success) {
                    loadIngredients();
                } else {
                    alert(result.error || "Failed to delete ingredient.");
                }
            })
            .catch(err => console.error("Delete error:", err));
        });

        li.appendChild(delete_button);
        ingredientsList.appendChild(li);
    }

    loadIngredients(); // Initial load
});
