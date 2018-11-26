const FoodEntry = require('../models/FoodEntryModel');

exports.createFoodEntry = (req, res, next) => {
    console.log('creating food entry');
    const foodEntry = new FoodEntry({
        user: req.body.user,
        meal: req.body.meal,
        name: req.body.name,
        calories: req.body.calories,
        protein: req.body.protein,
        carbs: req.body.carbs,
        fats: req.body.fats,
        dateAdded: new Date().setUTCHours(0,0,0,0)
    })
    foodEntry.save().then(result => {
        if(result) {
            res.status(201).json({message: 'Food Entry created', id: result._id})
        } else {
            res.status(500).json({message: 'Food entry not created'})
        }
    }).catch(err => {
        res.status(500).json({message: 'Something went wrong!', error: err});
    })
}

exports.getFoodEntryById = (req, res, next) => {
    FoodEntry.findById(req.params.FoodEntryID).then(result => {
        if(result) {
            res.status(200).json({message: 'Food Entry found.', foodEntry: result});
        } else {
            res.status(404).json({message: 'Food entry not found.'})
        }
    }).catch(err => {
        res.status(500).json({message: 'Something went wrong!', error: err});
    })
}

exports.getFoodEntries = (req, res, next) => {
    req.query.dateAdded = new Date(req.query.dateAdded);
    console.log(req.query);
    FoodEntry.find(req.query).then(result => {
        if(result.length > 0) {
            res.status(200).json({message: 'Food entries found.', foodEntries: result});
        } else {
            res.status(404).json({message: 'No Food entries found'});
        }
    }).catch(err => {
        res.status(500).json({message: 'Something went wrong!', error: err});
    })
}

exports.updateFoodEntry = (req, res, next) => {
    FoodEntry.findByIdAndUpdate(req.params.FoodEntryID,
                                {$set: {
                                    meal: req.body.meal,
                                    name: req.body.name,
                                    calories: req.body.calories,
                                    protein: req.body.protein,
                                    carbs: req.body.carbs,
                                    fats: req.body.fats
                                }}).then(result => {
        if(result) {
            res.status(200).json({message: 'Food Entry Updated.'});
        } else {
            res.status(404).json({message: 'Food entry not found.'})
        }
    }).catch(err => {
        res.status(500).json({message: 'Something went wrong!', error: err});
    })
}

exports.deleteFoodEntry = (req, res, next) => {
    FoodEntry.findByIdAndDelete(req.params.FoodEntryID).then(result => {
        if(result) {
            res.status(200).json({message: 'Food Entry deleted.'});
        } else {
            res.status(404).json({message: 'Food entry not found.'})
        }
    }).catch(err => {
        res.status(500).json({message: 'Something went wrong!', error: err});
    })
}