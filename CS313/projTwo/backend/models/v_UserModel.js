const mongoose = require('mongoose');

const vUserSchema = mongoose.Schema({
    userId: { type: String, required: true},
    email: { type: String, required: true},
    password: { type: String, required: true},
    firstName: { type: String, required: true},
    lastName: { type: String, required: true},
    middleName: { type: String},
    heightInInches: { type: Number, required: true},
    weightInPounds: { type: Number, required: true},
    goalWeightInPounds: { type: Number, required: true},
    genderAtBirth: { type: String, enum: ['Male', 'Female']},
    dateOfBirth: { type: Date, required: true}
});

module.exports = mongoose.model('v_User', vUserSchema);
