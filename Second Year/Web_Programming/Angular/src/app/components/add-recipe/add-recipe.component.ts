import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { HttpClient } from '@angular/common/http';
import { NgIf, NgFor } from '@angular/common';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-add-recipe',
  standalone: true,
  imports: [NgIf, NgFor, FormsModule],
  templateUrl: './add-recipe.component.html',
  styleUrls: ['./add-recipe.component.css']
})
export class AddRecipeComponent implements OnInit {
  recipe: any = { author: '', name: '', type: '', description: '', ingredients: [] };
  allIngredients: any[] = [];
  selectedIngredients: number[] = [];

  constructor(private route: ActivatedRoute, private http: HttpClient, private router: Router) {}

  ngOnInit(): void {
      this.fetchAllIngredients();
  }

  fetchAllIngredients() {
    this.http.get<any[]>('http://localhost/Lab7/api/ingredients.php').subscribe(
      data => {
        this.allIngredients = data;
      },
      error => console.error('Error fetching ingredients:', error)
    );
  }

  addRecipe() {
    this.http.post(`http://localhost/Lab7/api/recipes.php`, {
      id: this.recipe.id,
      author: this.recipe.author,
      name: this.recipe.name,
      type: this.recipe.type,
      description: this.recipe.description,
      ingredients: this.selectedIngredients
    }).subscribe(
      () => {
        this.router.navigate(['/']);
      },
      error => {
        console.error('Error updating recipe:', error);
      }
    );
  }

  toggleIngredient(ingredientId: number, event: Event) {
    const isChecked = (event.target as HTMLInputElement).checked;
  
    if (isChecked) {
      // Add to selected ingredients
      if (!this.selectedIngredients.includes(ingredientId)) {
        this.selectedIngredients.push(ingredientId);
      }
    } else {
      // Remove from selected ingredients
      this.selectedIngredients = this.selectedIngredients.filter(id => id !== ingredientId);
    }
  }  
}
