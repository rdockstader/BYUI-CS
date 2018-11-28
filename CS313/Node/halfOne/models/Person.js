const mongoose = require('mongoose');

const personSchema = mongoose.Schema({
  firstName: { type: String, required: true},
  lastName: { type: String, required: true},
  dateOfBirth: { type: Date}
});

module.exports = mongoose.model('Person', personSchema);
