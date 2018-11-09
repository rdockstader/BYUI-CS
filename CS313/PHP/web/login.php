<?php
    session_start();
    $isLogin = true;
    require './partials/db.php';
    require './partials/session.php';
?>

<!doctype html>
<html>
	<head>
		<meta charset="utf-8">
		<title>CS313 Prove 03</title>
        <?php include './partials/headlinks.php' ?>
	</head>
	<body>
        <?php include './partials/header.php' ?>
        <div class="jumbotron jumbotron-fluid">
          <div class="container">
            <h1 class="display-4">Task Killer!</h1>
            <p class="lead">Organize, and eliminate your tasks</p>
          </div>
        </div>
        <div class="container mt-3 pt-3">
           <div class="row mb-4">
               <div class="col-12">
                <form action="<?php htmlspecialchars($_SERVER["PHP_SELF"]) ?>" method="post">
                    <div class="form-group">
                        <label for="login-username">Username</label>
                        <input type="test" class="form-control" id="login-username" name="username" aria-describedby="emailHelp" placeholder="Enter Username">
                    </div>
                    <div class="form-group">
                        <label for="login-password">Password</label>
                        <input type="password" class="form-control" id="login-password" name="password" placeholder="Password">
                        <small id="emailHelp" class="form-text text-muted">new around here? Visit the <a href="/signup.php">Sign Up</a> page for a new account.</small>
                    </div>
                    <button type="submit" class="btn btn-primary" name="login">Submit</button>
                </form>
               </div>
           </div>
        </div>
        <?php include './partials/footer.php' ?>
	</body>
</html>
