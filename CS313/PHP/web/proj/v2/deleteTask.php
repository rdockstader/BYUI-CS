<?php session_start(); ?>
<?php
    include '../../partials/db.php';
    require '../../partials/session.php';
    try 
    {
      if(isset($_SESSION['userid']) && $_GET['taskid'] && $_GET['taskgroupid']) 
      {
        $deleteTask = $db->prepare('DELETE FROM ttasks WHERE userid=:userid AND taskgroupid=:taskgroupid AND taskid=:taskid');
        $deleteTask->bindValue(':userid', $_SESSION['userid'], PDO::PARAM_INT);
        $deleteTask->bindValue(':taskgroupid', $_GET['taskgroupid'], PDO::PARAM_INT);
        $deleteTask->bindValue(':taskid', $_GET['taskid'], PDO::PARAM_INT);
        $deleteTask->execute();
        $returnTask = $deleteTask->fetchAll(PDO::FETCH_ASSOC);
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