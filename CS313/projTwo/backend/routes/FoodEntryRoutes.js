const express = require("express");

const foodEntryController = require("../controllers/FoodEntryController");

const router = express.Router();

// CREATE USER
router.post("/", foodEntryController.createFoodEntry);

// READ SINGLE USER BY ID
router.get('/:FoodEntryID', foodEntryController.getFoodEntry);

router.get('/user/:UserID', foodEntryController.getFoodEntriesByUser);

// UPDATE USER
router.put("/:FoodEntryID", foodEntryController.updateFoodEntry);

// DELETE USER
router.delete('/:FoodEntryID', foodEntryController.deleteFoodEntry);

module.exports = router;
