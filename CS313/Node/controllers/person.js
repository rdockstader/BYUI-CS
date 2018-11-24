var Person = require('../models/Person');
var PersonRelationship = require('../models/PersonRelationship');

exports.FindPersonDisplay = (req, res, next) => {
    res.render('week10/team');
}
