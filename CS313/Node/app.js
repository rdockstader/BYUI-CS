const express = require('express');
const bodyParser = require('body-parser');
const mongoose = require('mongoose');

const app = express();

/*******************************/
/*********  SETUP  *************/
/*******************************/

// Routers
const indexRoutes = require('./routes/index');
const personApiRoutes = require('./routes/personApi');
const personRoutes = require('./routes/person');

// Connect to MongoDB
const mongoURL = "mongodb://" + process.env.MONGO_UN + ":" + process.env.MONGO_PW + "@" + process.env.MONGO_URL;

mongoose.connect(mongoURL, { useNewUrlParser: true }).then(
    () => {
      console.log('Connected to Database!')
    }).catch(() => {
      console.log('Connection failed!');
    });


// set view engine to ejs
app.set("view engine", "ejs");

// add body parser
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false}));
// set public directory to a static resource
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

// routers
app.use("/", indexRoutes);
app.use('/api/person/', personApiRoutes);
app.use('/person/', personRoutes);

module.exports = app;
