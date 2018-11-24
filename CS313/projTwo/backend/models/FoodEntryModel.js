const mongoose = require('mongoose');

const foodEntrySchema = mongoose.Schema({
    user: {type: mongoose.Schema.Types.ObjectId, ref: "User"},
    meal: { type: String, enum: ['Breakfast', 'Lunch', 'Dinner', 'Snack'], required: true},
    name: { type: String, required: true},
    calories: { type: Number, required: true},
    protein: { type: Number, required: true},
    carbs: { type: Number, required: true},
    fats: { type: Number, required: true},
    dateAdded: { type: Date, required: true}
});

module.exports = mongoose.model('FoodEntry', foodEntrySchema);
