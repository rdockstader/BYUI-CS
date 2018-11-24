const mongoose = require('mongoose');

const userGoalSchema = mongoose.Schema({
    user: {type: mongoose.Schema.Types.ObjectId, ref: "User"},
    dailyCalories: { type: Number, required: true},
    dailyProtein: { type: Number},
    dailyCarbs: { type: Number},
    dailyFats: { type: Number},
    dateAdded: { type: Date, required: true}
});

module.exports = mongoose.model('UserGoal', userGoalSchema);
