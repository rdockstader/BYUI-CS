const jwt = require("jsonwebtoken");



module.exports = (req, res, next) => {
  try {
    const token = req.headers.authorization.split(" ")[1];
    const decodedToken = jwt.verify(token, process.env.JWT_KEY);
      if(decodedToken) {
        req.userData = {username: decodedToken.username, password: decodedToken.password};
        next();
      } else {
        res.status(401).json({message: "Auth user not found"})
      }

  } catch (error) {
    console.log(error);
    res.status(401).json({message: "You are not authenticated"});
  }
}