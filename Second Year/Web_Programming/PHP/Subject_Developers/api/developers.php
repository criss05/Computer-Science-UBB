<?php
require_once '../db/connection.php';

header('Content-Type: application/json');
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, DELETE, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type, Authorization");

$method = $_SERVER['REQUEST_METHOD'];

switch($method){
    case 'OPTIONS':
        http_response_code(200);
        exit;
    case 'GET':
        try{
            $stmt = $pdo->query("SELECT * FROM software_developers");
            $developers = $stmt->fetchAll(PDO::FETCH_ASSOC);
            echo json_encode($developers);
        }catch(PDOException $e){
            http_response_code(500);
            echo json_encode(['error' => 'Database error while fetching developers']);
        }
        break;
}