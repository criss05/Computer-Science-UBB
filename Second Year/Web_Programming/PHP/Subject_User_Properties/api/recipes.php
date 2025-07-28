<?php
require_once '../db/connection.php';

header('Content-Type: application/json');
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type, Authorization");

$method = $_SERVER['REQUEST_METHOD'];  // GET, POST, PUT, DELETE

switch ($method) {
    case 'OPTIONS':
        http_response_code(200);
        exit;
    case 'GET':
        if (isset($_GET['id'])) {
            // Get a single recipe by ID
            $recipeId = $_GET['id'];
            try {
                $stmt = $pdo->prepare("SELECT * FROM recipes WHERE id = :id");
                $stmt->execute([':id' => $recipeId]);
                $recipe = $stmt->fetch(PDO::FETCH_ASSOC);

                if ($recipe) {
                    // Get ingredients for this recipe
                    $stmt = $pdo->prepare("SELECT i.id, i.name FROM ingredients i 
                                           JOIN recipe_ingredients ri ON i.id = ri.ingredient_id
                                           WHERE ri.recipe_id = :recipe_id");
                    $stmt->execute([':recipe_id' => $recipeId]);
                    $ingredients = $stmt->fetchAll(PDO::FETCH_ASSOC);

                    $recipe['ingredients'] = $ingredients;
                    echo json_encode($recipe);
                } else {
                    http_response_code(404);
                    echo json_encode(['error' => 'Recipe not found']);
                }
            } catch (PDOException $e) {
                http_response_code(500);
                echo json_encode(['error' => 'Database error while fetching recipe']);
            }
        } else {
            // Get all recipes
            $type = isset($_GET['type']) ? $_GET['type'] : null;

            try {
                if ($type) {
                    // If a specific type is provided, filter recipes by type
                    $stmt = $pdo->prepare("SELECT id, author, name, description, type FROM recipes WHERE type LIKE :type ORDER BY name");
                    $stmt->execute([':type' => '%' . $type . '%']);
                } else {
                    // Fetch all recipes
                    $stmt = $pdo->query("SELECT id, author, name, description, type FROM recipes ORDER BY name");
                }

                $recipes = $stmt->fetchAll(PDO::FETCH_ASSOC);

                echo json_encode($recipes);
            } catch (PDOException $e) {
                http_response_code(500);
                echo json_encode(['error' => 'Database error while fetching recipes']);
            }
        }
        break;

        case 'POST':
            $input = json_decode(file_get_contents('php://input'), true);
        
            if (!isset($input['author'], $input['name'], $input['type'], $input['description'], $input['ingredients'])) {
                http_response_code(400);
                echo json_encode(['error' => 'Missing required fields']);
                exit;
            }
        
            try {
                // Start transaction
                $pdo->beginTransaction();
        
                // Insert recipe
                $stmt = $pdo->prepare("INSERT INTO recipes (author, name, type, description) VALUES (:author, :name, :type, :description)");
                $stmt->execute([
                    ':author' => $input['author'],
                    ':name' => $input['name'],
                    ':type' => $input['type'],
                    ':description' => $input['description']
                ]);
        
                $recipeId = $pdo->lastInsertId();
        
                // Link ingredients
                $stmtLink = $pdo->prepare("INSERT INTO recipe_ingredients (recipe_id, ingredient_id) VALUES (:rid, :iid)");
                foreach ($input['ingredients'] as $ingredientId) {
                    $stmtLink->execute([
                        ':rid' => $recipeId,
                        ':iid' => $ingredientId
                    ]);
                }
        
                $pdo->commit();
        
                echo json_encode(['success' => true, 'recipe_id' => $recipeId]);
        
            } catch (PDOException $e) {
                $pdo->rollBack();
                http_response_code(500);
                echo json_encode(['error' => 'Database error while adding recipe.']);
            }
            break;
        

    case 'PUT':
        // Update an existing recipe
        $data = json_decode(file_get_contents('php://input'), true);

        if (!isset($data['id'], $data['author'], $data['name'], $data['type'], $data['description'], $data['ingredients'])) {
            http_response_code(400);
            echo json_encode(['error' => 'Missing required fields']);
            exit;
        }

        try {
            // Update the recipe
            $stmt = $pdo->prepare("UPDATE recipes SET author = :author, name = :name, type = :type, description = :description WHERE id = :id");
            $stmt->execute([
                ':author' => $data['author'],
                ':name' => $data['name'],
                ':type' => $data['type'],
                ':description' => $data['description'],
                ':id' => $data['id']
            ]);

            // Remove all previous ingredients
            $stmt = $pdo->prepare("DELETE FROM recipe_ingredients WHERE recipe_id = :recipe_id");
            $stmt->execute([':recipe_id' => $data['id']]);

            // Add the new ingredients
            $stmt = $pdo->prepare("INSERT INTO recipe_ingredients (recipe_id, ingredient_id) VALUES (:recipe_id, :ingredient_id)");
            foreach ($data['ingredients'] as $ingredientId) {
                $stmt->execute([
                    ':recipe_id' => $data['id'],
                    ':ingredient_id' => $ingredientId
                ]);
            }

            echo json_encode(['success' => 'Recipe updated successfully']);
        } catch (PDOException $e) {
            http_response_code(500);
            echo json_encode(['error' => 'Database error while updating recipe']);
        }
        break;
    case 'DELETE':
        // Delete a recipe
        $data = json_decode(file_get_contents('php://input'), true);

        if (!isset($data['id']) || empty($data['id'])) {
            http_response_code(400);
            echo json_encode(['error' => 'Recipe ID is required']);
            exit;
        }

        try {
            // Delete the recipe
            $stmt = $pdo->prepare("DELETE FROM recipes WHERE id = :id");
            $stmt->execute([':id' => $data['id']]);

            // Remove ingredients related to the recipe
            $stmt = $pdo->prepare("DELETE FROM recipe_ingredients WHERE recipe_id = :recipe_id");
            $stmt->execute([':recipe_id' => $data['id']]);

            echo json_encode(['success' => 'Recipe deleted successfully']);
        } catch (PDOException $e) {
            http_response_code(500);
            echo json_encode(['error' => 'Database error while deleting recipe']);
        }
        break;

    default:
        http_response_code(405);  // Method Not Allowed
        echo json_encode(['error' => 'Method not allowed']);
}
