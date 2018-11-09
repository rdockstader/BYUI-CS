<?php
    require './db.php';
    
?>


<!doctype html>
<html lang="en">
    <head>
        <!-- Required meta tags -->
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
        <!-- Bootstrap CSS -->
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
        <title>Cs313 Week 06 Team</title>
    </head>
    <body>
       <?php include '../../partials/header.php' ?>
        <div class="jumbotron jumbotron-fluid">
            <div class="container">
                <h1 class="display-4">Scripture Resouces</h1>
                <p class="lead">Find and display scriptures stored in a backend database, via PHP</p>
            </div>
        </div>
        <div class="container">
           <div class="row">
               <div class="col-12">
                   <a href="./index.php" class="btn btn-secondary">Back</a>
               </div>
           </div>
            <div class="row">
                <div class="col-12">
                    <form action="insert.php" method="post">
                        <div class="form-group">
                            <label for="book-input">Book</label>
                            <input type="text" class="form-control" id="book-input" name="book" placeholder="John">
                        </div>
                        <div class="form-group">
                            <label for="chapter-input">chapter</label>
                            <input type="text" class="form-control" id="chapter-input" name="chapter" placeholder="3">
                        </div>
                        <div class="form-group">
                            <label for="verse-input">Verse</label>
                            <input type="text" class="form-control" id="verse-input" name="verse" placeholder="16">
                        </div>
                        <div class="form-group">
                            <label for="content-input">Content</label>
                            <textarea class="form-control" id="content-input" name="content" rows="3"></textarea>
                        </div>
                        <?php
                            try {
                                $query = 'SELECT * FROM tbltopics;';
                                $statement = $db->prepare($query);
                                $statement->execute();
                                $results = $statement->fetchAll(PDO::FETCH_ASSOC);
                                foreach($results as $row) {
                                    $topicId = $row['topicid'];
                                    $topicName = $row['name'];
                                    echo "<div class='form-check'>";
                                    echo "<input class='form-check-input' type='checkbox' name='topics[]' value='$topicId' id='topic-$topicId'>";
                                    echo "<label class='form-check-label' for='topic-$topicId'>";
                                    echo $topicName;
                                    echo "</label>";
                                    echo "</div>";
                                }
                            } catch (Exception $ex) {
                                echo $ex; // bad practice for prod, good for testing.
                                die();
                            }

                        ?>
                        <button type="submit" class="btn btn-primary mt-3">Submit</button>
                    </form>
                </div>
            </div>
        </div>
        <?php include '../../partials/footer.php' ?>
        <!-- Optional JavaScript -->
        <!-- jQuery first, then Popper.js, then Bootstrap JS -->
        <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
        <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
    </body>
</html>