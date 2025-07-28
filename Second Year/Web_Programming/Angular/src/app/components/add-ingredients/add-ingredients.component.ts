import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { NgIf, NgFor } from '@angular/common';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-add-ingredients',
  standalone: true,
  imports: [NgIf, NgFor, FormsModule],
  templateUrl: './add-ingredients.component.html',
  styleUrls: ['./add-ingredients.component.css']
})
export class AddIngredientsComponent implements OnInit {
  ingredients: any[] = [];
  newIngredientName: string = '';

  constructor(private http: HttpClient) {}

  ngOnInit(): void {
    this.loadIngredients();
  }

  loadIngredients() {
    this.http.get<any[]>('http://localhost/Lab7/api/ingredients.php').subscribe(
      data => {
        this.ingredients = data;
      },
      error => console.error('Error loading ingredients:', error)
    );
  }

  addIngredient() {
    if (this.newIngredientName.trim() === '') {
      alert('Please enter a valid ingredient name.');
      return;
    }

    const ingredientData = {
      name: this.newIngredientName.trim()
    };

    this.http.post('http://localhost/Lab7/api/ingredients.php', ingredientData).subscribe(
      () => {
        this.newIngredientName = '';
        this.loadIngredients(); // Refresh the ingredient list
      },
      error => {
        console.error('Error adding ingredient:', error);
        alert('Failed to add ingredient');
      }
    );
  }

  deleteIngredient(id: number) {
    if (confirm('Are you sure you want to delete this ingredient?')) {
      this.http.request('DELETE', `http://localhost/Lab7/api/ingredients.php`, { body: { id } }).subscribe(
        () => {
          this.ingredients = this.ingredients.filter(ingredient => ingredient.id !== id);
        },
        error => {
          console.error('Error deleting ingredient:', error);
          alert('Failed to delete ingredient');
        }
      );
    }
  }
}
