<?php
    try 
    {
        if(isset($_POST['login'])  && !empty($_POST['username']) && !empty($_POST['password'])) {
            $stmt = $db->prepare('SELECT * FROM tusers WHERE username=:username');
            $stmt->bindValue(':username', $_POST['username'], PDO::PARAM_STR);
            $stmt->execute();
            $row = $stmt->fetch(PDO::FETCH_ASSOC);
            if(isset($row) && password_verify($_POST['password'], $row['password'])) {
                $_SESSION['valid'] = true;
                $_SESSION['username'] = $_POST['username'];
                $_SESSION['userid'] = $row['userid'];
                //echo "<script>console.log('UserID set to: ".$_SESSION['userid']."');</script>";
                if(isset($_SESSION['redirect']))
                {  
                   header('location: '.$_SESSION['redirect']);
                   unset($_SESSION['redirect']);
                   die(); 
                }
                else 
                {
                    header('location: index.php');
                    die();
                }
                
            } else {
                header('location: /login.php');
                die();
            }

        }
        else if($_SESSION['valid'] != true && !isset($isLogin)){
            header('location: /login.php');
            die();
        }
        //else {
        //    echo "<script>console.log('UserID: ".$_SESSION['userid']."');</script>";
        //}
    }
    catch (PDOException $ex)
    {
      echo 'Error!: ' . $ex->getMessage();
      die();
    } 
?>