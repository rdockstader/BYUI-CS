<?php
    $list = explode(", ", $_POST["input6"]);
    //$list = explode(", ", "HTML, CSS, JavaScript, XML, DTD, XSL, AJAX, PHP, JQuery, JSON, CGI");
    sort($list);
?>
<html>
    <head>
        <title>Week 11 : Problem 6</title>
    </head>
    <body>
        <p>
            <?php for($i = 0; $i < sizeof($list); $i++) {
                echo $list[$i];
                echo "<br>";
            } ?>
        </p>
    </body>
</html>