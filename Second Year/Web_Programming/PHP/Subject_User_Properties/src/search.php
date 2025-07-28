<?php
session_start();
require 'db.php';
if (!isset($_SESSION['user_id'])) {
  header("Location: login.php");
  exit();
}

$matches = [];
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['search'])) {
  $term = '%' . $_POST['search'] . '%';
  $stmt = $pdo->prepare("SELECT * FROM properties WHERE description LIKE :term");
  $stmt->bindValue(':term', $term, PDO::PARAM_STR);
  $stmt->execute();

  $matches = $stmt->fetchAll();
  foreach ($matches as $row) {
    $_SESSION['search_log'][] = $row['id'];
  }
}

?>

<h2>Search Properties</h2>
<form method="POST">
  Description: <input type="text" name="search">
  <input type="submit" value="Search">
</form>

<?php if ($matches): ?>
  <h3>Results:</h3>
  <ul>
    <?php foreach ($matches as $p): ?>
      <li><?= htmlspecialchars($p['address']) ?> - <?= htmlspecialchars($p['description']) ?>
    </li>
    <?php endforeach; ?>
  </ul>
<?php endif; ?>
<p><a href="index.php">Back</a></p>
