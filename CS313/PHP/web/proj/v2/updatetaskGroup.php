<?php
    session_start();
    include '../../partials/db.php';
    require '../../partials/session.php';
    $taskGroups = [];
    if(isset($_SESSION['userid'])) {
        if(isset($_POST['edit']) && isset($_POST['id'])) {
            $updateTaskGroup = $db->prepare('UPDATE ttaskgroups SET groupname = :groupname, category = :category WHERE userid=:userid AND taskgroupid = :taskgroupid');
            $updateTaskGroup->bindValue(':groupname', $_POST['groupname'], PDO::PARAM_INT);
            $updateTaskGroup->bindValue(':category', $_POST['category'], PDO::PARAM_INT);
            $updateTaskGroup->bindValue(':userid', $_SESSION['userid'], PDO::PARAM_INT);
            $updateTaskGroup->bindValue(':taskgroupid', $_POST['id'], PDO::PARAM_INT);
            $updateTaskGroup->execute();
        }
    }

    header("Location: index.php");
    die();
    
?>