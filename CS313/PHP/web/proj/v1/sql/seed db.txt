-- DROP TABLES

DROP TABLE tTasks;
DROP TABLE tTaskGroups;
DROP TABLE tUsers;
DROP TABLE tTaskGroupCategories;

-- CREATE TABLES

CREATE TABLE tTaskGroupCategories (
	code VARCHAR(5) PRIMARY KEY,
	label VARCHAR(255)
);

CREATE TABLE tUsers (
	UserID SERIAL PRIMARY KEY,
	UserName VARCHAR(255) UNIQUE,
	firstName VARCHAR(255),
	lastName VARCHAR(255),
	Password VARCHAR(255)
);

CREATE TABLE tTaskGroups (
	TaskGroupID SERIAL PRIMARY KEY,
	GroupName VARCHAR(255),
	category VARCHAR(5) REFERENCES tTaskGroupCategories(code),
	UserID INT REFERENCES tUsers(UserID),
	Priority INT
);

CREATE TABLE tTasks (
	TaskID SERIAL PRIMARY KEY,
	TaskName VARCHAR(255),
	TaskDesc TEXT,
	TaskGroupID INT REFERENCES tTaskGroups(TaskGroupID),
	UserID INT REFERENCES tUsers(UserID),
	DateCreated DATE,
	CompletedDate DATE
);

-- Inserts

-- Task Group Categories
INSERT INTO tTaskGroupCategories (code, label) VALUES 
	('SCH', 'School'), 
	('WORK', 'Work'), 
	('HOME', 'Home'),
	('CHRCH', 'Church'), 
	('SH', 'Side Hustle'); 
-- users
INSERT INTO tUsers (username, firstname, lastname, password) VALUES
	('ryan', 'Ryan', 'Dockstader', 'password'),
	('instructor', 'Brother', 'Burton', 'password');
-- Task groups RYAN
INSERT INTO tTaskGroups (groupname, category, userid, priority) VALUES
	('CS 313', 'SCH', 1, 5),
	('CS 246', 'SCH', 1, 5),
	('YouTube', 'SH', 1, 4),
	('Blog', 'SH', 1, 4),
	('Sunday School Presidency', 'CHRCH', 1, 6),
	('Other Church Stuff', 'CHRCH', 1, 6),
	('Training Manuals', 'WORK', 1, 3),
	('Chores', 'HOME', 1, 7),
	('Personal Study Topics', 'HOME', 1, 7);
-- Tasks RYAN
INSERT INTO tTasks (taskname, taskdesc, taskgroupid, userid, datecreated) VALUES
	('Complete Read only project site', 'Project site needs to be completed by the end of this week. It just needs to pull data from the database and display it to the user. Creating a session is a good idea. Probably use the tUSers tabls for this', 1, 1, current_timestamp),
	('Make first Android app','Complete android app assignment. Desc available in canvas.', 2, 1, current_timestamp),
	('Week 05 Group Meeting','Meet with group to cover this weeks team topic', 2, 1, current_timestamp),
	('Final edits for speeding up old computer','Complete and export the current project', 3, 1, current_timestamp),
	('Write post on DC Motors','Should be a companion guide for the planned video release. Script and overview is on google drive', 3, 1, current_timestamp),
	('Prep for next months teacher council','Study the second lesson, pray for each member of the class.', 4, 1, current_timestamp),
	('Contact Bro. Meyers about getting in Wesleys blessing info','Blessing happened on 8/14/2018, need to submit membership info still.', 5, 1, current_timestamp),
	('eCourt Instance Guides','Finish converting setting up an instance guides from .docx to html. .docx guides on \\jove\support\supportTraining', 6, 1, current_timestamp),
	('Do the Dishes','N/A', 7, 1, current_timestamp),
	('Watch kids on friday','Jess is going to go to a play with her family', 7, 1, current_timestamp),
	('CompTIA Network+ cert','Watch course on Udemy and take notes. Then get cert through BATC', 8, 1, current_timestamp),
	('BoM study topic: The Atonement','Pay attention to the Atonement as youre reading the book of mormon.', 8, 1, current_timestamp);
-- Task Groups INSTRUCTOR
INSERT INTO tTaskGroups (groupname, category, userid, priority) VALUES
	('CS 313 Sec 1', 'SCH', 2, 5),
	('CS 313 Sec 2', 'SCH', 2, 5),
	('Church Stuff', 'CHRCH', 2, 6),
	('Chores', 'HOME', 2, 7),
	('Personal Study Topics', 'HOME', 2, 7);
-- tasks INSTRUCTOR
INSERT INTO tTasks (taskname, taskdesc, taskgroupid, userid, datecreated) VALUES
	('Grade W05 assignments','Be sure to give this Ryan fellow an A ;)', 9, 2, current_timestamp),
	('Grade W06 assignments','Be sure to give this Ryan fellow an A ;)', 9, 2, current_timestamp),
	('Grade W07 assignments','Be sure to give this Ryan fellow an A ;)', 9, 2, current_timestamp),
	('Grade W05 assignments','Make sure websites show data from database.', 10, 2, current_timestamp),
	('Grade W06 assignments','Try to update some data', 10, 2, current_timestamp),
	('Grade W07 assignments','Do whatever week 07 required on the proj website', 10, 2, current_timestamp),
	('Get Excited!','2 hour church and more time for family studies is coming this January!', 11, 2, current_timestamp),
	('Do the Dishes','N/A', 12, 2, current_timestamp),
	('Watch kids on friday','Wifey is going to go to a play with her family', 12, 2, current_timestamp),
	('Review personal study topics coming next year','Get on top of the come follow me personal and family materials.', 13, 2, current_timestamp);
	
-- Queries
SELECT
	t.taskname,
	t.taskdesc,
	t.DateCreated,
	t.CompletedDate,
	tg.GroupName,
	u.firstname || ' ' || u.lastname AS userFullName,
	tgc.label AS groupCategory
FROM
	tTasks AS t
	JOIN tTaskGroups AS tg ON (tg.taskgroupid = t.taskgroupid)
	JOIN tUsers AS u ON (u.userid = t.userid)
	JOIN tTaskGroupCategories AS tgc ON (tg.category = tgc.code);
	














