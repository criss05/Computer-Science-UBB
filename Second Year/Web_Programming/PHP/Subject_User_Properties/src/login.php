<?php
session_start();
require 'db.php';

if ($_SERVER['REQUEST_METHOD']==='POST'){
    $name = trim($_POST['name']);
    $stmt = $pdo->prepare("SELECT id, question FROM users WHERE name = :name");
    $stmt->bindValue(':name', $name, PDO::PARAM_STR);
    $stmt->execute();

    $user = $stmt->fetch(PDO::FETCH_ASSOC);
    if($user){
        $_SESSION['tmp_user_id'] = $user['id'];
        $_SESSION['tmp_user_name'] = $name;
        $_SESSION['tmp_question'] = $user['question'];
        header("Location: question.php");
        exit();
    }
    else{
        $error = "User not found";
    }
}

?>

<form method="POST">
    <h2>Login - Step 1</h2>
    <?php if (isset($error)) echo "<p style='collor:red;'>$error</p>"; ?>
    Name: <input type="text" name="name" required>
    <input type="submit" value="Login">
</form>