import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { RecipeListComponent } from './components/recipe-list/recipe-list.component';
import { RecipeDetailsComponent } from './components/recipe-details/recipe-details.component';
import { AddRecipeComponent } from './components/add-recipe/add-recipe.component';
import { AddIngredientsComponent } from './components/add-ingredients/add-ingredients.component';
import { UpdateRecipeComponent } from './components/update-recipe/update-recipe.component';

 export const routes: Routes = [
  { path: '', component: RecipeListComponent },
  { path: 'add-recipe', component: AddRecipeComponent },
  { path: 'recipe/:id', component: RecipeDetailsComponent },
  { path: 'add-ingredients', component: AddIngredientsComponent },
  { path: 'update-recipe/:id', component: UpdateRecipeComponent },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
