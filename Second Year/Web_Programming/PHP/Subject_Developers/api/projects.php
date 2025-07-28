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
            $stmt = $pdo->query("SELECT * FROM projects");
            $projects = $stmt->fetchAll(PDO::FETCH_ASSOC);
            echo json_encode($projects);
        }catch(PDOException $e){
            http_response_code(500);
            echo json_encode(['error' => 'Database error while fetching projects']);
        }
        break;

    case 'PUT':
        $data = json_decode(file_get_contents('php://input'), true);

        if (!isset($data['dev'], $data['projects'])){
            http_response_code(400);
            echo json_encode(['error' => 'Missing required fields']);
            exit;
        }

        try{
            $dev = $data['dev'];

            $stmt = $pdo->prepare("SELECT 1 FROM software_developers WHERE name=?");
            $stmt->execute([$dev]);

            if ($stmt->fetchColumn()){
                
                $projects = $data['projects'];

                foreach($projects as $project){
                    $stmt = $pdo->prepare("SELECT 1 FROM projects WHERE name=?");
                    $stmt->execute([$project]);

                    if (!$stmt->fetchColumn()){
                        $stmt = $pdo->prepare("INSERT INTO projects (name, members) VALUES(?,?)");
                        $stmt->execute([$project, $dev]);
                    }else{
                        $stmt = $pdo->prepare("UPDATE projects SET members=CONCAT(members, ', ', ?) WHERE name=?");
                        $stmt->execute([$dev, $project]);
                    }
                }
            }
            else{
                echo json_encode(['success' => 'Developer not in the database']);
            }
        }catch (PDOException $e) {
            http_response_code(500);
            echo json_encode(['error' => 'Database error while adding the projects to the developer']);
        }
}