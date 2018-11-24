var Person = require('../models/Person');
var PersonRelationship = require('../models/PersonRelationship');

exports.getPerson = (req, res, next) => {
    Person.findById(req.params.PersonID).then(person => {
        res.status(200).json(person);
    })
}

exports.getPersonByFirstName = (req, res, next) => {
    Person.find({firstName: { $regex: '.*' + req.params.firstName + '.*' }}).then(result => {
        console.log(result);
        res.status(200).json(result);
    })
}

exports.createPerson = (req, res, next) => {
    let pers = new Person();
    pers.firstName = req.body.firstName;
    pers.lastName = req.body.lastName;
    pers.dateOfBirth = req.body.dateOfBirth;
    pers.save().then(result => {
        res.status(201).json({message: "Submit successful", id: result.id});
    })
}

exports.createRelationship = (req, res, next) => {
    let persRel = new PersonRelationship();
    persRel.parent = req.body.parent;
    persRel.child = req.body.child;
    persRel.save().then(result => {
        res.status(201).json({message: "Submit successful", id: result.id});
    })
}

exports.getChildren = (req, res, next) => {
    PersonRelationship.find({parent: req.params.PersonID}).populate('child').then(result => {
         res.status(200).json(result);
    })
}

exports.getParents = (req, res, next) => {
    PersonRelationship.find({child: req.params.PersonID}).populate('parent').then(result => {
         res.status(200).json(result);
    })
}