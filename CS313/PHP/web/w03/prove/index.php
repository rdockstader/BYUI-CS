<?php
    if(!isset($_SESSION)) {
        session_start();
    }
    if($_POST["number"]) {
        if(!isset($_SESSION["cart"])) {
            $_SESSION["cart"] = array($_POST["number"]);
        } else {
            $_SESSION["cart"][] = $_POST["number"];
        }
    }
?>

<!doctype html>
<html>
	<head>
		<meta charset="utf-8">
		<title>CS313 Prove 03</title>
        <?php include '../../partials/headlinks.php' ?>
	</head>
	<body>
        
        <?php include '../../partials/header.php' ?>
        <div class="jumbotron jumbotron-fluid">
          <div class="container">
            <h1 class="display-4">Pok&#233; Shop</h1>
            <p class="lead">Page Author: Ryan Dockstader</p>
          </div>
        </div>
        <div class="container mt-3 pt-3">
            <div class="row mb-4">
                <div class="col-9">
                   
                   <?php
                    include '../../partials/poke.php';
                    foreach($pokemon as $p) {
                    echo '<div class="row">';
                    echo '  <div class="col-3">';
                    echo '      <img src="'.$p->img.'" alt="image" class="img-fluid mx-auto d-block rounded">';
                    echo '  </div>';
                    echo '  <div class="col-9">';
                    echo '      <h4>'.$p->name.'</h4>';
                    echo '      <p class="lead">'.$p->number.'</p>';
                    echo '      <p> Price: $'.number_format($p->price, 2).'</p>';
                     echo '      <form method="post" action="'.htmlspecialchars($_SERVER["PHP_SELF"]).'">'; 
                     echo '      <input class="d-none" type="text" value="'.$p->number.'" readonly name="number">';
                    echo '      <button class="btn btn-primary">Add to Cart</button>';
                     echo '      </form>';
                    echo '  </div>';
                    echo '</div>';
                   } ?>        
                </div>
                <div class="col-3">
                    <div class="list-group">
                        <a href="./cart.php" class="list-group-item list-group-item-action">View Cart (<?php if(!$_SESSION["cart"]) { echo 0; } else { echo sizeof($_SESSION["cart"]);}  ?>)</a>
                        <a href="./checkout.php" class="list-group-item list-group-item-action">Checkout</a>
                    </div>
                </div>
            </div>
        </div>
        <?php include '../../partials/footer.php' ?>
        <?php include '../../.partials/scripts.php' ?>
        <script src="script.js"></script>
	</body>
</html>
