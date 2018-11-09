<!doctype html>
<html lang="en">
    <head>
        <!-- Required meta tags -->
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
        <!-- Bootstrap CSS -->
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
        <title>Cs313 Week 03 Team</title>
    </head>
    <body>
       <?php include '../../partials/header.php' ?>
        <div class="jumbotron jumbotron-fluid">
            <div class="container">
                <h1 class="display-4">CS 313 Team Activity 03</h1>
                <p class="lead">PHP Form Handling.</p>
            </div>
        </div>
        <div class="container">
            <form action="display.php" method="post">
                <div class="form-group">
                    <label for="name-input">Name</label>
                    <input type="text" class="form-control" id="name-input" name="name" placeholder="Enter Name">
                </div>
                <div class="form-group">
                    <label for="email-input">Email Address</label>
                    <input type="email" class="form-control" id="email-input" name="email" aria-describedby="emailHelp" placeholder="Enter email">
                    <small id="emailHelp" class="form-text text-muted">We'll never share your email with anyone else.</small>
                </div>
                <!--<div class="form-group">
                    <label for="major-input">Major</label>
                    <select class="form-control" id="major-input">
                        <option>Computer Science</option>
                        <option>Web Design and Development</option>
                        <option>Computer information Technology</option>
                        <option>Computer Engineering</option>
                    </select>
                </div>-->
                <div class="form-group">
                    <label for="major-input">Major</label>
                    <?php 
                        $majors = array((object)["id"=>"cs-radio", "value"=>"Computer Science"], 
                                        (object)["id"=>"wdd-radio", "value"=>"Web Design and Development"], 
                                        (object)["id"=>"cit-radio", "value"=>"Computer information Technology"], 
                                        (object)["id"=>"ce-radio", "value"=>"Computer Engineering"]);
        
                        foreach($majors as $major) {
                           echo '<div class="form-check">';
                            echo '<input class="form-check-input" type="radio" name="major" id="'.$major->id.'" value="'.$major->value.'">';
                            echo '<label class="form-check-label" for="'.$major->id.'">';
                            echo $major->value;
                            echo '</label>';
                            echo '</div>'; 
                        }
                    ?>
                </div>
                <div class="form-group">
                    <label for="comments-input">Comments</label>
                    <textarea class="form-control" id="comments-input" name="comments" rows="3"></textarea>
                </div>
                <!--<div class="form-group">
                    <label for="continents-input">Continents Visited</label>
                    <select multiple class="form-control" id="continents-input">
                        <option>North America</option>
                        <option>South America</option>
                        <option>Europe</option>
                        <option>Asia</option>
                        <option>Australia</option>
                        <option>Africa</option>
                        <option>Antarctica</option>
                    </select>
                </div>-->
                <div class="form-group">
                   <label for="continents-input">Continents Visited</label>
                   <div class="form-check">
                       <input class="form-check-input" name="continents[]" type="checkbox" value="na" id="north-america-check">
                       <label class="form-check-label" for="north-america">
                           North America
                       </label>
                   </div>
                   <div class="form-check">
                       <input class="form-check-input" name="continents[]" type="checkbox" value="sa" id="south-america-check">
                       <label class="form-check-label" for="south-america">
                           South America
                       </label>
                   </div>
                   <div class="form-check">
                       <input class="form-check-input" name="continents[]" type="checkbox" value="eu" id="europe-check">
                       <label class="form-check-label" for="europe-check">
                           Europe
                       </label>
                   </div>
                   <div class="form-check">
                       <input class="form-check-input" name="continents" type="checkbox" value="as" id="asia-check">
                       <label class="form-check-label" for="asia-check">
                           Asia
                       </label>
                   </div>
                   <div class="form-check">
                       <input class="form-check-input" name="continents[]" type="checkbox" value="au" id="australia-check">
                       <label class="form-check-label" for="australia-check">
                           Australia
                       </label>
                   </div>
                   <div class="form-check">
                       <input class="form-check-input" name="continents[]" type="checkbox" value="af" id="africa-check">
                       <label class="form-check-label" for="africa-check">
                           Africa
                       </label>
                   </div>
                   <div class="form-check">
                       <input class="form-check-input" name="continents[]" type="checkbox" value="an" id="antarctica-check">
                       <label class="form-check-label" for="antarctica-check">
                           Antarctica
                       </label>
                   </div>
                </div>
                <button type="submit" class="btn btn-primary">Submit</button>
            </form>
        </div>
        <?php include '../../partials/footer.php' ?>
        <!-- Optional JavaScript -->
        <!-- jQuery first, then Popper.js, then Bootstrap JS -->
        <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
        <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
    </body>
</html>