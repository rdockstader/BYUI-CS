const mongoose = require('mongoose');

const userGoalSchema = mongoose.Schema({
    user: {type: mongoose.Schema.Types.ObjectId, ref: "User", required: true},
    dailyCalories: { type: Number, required: true},
    dailyProtein: { type: Number},
    dailyCarbs: { type: Number},
    dailyFats: { type: Number},
    dateAdded: { type: Date, required: true},
    dateReplaced: { type: Date}
});

module.exports = mongoose.model('UserGoal', userGoalSchema);
