const jwt = require("jsonwebtoken");
const User = require("../models/UserModel");



module.exports = (req, res, next) => {
  try {
    const token = req.headers.authorization.split(" ")[1];
    const decodedToken = jwt.verify(token, process.env.JWT_KEY);
    User.findById(decodedToken.userId).then(user => {
      if(user) {
        req.userData = {email: decodedToken.email, userId: decodedToken.userId, userType: user.type};
      next();
      } else {
        res.status(401).json({message: "Auth user not found"})
      }

    });
  } catch (error) {
    console.log(error);
    res.status(401).json({message: "You are not authenticated"});
  }
}
