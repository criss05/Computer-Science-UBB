<?php
require_once '../db/connection.php';

header('Content-Type: application/json');
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, DELETE, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type, Authorization");

$method = $_SERVER['REQUEST_METHOD'];  // GET, POST, DELETE

switch ($method) {
    case 'OPTIONS':
        http_response_code(200);
        exit;
    case 'GET':
        // Fetch all ingredients
        try {
            $stmt = $pdo->query("SELECT id, name FROM ingredients ORDER BY name");
            $ingredients = $stmt->fetchAll(PDO::FETCH_ASSOC);
            echo json_encode($ingredients);
        } catch (PDOException $e) {
            http_response_code(500);
            echo json_encode(['error' => 'Database error while fetching ingredients']);
        }
        break;

    case 'POST':
        // Add new ingredient
        $data = json_decode(file_get_contents('php://input'), true);

        if (!isset($data['name']) || empty($data['name'])) {
            http_response_code(400);
            echo json_encode(['error' => 'Ingredient name is required']);
            exit;
        }

        try {
            // Insert new ingredient
            $stmt = $pdo->prepare("INSERT INTO ingredients (name) VALUES (:name)");
            $stmt->execute([':name' => $data['name']]);
            echo json_encode(['success' => 'Ingredient added successfully']);
        } catch (PDOException $e) {
            http_response_code(500);
            echo json_encode(['error' => 'Database error while adding ingredient']);
        }
        break;

    case 'DELETE':
        // Delete an ingredient
        $data = json_decode(file_get_contents('php://input'), true);

        if (!isset($data['id']) || empty($data['id'])) {
            http_response_code(400);
            echo json_encode(['error' => 'Ingredient ID is required']);
            exit;
        }

        try {
            // Delete the ingredient
            $stmt = $pdo->prepare("DELETE FROM ingredients WHERE id = :id");
            $stmt->execute([':id' => $data['id']]);
            echo json_encode(['success' => 'Ingredient deleted successfully']);
        } catch (PDOException $e) {
            http_response_code(500);
            echo json_encode(['error' => 'Database error while deleting ingredient']);
        }
        break;

    default:
        http_response_code(405);  // Method Not Allowed
        echo json_encode(['error' => 'Method not allowed']);
}
