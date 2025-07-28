import { Component } from '@angular/core';
import { RouterModule, RouterOutlet, Routes } from '@angular/router';
import { bootstrapApplication } from '@angular/platform-browser';
import { importProvidersFrom } from '@angular/core';
import { RecipeListComponent } from './components/recipe-list/recipe-list.component';
import { RecipeDetailsComponent } from './components/recipe-details/recipe-details.component';
import { AddRecipeComponent } from './components/add-recipe/add-recipe.component';
import { AddIngredientsComponent } from './components/add-ingredients/add-ingredients.component';
import { FormsModule } from '@angular/forms';
import { HttpClientModule, provideHttpClient } from '@angular/common/http';
import { UpdateRecipeComponent } from './components/update-recipe/update-recipe.component';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [
    RouterModule
  ],
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'lab8-angular';
}

const routes: Routes = [
  { path: '', component: RecipeListComponent },
  { path: 'add-recipe', component: AddRecipeComponent },
  { path: 'recipe/:id', component: RecipeDetailsComponent },
  { path: 'add-ingredients', component: AddIngredientsComponent },
  { path: 'update-recipe/:id', component: UpdateRecipeComponent },
];

bootstrapApplication(AppComponent, {
  providers: [
    importProvidersFrom(
      RouterModule.forRoot(routes),
      FormsModule,
      HttpClientModule
    )
  ]
}).catch(err => console.error(err));
