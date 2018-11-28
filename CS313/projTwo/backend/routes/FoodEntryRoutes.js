const express = require("express");

const foodEntryController = require("../controllers/FoodEntryController");

const CheckAuth = require('../middleware/check-auth');

const router = express.Router();

// CREATE FOOD ENTRY
router.post("/", foodEntryController.createFoodEntry);

// READ FOOD ENTRIES BY QUERY PARAMETERS
router.get('/', CheckAuth, foodEntryController.getFoodEntries);

// READ SINGLE FOOD ENTRY BY ID
router.get('/:FoodEntryID', foodEntryController.getFoodEntryById);

// UPDATE USER
router.put("/:FoodEntryID", foodEntryController.updateFoodEntry);

// DELETE USER
router.delete('/:FoodEntryID', foodEntryController.deleteFoodEntry);

module.exports = router;
