<?php session_start(); ?>
   

<?php
    include '../../partials/db.php';
    require '../../partials/session.php';
    try 
    {
      if(isset($_SESSION['userid']) && $_GET['taskid'] && $_GET['taskgroupid']) 
      {
        $dateString =  date("Y-m-d");
        echo "date: ".$dateString."<br>";
        echo "User ID: ".$_SESSION['userid']."<br>";
          echo "Task Group ID: ".$_GET['taskgroupid']."<br>";
          echo "Task ID: ".$_GET['taskid']."<br>";
        $updateTask = $db->prepare('UPDATE ttasks SET completeddate=:date  WHERE userid=:userid AND taskgroupid=:taskgroupid AND taskid=:taskid');
        $updateTask->bindValue(':date', $dateString, PDO::PARAM_STR);
        $updateTask->bindValue(':userid', $_SESSION['userid'], PDO::PARAM_INT);
        $updateTask->bindValue(':taskgroupid', $_GET['taskgroupid'], PDO::PARAM_INT);
        $updateTask->bindValue(':taskid', $_GET['taskid'], PDO::PARAM_INT);
        $updateTask->execute();
        $returnTask = $updateTask->fetchAll(PDO::FETCH_ASSOC);
        print_r($returnTask);
      }  
    }
    catch (PDOException $ex)
    {
        echo "Error connecting to DB. Details: $ex";
        die();
    }
    $location = "tasks.php?taskgroupid=".$_GET['taskgroupid'];
    
     header("Location: $location");
    die();
    
?>