const express = require('express');
const bodyParser = require('body-parser');

const app = express();

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false}));

app.set("view engine", "ejs");

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
    console.log("username: " + req.body.username + " Password " + req.body.password)
});

app.post('/lotout', (req, res, next) => {
    // do logout stuff here.
});

app.get('/getServerTime', (req, res, next) => {
    let time = new Date();
    res.render("serverTime", {time: time});
})


module.exports = app;