<?php session_start(); ?>
   

<?php
    $_SESSION['redirect'] = "/proj/v1/";
    include '../../partials/db.php';
    require '../../partials/session.php';
    $taskGroups = [];
    if(isset($_SESSION['userid'])) {
        
        $getTaskGroups = $db->prepare('SELECT * FROM ttaskgroups WHERE userid=:userid');
        $getTaskGroups->bindValue(':userid', $_SESSION['userid'], PDO::PARAM_INT);
        $getTaskGroups->execute();
        $taskGroups = $getTaskGroups->fetchAll(PDO::FETCH_ASSOC);
    }
    
?>

<!doctype html>
<html>
	<head>
		<meta charset="utf-8">
		<title>CS313 Prove 03</title>
        <?php include '../../partials/headlinks.php' ?>
	</head>
	<body>
        
        <?php include '../../partials/header.php' ?>
        <div class="jumbotron jumbotron-fluid">
          <div class="container">
            <h1 class="display-4">Task Killer!</h1>
            <p class="lead">Organize, and eliminate your tasks</p>
          </div>
        </div>
        <div class="container mt-3 pt-3">
           <div class="row mb-4">
               <div class="col-12">
                    <p>
                        <button class="btn btn-primary" type="button" data-toggle="collapse" data-target="#addNewTaskGroup" aria-expanded="false" aria-controls="addNewTaskGroup">
                            Add New Task Group
                        </button>
                    </p>
                    <div class="collapse" id="addNewTaskGroup">
                        <div class="card card-body">
                            <form action="<?php htmlspecialchars($_SERVER["PHP_SELF"]) ?>" method="post">
                                <div class="form-group">
                                    <label for="groupname">Group Name</label>
                                    <input type="text" class="form-control" id="groupname" name="groupname" placeholder="Enter Group Name">
                                </div>
                                <button type="submit" class="btn btn-success">Add Group</button>
                            </form>
                        </div>
                    </div>
               </div>
           </div>
            <div class="row mb-4">
                <div class="col-12">
                    <div class="list-group">
                        <?php foreach($taskGroups as $group) { ?>
                        <a href="./tasks.php?taskgroupid=<?php echo $group['taskgroupid']; ?>" class="list-group-item list-group-item-action"><?php echo $group['groupname']; ?></a>    
                        <?php  } ?> 
                    </div>
                </div>
            </div>
        </div>
        <?php include '../../partials/footer.php' ?>
	</body>
</html>
