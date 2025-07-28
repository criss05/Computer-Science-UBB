import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { HttpClient } from '@angular/common/http';
import { NgIf, NgFor } from '@angular/common';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-update-recipe',
  standalone: true,
  imports: [NgIf, NgFor, FormsModule],
  templateUrl: './update-recipe.component.html',
  styleUrls: ['./update-recipe.component.css']
})
export class UpdateRecipeComponent implements OnInit {
  recipe: any = { author: '', name: '', type: '', description: '', ingredients: [] };
  allIngredients: any[] = [];
  selectedIngredients: number[] = [];

  constructor(private route: ActivatedRoute, private http: HttpClient, private router: Router) {}

  ngOnInit(): void {
    const id = this.route.snapshot.paramMap.get('id');
    if (id) {
      this.fetchRecipeDetails(id);
      this.fetchAllIngredients();
    }
  }

  fetchRecipeDetails(id: string) {
    this.http.get<any>(`http://localhost/Lab7/api/recipes.php?id=${id}`).subscribe(
      data => {
        this.recipe = data;
        this.selectedIngredients = data.ingredients.map((i: any) => i.id);
      },
      error => console.error('Error fetching recipe details:', error)
    );
  }

  fetchAllIngredients() {
    this.http.get<any[]>('http://localhost/Lab7/api/ingredients.php').subscribe(
      data => {
        this.allIngredients = data;
      },
      error => console.error('Error fetching ingredients:', error)
    );
  }

  updateRecipe() {
    this.http.put(`http://localhost/Lab7/api/recipes.php`, {
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
