const UserGoal = require('../models/UserGoalModel');


exports.createUserGoal = (req, res, next) => {
    console.log('Creating User Goal');
    let userGoal = new UserGoal({
        user: req.body.UserID,
        dailyCalories: req.body.dailyCalories,
        dailyProtein: req.body.dailyProtein,
        dailyCarbs: req.body.dailyCarbs,
        dailyFats: req.body.dailyFats,
        dateAdded: new Date()
    })
    userGoal.save().then(result => {
        if(result) {
            res.status(201).json({message: 'User Goal created!', id: result._id});
        } else {
            res.status(500).json({message: 'Something went wrong :('})
        }
    }).catch(err => {
        res.status(500).json({message: 'Something went wrong!', error: err})
    })
}

exports.getUserGoal = (req, res, next) => {
    UserGoal.findById(req.params.UserGoalID).then(result => {
        if(result) {
            res.status(200).json({message: 'User goal found', userGoal: result});
        } else {
            res.status(404).json({message: 'User goal not found'});
        }
    }).catch(err => {
        res.status(500).json({message: 'Something went wrong!', error: err});
    })
}

exports.updateUserGoal = (req, res, next) => {
    UserGoal.findByIdAndUpdate(req.params.UserGoalID, 
        {$set: {
            dailyCalories: req.body.dailyCalories,
            dailyProtein: req.body.dailyProtein,
            dailyCarbs: req.body.dailyCarbs,
            dailyFats: req.body.dailyFats
    }}).then(result => {
        if(result) {
            res.status(200).json({message: 'User goal updated'});
        } else {
            res.status(404).json({message: 'User goal not found'});
        }
    }).catch(err => {
        res.status(500).json({message: 'Something went wrong!', error: err});
    })
}

exports.deleteUserGoal = (req, res, next) => {
    UserGoal.findByIdAndDelete(req.params.UserGoalID).then(result => {
        if(result) {
            res.status(200).json({message: 'User goal Deleted'});
        } else {
            res.status(404).json({message: 'User goal not found'});
        }
    }).catch(err => {
        res.status(500).json({message: 'Something went wrong!', error: err});
    })    
}