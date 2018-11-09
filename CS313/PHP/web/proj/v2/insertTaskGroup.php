<?php
    session_start();
    include '../../partials/db.php';
    require '../../partials/session.php';
    $taskGroups = [];
    if(isset($_SESSION['userid'])) {
        try
        {
            $insertTaskGroup = $db->prepare('INSERT INTO ttaskgroups (groupname, category, priority, userid) VALUES (:groupname, :category, :priority, :userid )');
            $insertTaskGroup->bindValue(':groupname', $_POST['groupname'], PDO::PARAM_INT);
            $insertTaskGroup->bindValue(':category', $_POST['category'], PDO::PARAM_INT);
            $insertTaskGroup->bindValue(':priority', $_POST['priority'], PDO::PARAM_INT);
            $insertTaskGroup->bindValue(':userid', $_SESSION['userid'], PDO::PARAM_INT);
            $insertTaskGroup->execute();
        }
        catch (PDOException $ex)
        {
            echo "Error inserting Task Group. Details: $ex";
            die();
        }    
    }
    header("Location: index.php");
    die();
    
?>