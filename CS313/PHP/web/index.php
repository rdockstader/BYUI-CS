<?php session_start(); ?>


<!doctype html>
<html>
	<head>
		<meta charset="utf-8">
		<title>CS313 Home Page</title>
        <?php include 'partials/headlinks.php' ?>
        <?php include 'partials/scripts.php' ?>
	</head>
	<body>
        <?php include 'partials/header.php' ?>
        <div class="jumbotron jumbotron-fluid">
          <div class="container">
            <h1 class="display-4">BYU-I ~ CS313</h1>
            <p class="lead">Page Author: Ryan Dockstader</p>
          </div>
        </div>
        <div class="container">
            <div class="row">
                <div class="col-12">
                    <h2>About Me</h2>
                </div>
                <div class="col-9">
                    <p>I'm from a small town in south eastern Idaho, called Preston. If you think you've heard of that before you just might be right! It was the location of the film Napoleon Dynamite. Growing up in Preston there were a lot of people that grew up on farms, and planned to take over the family farm when they grew up. However, I wasn't one of those kids. From as far back as I can remember I wanted to be an engineer. I didn't know what that meant, or how to spell it but I knew it was what I wanted to be. Somewhere between then and now, I also fell in love with all things technology. From the tech behind rockets to the CPUs in a home computer I wanted (and still do) to learn about it all. I have a passion for learning, and creating. If it's something that I love, I will spend as long as it takes until I know it's the best I can make it. I use that very drive to propel myself forward in learning, the work place, and every other facet of my life.</p>
                </div>
                <div class="col-3">
                    <img src="img/ry-ani.png" alt="Ryan 8 bit" id="8-bit-ani" class="img-fluid mx-auto d-block rounded">
                </div>
            </div>
            <div class="row">
                <div class="col-12">
                    <h2>CS 313</h2>
                    <p class="lead">Web Engineering II</p>
                    <p>
                        Web Engineering II covers more advanced topics in PHP and JavaScript then Web Engineering I does. It allows the student more flexability to learn about each of the concepts on their own and in a group setting, isntead of with the structure of a text book.
                    </p>
                </div>
            </div>
            <div class="row pb-3">
                <div class="col-12">
                    <table class="table table-striped">
                        <thead>
                            <tr>
                                <th scope="col">Week</th>
                                <th scope="col">Team Assignment</th>
                                <th scope="col">Prove Assignment</th>
                            </tr>
                        </thead>
                        <tbody>
                            <tr>
                                <th scope="row">01</th>
                                <td>N/A</td>
                                <td><a href="hello.html">Hello, World!</a></td>
                            </tr>
                            <tr>
                                <th scope="row">02</th>
                                <td><a href="w02/team/">Buttons and Javascript</a></td>
                                <td>This Home Page</td>
                            </tr>
                            <tr>
                                <th scope="row">03</th>
                                <td><a href="w03/team/">PHP Form Handling</a></td>
                                <td><a href="w03/prove/">Pok&#233; Shop</a></td>
                            </tr>
                            <tr>
                                <th scope="row">04</th>
                                <td><a href="w04/sqlFiles/Team.txt" download>Team Database</a></td>
                                <td><a href="w04/sqlFiles/Prove.txt" download>Prove Database</a></td>
                            </tr>
                            <tr>
                                <th scope="row">05</th>
                                <td><a href="w05/team/">Display Query Results</a></td>
				                <td><a href="proj/v1/">Read Only Task Killer</a></td>
                            </tr>
                            <tr>
                                <th scope="row">06</th>
                                <td><a href="w06/team/">Scripture Add Form</a></td>
				                <td><a href="proj/v2/">Task Killer Complete</a></td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
        <?php include 'partials/footer.php' ?>
        <?php include 'partials/scripts.php' ?>
    </body>
</html>
