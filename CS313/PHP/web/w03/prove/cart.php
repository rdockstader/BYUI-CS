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
                   <table class="table table-striped">
                       <thead>
                           <tr>
                               <th scope="col">Item</th>
                               <th scope="col">Quantity</th>
                               <th scope="col">Price Per Unit</th>
                           </tr>
                       </thead>
                       <tbody>
                           <?php
                                foreach($cart as $c) {
                                    echo '<tr>';
                                    echo '<td>'.$c->name.'</td>';
                                    echo '<td>'.'1'.'</td>';
                                    echo '<td>$'.number_format($c->price, 2).'</td>';
                                    echo '</tr>';
                                }
                            ?>
                       </tbody>
                   </table>
                    <p class="text-right"><strong>Total:</strong> $<?php echo number_format($totalPrice, 2) ?></p>
                </div>
                <div class="col-3">
                    <div class="list-group">
                        <a href="./" class="list-group-item list-group-item-action">Browse</a>
                        <a href="./checkout.php" class="list-group-item list-group-item-action bg-success text-light">Checkout</a>
                    </div>
                </div>
            </div>
        </div>
        <?php include '../../partials/footer.php' ?>
        <?php include '../../.partials/scripts.php' ?>
        <script src="script.js"></script>
	</body>
</html>






