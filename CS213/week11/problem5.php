<?php
    $x = $_POST["x"];
    $n = $_POST["n"];
?>
<html>
    <head>
        <title>Week 11 : Problem 5</title>
    </head>
    <body>
        <table>
            <tr>
                <th>N</th>
                <th>X<sup>n</sup></th>
            </tr>
          <?php for($i = 1; $i<=$n; $i++) {
              echo "<tr><td>".$i."</td><td>".pow($x, $i)."</td></tr>";
          } ?>
       </table>
    </body>
</html>