const mongoose = require('mongoose');

const personRelationshipSchema = mongoose.Schema({
  parent: {type: mongoose.Schema.Types.ObjectId, ref: "Person"},
  child: {type: mongoose.Schema.Types.ObjectId, ref: "Person"}
});

module.exports = mongoose.model('PersonRelationship', personRelationshipSchema);
