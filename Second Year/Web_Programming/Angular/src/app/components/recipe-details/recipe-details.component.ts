import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { HttpClient } from '@angular/common/http';
import { NgFor, NgIf } from '@angular/common';

@Component({
  selector: 'app-recipe-details',
  standalone: true,
  imports: [NgFor, NgIf],
  templateUrl: './recipe-details.component.html',
  styleUrls: ['./recipe-details.component.css']
})
export class RecipeDetailsComponent implements OnInit {
  recipe: any = null;
  ingredients: any[] = [];

  constructor(private route: ActivatedRoute, private http: HttpClient) {}

  ngOnInit(): void {
    const id = this.route.snapshot.paramMap.get('id');
    if (id) {
      this.fetchRecipe(id);
    }
  }

  fetchRecipe(id: string) {
    this.http.get<any>(`http://localhost/Lab7/api/recipes.php?id=${id}`).subscribe(
      data => {
        this.recipe = data;
        this.ingredients = data.ingredients || [];
      },
      error => {
        console.error('Error fetching recipe details:', error);
      }
    );
  }
}
