<?php
session_start();
require 'db.php';
if (!isset($_SESSION['user_id'])) {
  header("Location: login.php");
  exit();
}

$stmt = $pdo->query("
  SELECT p.address, p.description, COUNT(up.u_id) AS owners
  FROM properties p
  JOIN users_properties up ON p.id = up.p_id
  GROUP BY p.id
  HAVING owners > 1
");
$shared = $stmt->fetchAll();
?>

<h2>Properties with Multiple Owners</h2>
<ul>
  <?php foreach ($shared as $row): ?>
    <li><strong><?= htmlspecialchars($row['address']) ?></strong> - <?= htmlspecialchars($row['description']) ?> (<?= $row['owners'] ?> owners)</li>
  <?php endforeach; ?>
</ul>
<p><a href="index.php">Back</a></p>
