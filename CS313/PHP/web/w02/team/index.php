<!doctype html>
<html>
	<head>
		<meta charset="utf-8">
		<title>CS313 W02 Team Page</title>
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
        <link rel="stylesheet" href="../../style.css">
        <link rel="stylesheet" href="style.css">
        <link href="https://fonts.googleapis.com/css?family=Lato" rel="stylesheet">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
        <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
        <script src="script.js"></script>
	</head>
	<body>
        <?php include '../../partials/header.php' ?>
        <section>
            <h1>CS313 W02 Team Page</h1>
        </section>
		<secton class="container">
            <div class="row">
                 <div class="col-4 bold-hover" id="box-1">
                    Div 1
                </div>
                <div class="col-4 bold-hover" id="box-2">
                    Div 2
                </div>
                <div class="col-4 bold-hover" id="box-3">
                    Div 3
                </div>
            </div>
            <div class="row m-4">
                <div class="col-12">
                    <button class="btn btn-default" onclick="btnClick()">Click Me</button>
                </div>
            </div>
            
            <div class="row mb-3">
                <div class="col-6 m-0">
                    <input class="form-control mb-3" type="text" name="color" id="color">
                    <button class="btn btn-primary" onclick="changeColor()">Change Color</button>
                </div>
            </div>
            <div class="row">
                <div class="col-12">
                    <button class="btn btn-primary" onclick="toggleDiv3()">Toggle Div 3</button>
                </div>
            </div>
        </secton>
        <?php include '../../partials/footer.php' ?>
	</body>
</html>
