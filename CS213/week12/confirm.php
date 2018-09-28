<!DOCTYPE html>
<html lang="en">
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <title>eCommerce Site</title>
        <!-- bootstrap for alerts... -->
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
                    <div class="col span-1-of-1">
                        <?php if($_POST['wasSubmit'] == '1') { ?>
                        <div class="alert alert-success">
                            Form Succesfully Submitted
                        </div>
                        <?php } else { ?>
                        <div class="alert alert-danger">
                            Form Canceled
                        </div>
                        <?php } ?>
                    </div>
                </div>
            </div>
        </section>
    </body>
</html>