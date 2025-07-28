<?php
session_start();
require 'db.php';
if (!isset($_SESSION['user_id'])) {
  header("Location: login.php");
  exit();
}

$popular = null;
if (!empty($_SESSION['search_log'])) {
  $counts = array_count_values($_SESSION['search_log']);
  arsort($counts);
  $topId = array_key_first($counts);

  $stmt = $pdo->prepare("SELECT * FROM properties WHERE id = :id");
  $stmt->bindValue(':id', $topId, PDO::PARAM_INT);
  $stmt->execute();
  $popular = $stmt->fetch();
}
?>

<h2>Most Popular Property</h2>
<?php if ($popular): ?>
  <p><strong><?= htmlspecialchars($popular['address']) ?></strong>: <?= htmlspecialchars($popular['description']) ?></p>
<?php else: ?>
  <p>No searches yet.</p>
<?php endif; ?>
<p><a href="index.php">Back</a></p>
