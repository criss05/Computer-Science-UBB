import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Router } from '@angular/router';
import { CommonModule, NgFor } from '@angular/common';
import { FormsModule, NgModel } from '@angular/forms';

@Component({
  selector: 'app-recipe-list',
  standalone: true,
  imports: [NgFor, FormsModule, CommonModule],
  templateUrl: './recipe-list.component.html',
  styleUrls: ['./recipe-list.component.css']
})

export class RecipeListComponent implements OnInit {
  recipes: any[] = [];
  filteredRecipes: any[] = [];
  searchTerm: string = ''

  constructor(private http: HttpClient, private router: Router) { }

  ngOnInit(): void {
    this.loadSearchTerm();
    this.fetchRecipes();
  }

  loadSearchTerm() {
    const savedSearchTerm = localStorage.getItem('recipeSearchTerm');
    if (savedSearchTerm) {
      this.searchTerm = savedSearchTerm;
    }
  }

  saveSearchTerm() {
    localStorage.setItem('recipeSearchTerm', this.searchTerm);
  }

  fetchRecipes() {
    this.http.get<any[]>('http://localhost/Lab7/api/recipes.php').subscribe(
      data => {
        this.recipes = data;
        this.filterRecipes();
      },
      error => {
        console.error('Error fetching recipes:', error);
      }
    );
  }

  viewRecipeDetails(id: number) {
    this.router.navigate([`/recipe/${id}`]);
  }

  deleteRecipe(id: number) {
    if (confirm('Are you sure you want to delete this recipe?')) {
      this.http.request('DELETE', `http://localhost/Lab7/api/recipes.php`, { body: { id } }).subscribe(
        () => {
          // Remove the deleted recipe from the local list
          this.recipes = this.recipes.filter(recipe => recipe.id !== id);
          alert('Recipe deleted successfully');
        },
        error => {
          console.error('Error deleting recipe:', error);
          alert('Failed to delete recipe');
        }
      );
    }
  }


  updateRecipeDetails(id: number) {
    this.router.navigate([`/update-recipe/${id}`]);
  }


  filterRecipes() {
    this.saveSearchTerm();
    const term = this.searchTerm.toLowerCase();
    if (term !== '') {
      this.filteredRecipes = this.recipes.filter(recipe =>
        recipe.type.toLowerCase().includes(term)
      );
    } else {
      this.filteredRecipes = [...this.recipes];
    }
  }
}
