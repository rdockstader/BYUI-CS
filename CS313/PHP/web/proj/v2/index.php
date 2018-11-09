<?php
    session_start();
    $_SESSION['redirect'] = "/proj/v2/";
    include '../../partials/db.php';
    require '../../partials/session.php';
    $taskGroups = [];
    if(isset($_SESSION['userid'])) {
        
        $getTaskGroups = $db->prepare('SELECT tg.groupname, tg.priority, tgc.label AS category FROM ttaskgroups tg JOIN ttaskgroupcategories tgc ON TG.category = TGC.code WHERE userid=:userid ORDER BY priority');
        $getTaskGroups->bindValue(':userid', $_SESSION['userid'], PDO::PARAM_INT);
        $getTaskGroups->execute();
        $taskGroups = $getTaskGroups->fetchAll(PDO::FETCH_ASSOC);
        
        $getTaskCategories = $db->prepare('SELECT * FROM ttaskgroupcategories');
        $getTaskCategories->execute();
        $taskCategories = $getTaskCategories->fetchAll(PDO::FETCH_ASSOC);
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
                            <form action="insertTaskGroup.php" method="post">
                                <div class="form-group">
                                    <label for="groupname">Group Name</label>
                                    <input type="text" class="form-control" id="groupname" name="groupname" placeholder="Enter Group Name">
                                </div>
                                <div class="form-group">
                                    <label for="exampleFormControlSelect1">Category</label>
                                    <select class="form-control" id="dd-category" name="category">
                                        <?php try { foreach($taskCategories as $cat) { ?>
                                           <option value="<?php echo $cat['code']; ?>" <?php if($cat['code'] == $taskGroup['category']) { echo 'selected="selected"'; } ?> ><?php echo $cat['label']; ?></option>
                                        <?php  } } 
                                            catch (PDOException $ex)
                                            {
                                                echo "Error connecting to DB. Details: $ex";
                                                die();
                                            } ?> 
                                    </select>
                                </div>
                                <div class="form-group">
                                    <label for="priority">Priority</label>
                                    <input type="number" class="form-control" id="priority" value="3" min="1" name="priority" aria-labelledby="priorityHelp">
                                    <small id="priorityHelp" class="form-text text-muted">1 Is the highest priority item.</small>
                                </div>
                                <button type="submit" class="btn btn-success">Add Group</button>
                            </form>
                        </div>
                    </div>
               </div>
           </div>
            <div class="row mb-4">
                <div class="col-12">
                    <table class="table">
                        <thead>
                            <tr>
                                <th scope="col">Group</th>
                                <th scope="col">Category</th>
                                <th scope="col">Important</th>
                                <th scope="col">Edit</th>
                                <th scope="col">Delete</th>
                            </tr>
                        </thead>
                        <tbody>
                           <?php foreach($taskGroups as $group) { ?>
                               <tr>
                                   <td>
                                       <a href="./tasks.php?taskgroupid=<?php echo $group['taskgroupid']; ?>"><?php echo $group['groupname']; ?></a>
                                   </td>
                                   <td>
                                       <a href="./tasks.php?taskgroupid=<?php echo $group['taskgroupid']; ?>"><?php echo $group['category']; ?></a>
                                   </td>
                                   <td>
                                       <?php if($group['priority'] == 1) {?> <i class="icon ion-md-alert required"></i> <?php } ?>
                                   </td>
                                   <td>
                                       <a href="./editTaskGroup.php?taskgroupid=<?php echo $group['taskgroupid']; ?>" class="btn btn-warning">Edit</a>
                                   </td>
                                   <td>
                                       <a href="./deleteTaskGroup.php?taskgroupid=<?php echo $group['taskgroupid']; ?>" class="btn btn-danger">Delete</a>
                                   </td>
                               </tr>  
                            <?php  } ?> 
                        </tbody>
                    </table>
                    
                    
                </div>
            </div>
        </div>
        <?php include '../../partials/footer.php' ?>
	</body>
</html>
