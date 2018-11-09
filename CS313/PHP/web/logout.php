<?php
    session_start();
    unset($_SESSION["nome"]);  // where $_SESSION["nome"] is your own variable. if you do not have one use only this as follow **session_unset();**
    unset($_SESSION['valid']);
    unset($_SESSION['username']);
    unset($_SESSION['userid']);
    header("Location: /index.php");
    die();
?>
