<?php
    require("db.php");
    try
    {
        $query = 'INSERT INTO tScriptures(book, chapter, verse, content) VALUES(:book, :chapter, :verse, :content)';
        $statement = $db->prepare($query);
        $statement->bindValue(':book', $_POST['book']);
        $statement->bindValue(':chapter', $_POST['chapter']);
        $statement->bindValue(':verse', $_POST['verse']);
        $statement->bindValue(':content', $_POST['content']);
        $statement->execute();
        $scriptureId = $db->lastInsertId("tscriptures_scriptureid_seq");
        foreach ($_POST['topics'] as $topic)
        {
            echo 'Scripture ID: '.$scriptureId.' Topic ID: '.$topic;
            $statement = $db->prepare('INSERT INTO tblScriptures_topics(scriptureId, topicId) VALUES(:scriptureId, :topicId)');
            $statement->bindValue(':scriptureId', $scriptureId);
            $statement->bindValue(':topicId', $topic);
            $statement->execute();
        }
    }
    catch (Exception $ex)
    {
        echo $ex; // bad practice for prod, good for testing.
        die();
    }

    header("Location: index.php");
    die(); 
?>