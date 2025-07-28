<?php
session_start();
require 'db.php';

if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit();
}

$stmt=$pdo->prepare("SELECT p.id, p.address, p.description
                    FROM properties p
                    JOIN users_properties up ON p.id = up.p_id
                    WHERE up.u_id = :id");
$stmt->bindValue(":id", $_SESSION["user_id"], PDO::PARAM_INT);
$stmt->execute();
$properties = $stmt->fetchAll();

if (isset($_GET['id']) && isset($_GET['delete'])) {
    $propertyId = (int)$_GET['id'];
    $userId = $_SESSION['user_id'];

    // Step 1: Delete this user's association with the property
    $stmt = $pdo->prepare("DELETE FROM users_properties WHERE u_id = :uid AND p_id = :pid");
    $stmt->execute([
        ':uid' => $userId,
        ':pid' => $propertyId
    ]);

    // Step 2: Check if the property still has other owners
    $stmt = $pdo->prepare("SELECT COUNT(*) FROM users_properties WHERE p_id = :pid");
    $stmt->execute([':pid' => $propertyId]);
    $ownerCount = $stmt->fetchColumn();

    // Step 3: If no more owners, delete the property itself
    if ($ownerCount == 0) {
        $stmt = $pdo->prepare("DELETE FROM properties WHERE id = :pid");
        $stmt->execute([':pid' => $propertyId]);
    }
    header("Location: index.php");
    exit();
}
?>

<h2>My properties</h2>
<ul>
  <?php foreach ($properties as $p): ?>
    <li><strong><?= htmlspecialchars($p['address']) ?></strong> - <?= htmlspecialchars($p['description']) ?>
        <form method="GET">
            <input type="hidden" name="id" value="<?= $p['id'] ?>">
            <button type="submit" name="delete">Delete</button>
        </form>
    </li>
  <?php endforeach; ?>
</ul>
<p><a href="index.php">Back</a></p>
