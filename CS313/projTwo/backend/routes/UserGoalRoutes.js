const express = require("express");

const userGoalController = require("../controllers/UserGoalController");

const router = express.Router();

// CREATE USER GOAL
router.post("/", userGoalController.createUserGoal);

// READ SINGLE USER GOAL BY ID
router.get('/:UserGoalID', userGoalController.getUserGoal);

// UPDATE USER GOAL
router.put("/:UserGoalID", userGoalController.updateUserGoal);

// DELETE USER GOAL
router.delete('/:UserGoalID', userGoalController.deleteUserGoal);

module.exports = router;
