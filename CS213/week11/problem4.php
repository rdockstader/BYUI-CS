<?php
    $translater = array(
        "one" => "uno",
        "two" => "dos",
        "three" => "tres",
        "four" => "cuatro",
        "five" => "cinco",
        "six" => "seis",
        "seven" => "siete",
        "eight" => "ocho",
        "nine" => "nueve",
        "ten" => "diez",
        "eleven" => "once",
        "twelve" => "doce",
        "thirteen" => "trece",
        "fourteen" => "catorce",
        "fifteen" => "quince",
        "sixteen" => "dieciséis",
        "seventeen" => "diecisiete",
        "eighteen" => "dieciocho",
        "nineteen" => "diecinueve",
        "twenty" => "veinte"
    );
    $input = $_POST["input4"];
    $output =  $translater[$input];
?>
<html>
    <head>
        <title>Week 11 : Problem 4</title>
    </head>
    <body>
        <p>
    <?php if(isset($output)) {
        echo 'The word "' . $input . '" in Spanish "' . $output . '"';
     } else { 
        echo 'The English cardinal "' . $input . '" is not between "one" and "twenty"';
     } ?>
        </p>
    </body>
</html>
