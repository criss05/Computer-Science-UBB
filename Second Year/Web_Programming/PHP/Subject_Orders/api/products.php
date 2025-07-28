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
            $stmt = $pdo->query("SELECT id, name, price FROM products ORDER BY name");
            $products = $stmt->fetchAll(PDO::FETCH_ASSOC);
            echo json_encode($products);
        } catch (PDOException $e) {
            http_response_code(500);
            echo json_encode(['error' => 'Database error while fetching products']);
        }
        break;

    case 'POST':
        $input = json_decode(file_get_contents('php://input'), true);
    
        if (!isset($input['user'], $input['products'])) {
            http_response_code(400);
            echo json_encode(['error' => 'Missing required fields']);
            exit;
        }
    
        try {
            // Start transaction
            $pdo->beginTransaction();

            $stmt = $pdo->prepare("SELECT id FROM users WHERE username= :username");
            $stmt->execute([
                ':username' => $input['user']
            ]);
            $user = $stmt->fetchColumn();

            $total_price = 0;
            $discount = 0;
            $names =[];

            foreach ($input['products'] as $productId) { 
                $stmt = $pdo->prepare("SELECT name, price FROM products WHERE id=:id");
                $stmt->execute([
                    ':id' => $productId
                ]);
                $row = $stmt->fetch(PDO::FETCH_ASSOC);
                if($row){
                    $exploaded = explode("-", $row['name']);
                    $names[]=$exploaded[0];

                    $total_price += $row['price'];
                }
            }

            if (count($names) >= 3){
                $discount = 10;
            }
            
            $frequency = array_count_values($names);
            
            foreach($frequency as $key => $value){
                if ($value >=2){
                    $discount +=5;
                    break;
                }
            }

            $final_price = $total_price - $total_price * ($discount/100);   

             // 🔍 Check last 3 orders for repeated categories
            $stmt = $pdo->prepare("
                SELECT oi.p_id, o.id as order_id
                FROM orders o
                JOIN order_items oi ON o.id = oi.o_id
                WHERE o.u_id = :user
                ORDER BY o.id DESC
                LIMIT 100
            ");
            $stmt->execute([':user' => $user]);
            $orderProducts = $stmt->fetchAll(PDO::FETCH_ASSOC);

            $recentOrders = [];
            foreach ($orderProducts as $entry) {
                $orderId = $entry['order_id'];
                if (!isset($recentOrders[$orderId])) {
                    $recentOrders[$orderId] = [];
                }
                $recentOrders[$orderId][] = $entry['p_id'];
            }

            // Only take the last 3 orders
            $recentOrders = array_slice($recentOrders, 0, 3);

            // Build category map by order
            $categoriesByOrder = [];
            foreach ($recentOrders as $order) {
                $categories = [];
                foreach ($order as $productId) {
                    $stmt = $pdo->prepare("SELECT name FROM products WHERE id = :id");
                    $stmt->execute([':id' => $productId]);
                    $name = $stmt->fetchColumn();
                    $category = explode("-", $name)[0];
                    $categories[] = $category;
                }
                $categoriesByOrder[] = array_unique($categories);
            }

            // Count how many orders each category appears in
            $categoryCount = [];
            foreach ($categoriesByOrder as $orderCategories) {
                foreach ($orderCategories as $cat) {
                    $categoryCount[$cat] = ($categoryCount[$cat] ?? 0) + 1;
                }
            }

            // Check if any category in current order is in all last 3 orders
            $notDiversifying = [];
            foreach (array_unique($names) as $cat) {
                if (isset($categoryCount[$cat]) && $categoryCount[$cat] === 3) {
                    $notDiversifying[] = $cat;
                }
            }
            $diversity=true;
            if ($notDiversifying !== []){
                $diversity=false;
            }

            // Insert order
            $stmt = $pdo->prepare("INSERT INTO orders (u_id, price) VALUES (:user, :price)");
            $stmt->execute([
                ':user' => $user,
                ':price' => $final_price
            ]);
    
            $orderId = $pdo->lastInsertId();
    
            // Link ingredients
            $stmtLink = $pdo->prepare("INSERT INTO order_items (o_id, p_id) VALUES (:o_id, :pid)");
            foreach ($input['products'] as $productId) {
                $stmtLink->execute([
                    ':o_id' => $orderId,
                    ':pid' => $productId
                ]);
            }
            
            $pdo->commit();
    
            echo json_encode(['success' => true, 'totalPrice' => $total_price]);
    
        } catch (PDOException $e) {
            // $pdo->rollBack();
            http_response_code(500);
            echo json_encode(['error' => 'Database error while adding order.','user'=>$user,"warning"=> $diversity]);
        }
        break;
}