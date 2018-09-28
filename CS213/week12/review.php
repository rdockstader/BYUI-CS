<!DOCTYPE html>
<html lang="en">
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <title>eCommerce Site</title>
        <link rel="stylesheet" type="text/css" href="css/grid.css">
        <link rel="stylesheet" type="text/css" href="css/style.css">
        <link rel="stylesheet" type="text/css" href="css/ionicons.min.css">
    </head>
    <body>
        <header>
            <div>
                <a class="nav-button" href="./index.html">Back</a>
            </div>
        </header>
        <section>
            <div class="half-width">
                <div class="row">
                    <h2>Confirm Personal Information</h2>
                    <h3>Please Verify the Information below is correct</h3>
                </div>
                <div class="row">
                    <div class="col span-1-of-5">
                        <h4>Name</h4>
                    </div>
                    <div class="col span-3-of-5">
                        <p><?php echo $_POST["name"] ?></p>
                    </div>
                </div>
                <div class="vertical-spacer-25"></div>
                <div class="row address-div" name="address-div">
                    <div class="col span-1-of-5">
                        <h4>Address</h4>
                    </div>
                    <div class="col span-3-of-5 address-info" name="address-info">
                        <div class="row">
                            <div class="col span-1-of-1">
                                <p><?php echo $_POST["address1"] ?></p>
                            </div>
                        </div>
                        <div class="row">
                            <div class="col span-1-of-1">
                                <p><?php echo $_POST["address2"] ?></p>
                            </div>
                        </div>
                        <div class="row">
                            <div class="col span-1-of-1">
                                <p><?php echo $_POST["address-city"] ?> <?php echo $_POST["address-state"] ?>, <?php echo $_POST["address-zip"] ?></p>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="vertical-spacer-25"></div>
                <div class="row">
                    <div class="col span-1-of-5">
                        <h4>Phone Number</h4>
                    </div>
                    <div class="col span-3-of-5">
                        <p><?php echo $_POST["phone"] ?></p>
                    </div>
                </div>
                <div class="vertical-spacer-50"></div>
                <fieldset>
                    <h2>Shopping Card</h2>
                    <div class="row text-left centered-div">
                        <?php
                        $total = 0;
                        if(!empty($_POST['shopping-card'])) {
                            foreach($_POST['shopping-card'] as $item) { $JSON = json_decode($item); $total = $total + $JSON->cost; ?>
                                   <p> 
                                      <?php 
                                       echo $JSON->type;
                                       echo " - $";
                                       echo $JSON->cost;
                                      ?>
                                   </p>
                            <?php }} ?>
                    </div>
                </fieldset>
                <div class="vertical-spacer-50"></div>
                <div class="row">
                    <div class="col span-1-of-3">
                        <h4>Total</h4>
                    </div>
                    <div>
                        <p id="total-output">$<?php echo $total; ?></p>
                    </div>
                </div>
                <div class="row">
                    <div class="row">
                        <h2>Payment Information</h2>
                    </div>
                    <div class="row">
                        <div class="row">
                            <div class="col span-1-of-5">
                                <h4>Card Type</h4>
                            </div>
                            <div class="col span-3-of-5">
                                <p><?php echo $_POST["credit-card"] ?></p>
                            </div>
                        </div>
                        <div class="row">
                            <div class="col span-1-of-5">
                                <h4>Card Number</h4>
                            </div>
                            <div class="col span-3-of-5">
                                <p>**** **** **** <?php echo substr($_POST["card-number"], -4) ?></p>
                            </div>
                        </div>
                        <div class="row">
                            <div class="col span-1-of-5">
                                <h4>Experation Date</h4>
                            </div>
                            <div class="col span-1-of-5">
                                <p><?php echo $_POST["card-exp-month"] ?> <?php echo $_POST["card-exp-year"] ?></p>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="vertical-spacer-50"></div>
                <div class="vertical-spacer-50"></div>
                <div class="vertical-spacer-50"></div>
                <div class="row">
                    <div class="col span-1-of-2">
                        <form method="post" name="confirm-form" action="./confirm.php">
                            <input type="hidden" name="wasSubmit" value="0">
                            <button type="submit" id="review-cancel" class="submit-button">Cancel</button>
                        </form>
                    </div>
                    <div class="col span-1-of-2">
                        <form method="post" name="confirm-form" action="./confirm.php">
                            <input type="hidden" name="wasSubmit" value="1">
                            <button type="submit" id="review-submit" class="submit-button">Submit</button>
                        </form>
                    </div>
                </div>
            </div>
        </section>
    </body>
</html>