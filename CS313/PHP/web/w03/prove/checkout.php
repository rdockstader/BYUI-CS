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
                   <div>
                        <h2 class="text-center">Total: $<?php echo number_format($totalPrice, 2) ?></h2>   
                        <form action="confirmation.php" method="post">
                            <div class="form-row">
                                <div class="form-group col-md-6">
                                <label for="inputEmail4">Email</label>
                                <input type="email" class="form-control" id="inputEmail4" placeholder="jondoe@example.com" name="email">
                                </div>
                                <div class="form-group col-md-6">
                                <label for="inputPassword">Full Name</label>
                                <input type="input" class="form-control" id="inputPassword" placeholder="Jon Doe" name="name">
                                </div>
                            </div>
                                <div class="form-group">
                                <label for="inputAddress">Address</label>
                                <input type="text" class="form-control" id="inputAddress" placeholder="1234 Main St" name="address1">
                            </div>
                            <div class="form-group">
                                <label for="inputAddress2">Address 2</label>
                                <input type="text" class="form-control" id="inputAddress2" placeholder="Apartment, studio, or floor" name="address2">
                            </div>
                            <div class="form-row">
                                <div class="form-group col-md-6">
                                    <label for="inputCity">City</label>
                                    <input type="text" class="form-control" id="inputCity" placeholder="Logan" name="city">
                                </div>
                                <div class="form-group col-md-4">
                                    <label for="inputState">State</label>
                                    <input type="text" class="form-control" id="inputState" placeholder="UT" name="state">
                                </div>
                                <div class="form-group col-md-2">
                                    <label for="inputZip">Zip</label>
                                    <input type="text" class="form-control" id="inputZip" placeholder="84321" name="zip">
                                </div>
                            </div>
                            <button type="submit" class="btn btn-primary">Complete Order</button>
                        </form>
                   </div>
                </div>
                <div class="col-3">
                    <div class="list-group">
                        <a href="./" class="list-group-item list-group-item-action">Browse</a>
                        <a href="./cart.php" class="list-group-item list-group-item-action">View Cart (<?php if(!$_SESSION["cart"]) { echo 0; } else { echo sizeof($_SESSION["cart"]);}  ?>)</a>
                    </div>
                </div>
            </div>
        </div>
        <?php include '../../partials/footer.php' ?>
        <?php include '../../.partials/scripts.php' ?>
        <script src="script.js"></script>
	</body>
</html>






