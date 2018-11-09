<?php
    session_start();
    include '../../partials/db.php';
    require '../../partials/session.php';
    try 
    {
      if(isset($_SESSION['userid']) && $_GET['taskgroupid']) 
      {
        echo "User ID: ".$_SESSION['userid']."<br>";
        echo "Task Group ID: ".$_GET['taskgroupid']."<br>";
        $deleteTasks = $db->prepare('DELETE FROM ttasks WHERE userid=:userid AND taskgroupid=:taskgroupid');
        $deleteTasks->bindValue(':userid', $_SESSION['userid'], PDO::PARAM_INT);
        $deleteTasks->bindValue(':taskgroupid', $_GET['taskgroupid'], PDO::PARAM_INT);
        $deleteTasks->execute();
        $returnTask = $deleteTasks->fetchAll(PDO::FETCH_ASSOC);
        print_r($returnTask);
        $deleteTaskGroup = $db->prepare('DELETE FROM ttaskgroups WHERE userid=:userid AND taskgroupid=:taskgroupid');
        $deleteTaskGroup->bindValue(':userid', $_SESSION['userid'], PDO::PARAM_INT);
        $deleteTaskGroup->bindValue(':taskgroupid', $_GET['taskgroupid'], PDO::PARAM_INT);
        $deleteTaskGroup->execute();
        $returnTask = $deleteTaskGroup->fetchAll(PDO::FETCH_ASSOC);
        print_r($returnTask);
      }  
    }
    catch (PDOException $ex)
    {
        echo "Error connecting to DB. Details: $ex";
        die();
    }


    header("Location: index.php");
    die();
    
?>