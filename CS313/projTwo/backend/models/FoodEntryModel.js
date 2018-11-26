const mongoose = require('mongoose');

const foodEntrySchema = mongoose.Schema({
    user: {type: mongoose.Schema.Types.ObjectId, ref: "User", required: true},
    meal: { type: String, enum: ['Breakfast', 'Lunch', 'Dinner', 'Snack'], required: true},
    name: { type: String, required: true},
    calories: { type: Number, required: true},
    protein: { type: Number},
    carbs: { type: Number},
    fats: { type: Number},
    dateAdded: { type: Date, required: true}
});

module.exports = mongoose.model('FoodEntry', foodEntrySchema);
