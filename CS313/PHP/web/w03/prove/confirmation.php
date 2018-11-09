<?php
    include '../../partials/poke.php';
    if(!isset($_SESSION)) {
        session_start();
    }
    $cart = array();
    $totalPrice = 0;
    if($_SESSION["cart"]) {
        foreach($_SESSION["cart"] as $num) {
            $key = array_search($num, array_column($pokemon, 'number'));
            if(isset($key)) {
                $cart[] = $pokemon[$key];
                $totalPrice += $pokemon[$key]->price;
            }
        }
        $_SESSION["cart"] = array();
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
           <div class="row">
               <div class="col-12">
                   <?php if(isset($_POST)) { ?>
                   <div class="alert alert-success" role="alert">
                      The Order has been successfully placed!
                   </div>
                   <?php } ?>
               </div>
           </div>
            <div class="row mb-4">
                <div class="col-9">
                    <div class="card" style="width: 18rem;">
                        <div class="card-body">
                            <h5 class="card-title"><?php echo filter_var($_POST["name"], FILTER_SANITIZE_STRING); ?></h5>
                            <h6 class="card-subtitle mb-2 text-muted"><?php echo filter_var($_POST["email"], FILTER_SANITIZE_STRING); ?></h6>
                            <div class="card-text"><?php echo filter_var($_POST["address1"], FILTER_SANITIZE_STRING)." ".filter_var($_POST["address2"], FILTER_SANITIZE_STRING)
                                                                ."<br>".filter_var($_POST["city"], FILTER_SANITIZE_STRING).", ".filter_var($_POST["state"], FILTER_SANITIZE_STRING)
                                                                ." ".filter_var($_POST["zip"], FILTER_SANITIZE_STRING)."<br>"."Charged: <strong>".number_format($totalPrice, 2)."</strong>";  ?></div>
                        </div>
                    </div>
                </div>
                <div class="col-3">
                    <div class="list-group">
                        <a href="./" class="list-group-item list-group-item-action">Browse</a>
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
