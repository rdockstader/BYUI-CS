<?php
    session_start();
    include '../../partials/db.php';
    require '../../partials/session.php';
    if(isset($_SESSION['userid'])) {
        try
        {
            $dateString = date("Y-m-d");
            $insertTask = $db->prepare('INSERT INTO tTasks (taskname, taskdesc, taskgroupid, userid, datecreated) VALUES (:taskname, :taskdesc, :taskgroupid, :userid, :date )');
            $insertTask->bindValue(':taskname', $_POST['name'], PDO::PARAM_STR);
            $insertTask->bindValue(':taskdesc', $_POST['desc'], PDO::PARAM_STR);
            $insertTask->bindValue(':taskgroupid', $_POST['taskgroupid'], PDO::PARAM_INT);
            $insertTask->bindValue(':userid', $_SESSION['userid'], PDO::PARAM_INT);
            $insertTask->bindValue(':date', $dateString, PDO::PARAM_STR);
            $insertTask->execute();
        }
        catch (PDOException $ex)
        {
            echo "Error inserting Task. Details: $ex";
            die();
        }    
    }
    $location = "tasks.php?taskgroupid=".$_POST['taskgroupid'];
    
    header("Location: $location");
    //echo 'finished <br>';
    die();
    
?>