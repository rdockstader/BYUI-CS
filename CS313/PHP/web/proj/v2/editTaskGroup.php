<?php
    session_start();
    include '../../partials/db.php';
    require '../../partials/session.php';
    $taskGroup = null;
    $taskCategories = null;
    if(isset($_SESSION['userid']) && isset($_GET['taskgroupid'])) {
        try 
		{
            $getTaskGroup = $db->prepare('SELECT * FROM ttaskgroups WHERE userid=:userid AND taskgroupid=:taskgroupid');
            $getTaskGroup->bindValue(':userid', $_SESSION['userid'], PDO::PARAM_INT);
            $getTaskGroup->bindValue(':taskgroupid', $_GET['taskgroupid'], PDO::PARAM_INT);
            $getTaskGroup->execute();
            $taskGroup = $getTaskGroup->fetch(PDO::FETCH_ASSOC);
            $getTaskCategories = $db->prepare('SELECT * FROM ttaskgroupcategories');
            $getTaskCategories->execute();
            $taskCategories = $getTaskCategories->fetchAll(PDO::FETCH_ASSOC);
        }
        catch (PDOException $ex)
        {
            echo "Error connecting to DB. Details: $ex";
            die();
        }
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
                    <form action="updatetaskGroup.php" method="post">
                        <div class="form-group">
                            <label for="exampleInputEmail1">Task Group Name</label>
                            <input type="text" class="form-control" id="txt-group-name" name="groupname" value="<?php echo $taskGroup["groupname"]; ?>" placeholder="Enter Group Name">
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
                        <input type="text" value="<?php echo $_GET['taskgroupid']; ?>" name="id" hidden="true">
                        <input type="text" value="true" name="edit" hidden>
                        <button type="submit" class="btn btn-primary">Submit</button>
                    </form>
               </div>
           </div>
        </div>
        <?php include '../../partials/footer.php' ?>
	</body>
</html>
