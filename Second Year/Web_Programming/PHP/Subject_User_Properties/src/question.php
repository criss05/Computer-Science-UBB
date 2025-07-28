<?php
session_start();
require 'db.php';

if (!isset($_SESSION['tmp_user_id'])) {
    header("Location: login.php");
    exit();
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $answer = trim($_POST['answer']);
    $stmt = $pdo->prepare("SELECT answer FROM users WHERE id = :id");
    $stmt->bindValue(":id", $_SESSION['tmp_user_id'], PDO::PARAM_INT);
    $stmt->execute();
    
    $row = $stmt->fetch(PDO::FETCH_ASSOC);
    if($row){
        if (strcasecmp($row['answer'], $answer) === 0) {
            $_SESSION['user_id'] = $_SESSION['tmp_user_id'];
            $_SESSION['user_name'] = $_SESSION['tmp_user_name'];
            $_SESSION['search_log'] = [];
            unset($_SESSION['tmp_user_id'], $_SESSION['tmp_user_name'], $_SESSION['tmp_question']);
            header("Location: index.php");
            exit();
        } else {
            $error = "Incorrect answer.";
        }
    }
}
?>

<h2>Login - Step 2</h2>
<p>Question: <?= htmlspecialchars($_SESSION['tmp_question']) ?></p>
<form method="POST">
    Answer: <input type="text" name="answer" required>
    <input type="submit" value="Login">
</form>
<?php if (isset($error)) echo "<p style='color:red;'>$error</p>"; ?>
