const express = require("express");

const foodEntryController = require("../controllers/FoodEntryController");

const router = express.Router();

// CREATE USER
router.post("/", foodEntryController.createFoodEntry);

// Read food entires by query params
router.get('/', foodEntryController.getFoodEntries);

// READ SINGLE Food Entry BY ID
router.get('/:FoodEntryID', foodEntryController.getFoodEntryById);

// UPDATE USER
router.put("/:FoodEntryID", foodEntryController.updateFoodEntry);

// DELETE USER
router.delete('/:FoodEntryID', foodEntryController.deleteFoodEntry);

module.exports = router;
