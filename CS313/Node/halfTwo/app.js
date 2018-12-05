const express = require('express');
const bodyParser = require('body-parser');
const jwt = require("jsonwebtoken");

const app = express();

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false}));

app.set("view engine", "ejs");
const checkAuth = require('./middleware/check-auth');

app.use(express.static(/*__dirname +*/ "public"));

// Add headers
app.use((req, res, next) => {
    res.setHeader("Access-Control-Allow-Origin", "*");
    res.setHeader(
        "Access-Control-Allow-Headers",
        "Origin, X-Requested-Wih, Content-Type, Accept, Authorization"
    );
    res.setHeader(
        "Access-Control-Allow-Methods",
        "GET, POST, PATCH, PUT, DELETE, OPTIONS"
    );
    next();
});

app.get('/week11', (req, res, next) => {
    res.render("search");
})


app.get('/week12', (req, res, next) => {
    res.render("home");
});

app.post('/login', (req, res, next) => {
    console.log("username: " + req.body.username + " Password " + req.body.password);
    const token = jwt.sign({ username: req.body.username, password: req.body.password }, process.env.JWT_KEY, {expiresIn: "1h"});
    if(token) {
    res.status(200).json({token: token, success: true});
    } else {
        res.status(500).json({message: 'error', success: false})
    }
    
});

app.post('/logout', (req, res, next) => {
    // do logout stuff here.
});

app.get('/getServerTime', checkAuth, (req, res, next) => {
    let time = new Date();
    console.log(time);
    res.status(200).json({time: time});
})


module.exports = app;