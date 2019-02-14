const express = require("express");

const userGoalController = require("../controllers/UserGoalController");

const CheckAuth = require('../middleware/check-auth');

const router = express.Router();

// CREATE USER GOAL
router.post("/", CheckAuth, userGoalController.createUserGoal);

// READ CURRENT USWER GOAL
router.get('/', CheckAuth, userGoalController.getUserCurrentGoal);

// READ SINGLE USER GOAL BY ID
router.get('/:UserGoalID', CheckAuth, userGoalController.getUserGoal);

// UPDATE USER GOAL
router.put("/:UserGoalID", CheckAuth, userGoalController.updateUserGoal);

// DELETE USER GOAL
router.delete('/:UserGoalID', CheckAuth, userGoalController.deleteUserGoal);

module.exports = router;
