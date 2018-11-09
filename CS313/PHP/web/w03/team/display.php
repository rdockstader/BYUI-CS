<!doctype html>
<html lang="en">
    <head>
        <!-- Required meta tags -->
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

        <!-- Bootstrap CSS -->
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">

        <title>Cs313 Week 03 Team Display</title>
    </head>
    <body>
        <?php include '../../partials/header.php' ?>
        <?php $continents = array("na"=>"North America", "sa"=>"South America","eu"=>"Europe","as"=>"Asia","au"=>"Austraila","af"=>"Africa","an"=>"Antarctica") ?>
        <div class="jumbotron jumbotron-fluid">
            <div class="container">
                <h1 class="display-4">CS 313 Team Activity 03</h1>
                <p class="lead">PHP Form Handler.</p>
            </div>
        </div>
        <section class="container">
           <div class="row">
               <div class="col-12">
                   <a href="./" class="btn btn-primary">Back</a>
               </div>
           </div>
            <div class="row pt-4 mt-4">
                <div class="col-12">
                    <p><strong>Name: </strong><?php echo filter_var($_POST['name'], FILTER_VALIDATE_STRING) ?></p>
                    <p><strong>Email: </strong><a href="mailto:<?php echo $_POST['email'] ?>"><?php echo $_POST['email'] ?></a></p>
                    <p><strong>Major: </strong><?php echo $_POST['major'] ?></p>
                    <p><strong>Comments</strong></p>
                    <p><?php echo $_POST['comments'] ?></p>
                    <p><strong>Continents Visited</strong></p>
                    <ul>
                        <?php 
                           foreach($_POST['continents'] as $item) {
                                echo '<li>'.$continents[$item].'</li>';
                           }
                        ?>
                    </ul>
                </div>
            </div>
        </section>
        <?php include '../../partials/footer.php' ?>
        <!-- Optional JavaScript -->
        <!-- jQuery first, then Popper.js, then Bootstrap JS -->
        <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
        <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
    </body>
</html>