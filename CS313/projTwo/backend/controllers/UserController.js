const bcrypt = require("bcryptjs");
const jwt = require("jsonwebtoken");

const User = require('../models/UserModel');
const UserVersion = require('../models/v_UserModel');

exports.createUser = (req, res, next) => {
    console.log("Creating user!");
    bcrypt.hash(req.body.password, 10).then(hash => {
        const user = new User({
            email: req.body.email,
            password: hash,
            firstName: req.body.firstName,
            lastName: req.body.lastName,
            middleName: req.body.middleName,
            heightInInches: req.body.heightInInches,
            weightInPounds: req.body.weightInPounds,
            goalWeightInPounds: req.body.goalWeightInPounds,
            genderAtBirth: req.body.genderAtBirth,
            dateOfBirth: req.body.dateOfBirth
        })
        user.save().then(result => {
            if(result) {
                res.status(201).json({message: "User Created!", id: result._id});
            } else {
                res.status(500).json({message: 'User not saved!'});
            }
        }).catch(err => {
            res.status(500).json({message: 'Something went wrong!', error: err});
        });
    })
}
exports.getUser = (req, res, next) => {
    User.findById(req.params.UserID).then(result => {
        if(!result) {
            res.status(404).json({message: 'User not found!'});
        } else {
            res.status(200).json({message: 'User found', user: {
                                                                    userId: result._id,
                                                                    email: result.email,
                                                                    firstName: result.firstName,
                                                                    lastName: result.lastName,
                                                                    middleName: result.middleName,
                                                                    heightInInches: result.heightInInches,
                                                                    weightInPounds: result.weightInPounds,
                                                                    goalWeightInPounds: result.goalWeightInPounds,
                                                                    genderAtBirth: req.body.gender,
                                                                    dateOfBirth: result.dateOfBirth
                                                                }});
        }
    })
}
exports.updateUser = (req, res, next) => {
    // update one user by ID, set all but email and password
    User.findByIdAndUpdate(req.params.UserID,
                            {$set: {
                                firstName: req.body.firstName,
                                lastName: req.body.lastName,
                                middleName: req.body.middleName,
                                heightInInches: req.body.heightInInches,
                                weightInPounds: req.body.weightInPounds,
                                goalWeightInPounds: req.body.goalWeightInPounds,
                                genderAtBirth: req.body.gender,
                                dateOfBirth: req.body.dateOfBirth
                            }}).then(result => {
        if(result) {
            let vers = new UserVersion({
                                            userId: result._id,
                                            email: result.email,
                                            password: result.password,
                                            firstName: result.firstName,
                                            lastName: result.lastName,
                                            middleName: result.middleName,
                                            heightInInches: result.heightInInches,
                                            weightInPounds: result.weightInPounds,
                                            goalWeightInPounds: result.goalWeightInPounds,
                                            genderAtBirth: req.body.gender,
                                            dateOfBirth: result.dateOfBirth
                                        });
            vers.save();
            res.status(200).json({ message: "Update successful"});
        } else {
            res.status(404).json({ message: "User not found"});
        }
    }).catch(err => {
        res.status(500).json({
        message: "User update failed!",
        error: err
        })
    });
}
exports.deleteUser = (req, res, next) => {
    // delete user
    User.findOneAndDelete({_id: req.params.UserID}).then((result) => {
        if(result) {
        res.status(200).json({ message: 'user deleted'});
        } else {
        // couldn't find it....
        res.status(404).json({ message: "User not found!"})
        }
    }).catch(err => {
        // something bad happened, output error to the server console
        // and return a 500 server error
        console.log(err);
        res.status(500).json({
        message: "Delete User Failed!"
        })
    });
}

exports.login = (req, res, next) => {
    let fetchedUser;
    User.findOne({ email: req.body.email})
        .then(user => {
        if(!user) {
            return res.status(404).json({
            message: "No User Found"
            });
        }
        fetchedUser = user;
        return bcrypt.compare(req.body.password, user.password);
        })
        .then(result => {
        if(result.statusCode == 401) {
            return;
        }
        if(!result) {
            return res.status(401).json({
            message: "Invalid authentication credentials"
            });
        }
        const token = jwt.sign({ email: fetchedUser.email, userId: fetchedUser._id }, process.env.JWT_KEY, {expiresIn: "1h"});
        res.status(200).json({
            token: token,
            expiresIn: 3600,
            user: {
                userId: fetchedUser._id,
                email: fetchedUser.email,
                password: null,
                firstName: fetchedUser.firstName,
                lastName: fetchedUser.lastName,
                middleName: fetchedUser.middleName,
                heightInInches: fetchedUser.heightInInches,
                weightInPounds: fetchedUser.weightInPounds,
                goalWeightInPounds: fetchedUser.goalWeightInPounds,
                genderAtBirth: req.body.gender,
                dateOfBirth: fetchedUser.dateOfBirth
            }
        })
        })
        .catch(err => {
        return res.status(401).json({
            message: "Invalid authentication credentials"
        });
        })
}