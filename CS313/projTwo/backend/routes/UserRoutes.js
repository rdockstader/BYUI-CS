const express = require("express");

const userController = require("../controllers/UserController");

const router = express.Router();

// CREATE USER
router.post("/", userController.createUser);

// READ SINGLE USER BY ID
router.get('/:UserID', userController.getUser);

// UPDATE USER
router.put("/:UserID", userController.updateUser);

// DELETE USER
router.delete('/:UserID', userController.deleteUser);

// LOGIN USER
router.post("/login", userController.login);

module.exports = router;
