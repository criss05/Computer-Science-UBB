<?php
session_start();
if (!isset($_SESSION['user_id'])) {
  header("Location: login.php");
  exit();
}

if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['logout'])) {
    $_SESSION = [];
    session_destroy();
    echo "<h2>You have been logged out.</h2>";
    echo '<p><a href="login.php">Go to login</a></p>';
    exit();
}
?>

<h2>Welcome <?= htmlspecialchars($_SESSION['user_name']) ?></h2>
<form method="POST" style="margin-bottom: 20px;">
  <button type="submit" name="logout">Logout</button>
</form>

<ul>
  <li><a href="search.php">Search Properties</a></li>
  <li><a href="add_property.php">Add or Associate Property</a></li>
  <li><a href="delete_property.php">Delete Associate Property</a></li>
  <li><a href="popular.php">Most Popular Property (Session)</a></li>
  <li><a href="shared_properties.php">Properties (Multiple Owners)</a></li>
</ul>
