
<?php session_start(); ?>   

<?php
    include '../../partials/db.php';
    require '../../partials/session.php';
?>
<?php
    $today = new DateTime();
    $tasks = [];
    if(isset($_SESSION['userid']) && isset($_GET['taskgroupid'])) {
        
        $getTasks = $db->prepare('SELECT * FROM ttasks WHERE userid=:userid AND taskgroupid=:taskgroupid');
        $getTasks->bindValue(':userid', $_SESSION['userid'], PDO::PARAM_INT);
        $getTasks->bindValue(':taskgroupid', $_GET['taskgroupid'], PDO::PARAM_INT);
        $getTasks->execute();
        $tasks = $getTasks->fetchAll(PDO::FETCH_ASSOC);
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
                       <a href="./" class="btn btn-secondary">Back</a>
                       <button class="btn btn-primary" type="button" data-toggle="collapse" data-target="#addNewTask" aria-expanded="false" aria-controls="addNewTask">
                                Add New Task
                        </button>
                    </p>
                    <div class="collapse" id="addNewTask">
                        <div class="card card-body">
                            <form action="<?php htmlspecialchars($_SERVER["PHP_SELF"]) ?>" method="post">
                                <div class="form-group">
                                    <label for="name">Task Name</label>
                                    <input type="text" class="form-control" id="name" name="name" placeholder="Enter Task Name">
                                </div>
                                <div class="form-group">
                                    <label for="desc">Task Desc</label>
                                    <textarea class="form-control" id="desc" name="desc" rows="3"></textarea>
                                </div>
                                <button type="submit" class="btn btn-success">Add Task</button>
                            </form>
                        </div>
                    </div>
               </div>
           </div>
            <div class="row mb-4">
                <div class="col-12">
                    <div class="list-group">
                        <?php foreach($tasks as $task) { ?>
                        
                        <form action="<?php htmlspecialchars($_SERVER["PHP_SELF"]) ?>" method="post">
                            <div class="list-group-item list-group-item-action flex-column align-items-start">
                                <div class="d-flex w-100 justify-content-between">
                                    <h5 class="mb-1"> <?php echo $task['taskname'] ?></h5>
                                    <small>Added <?php echo DateTime::createFromFormat('Y-m-d', $task['datecreated'])->diff($today)->d; ?> day(s) ago</small>
                                </div>
                                <p class="mb-1"> <?php echo $task['taskdesc'] ?></p>
                                <input type="text" value=" <?php echo $task['taskid'] ?>" hidden>
                                <button type="submit" class="btn btn-success mt-2">Complete Task</button>
                            </div>
                        </form>
                        <?php  } ?> 
                    </div>
                </div>
            </div>
        </div>
        <?php include '../../partials/footer.php' ?>
	</body>
</html>
