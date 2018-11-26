const mongoose = require('mongoose');
const uniqueValidator = require('mongoose-unique-validator');

const userSchema = mongoose.Schema({
    email: { type: String, required: true, unique: true},
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

userSchema.plugin(uniqueValidator);

module.exports = mongoose.model('User', userSchema);
