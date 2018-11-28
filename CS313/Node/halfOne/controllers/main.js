exports.indexPage = (req, res, next) => {
    res.render("home");
}

var doMath = function(numberOne, numberTwo, operator) {
    let total = -1;
    switch (operator) {
        case '*':
            total = numberOne * numberTwo;
            break;
        case '/':
            total = numberOne / numberTwo;
            break;
        case '+':
            total = +numberOne + +numberTwo;
            break;
        case '-':
            total = numberOne - numberTwo;
            break;
    }

    return total;
}

exports.week09Team = (req, res, next) => {
    res.render("week09/team/");
}

exports.week09TeamMaths = (req, res, next) => {
    const lhs = req.body.numberOne;
    const rhs = req.body.numberTwo;
    let total = doMath(lhs, rhs, req.body.operator);
    
    res.render("week09/team/maths", {rhs: rhs, lhs: lhs, total: total, operator: req.body.operator});
}

exports.week09TeamMathService = (req, res, next) => {
    const lhs = req.body.numberOne;
    const rhs = req.body.numberTwo;
    let total = doMath(lhs, rhs, req.body.operator);
    res.status(200).json({total: total});
}

exports.week09Prove = (req, res, next) => {
    res.render("week09/prove/index", {});
}

exports.wek09GetPostalRate = (req, res, next) => {
    // Build postal rate JSON objects
    const lettersStamped = [
        {"weight":1, "cost":0.50}, 
        {"weight":2, "cost":0.71}, 
        {"weight":3, "cost":0.92},
        {"weight":3.5, "cost":1.13}
    ];
    const lettersMetered = [
        {"weight":1, "cost":0.47}, 
        {"weight":2, "cost":0.68}, 
        {"weight":3, "cost":0.89},
        {"weight":3.5, "cost":1.10}
    ];
    const largeEnvelopes = [
        {"weight":1, "cost":1.00},
        {"weight":2, "cost":1.21},
        {"weight":3, "cost":1.42},
        {"weight":4, "cost":1.63},
        {"weight":5, "cost":1.84},
        {"weight":6, "cost":2.05},
        {"weight":7, "cost":2.26},
        {"weight":8, "cost":2.47},
        {"weight":9, "cost":2.68},
        {"weight":10, "cost":2.89},
        {"weight":11, "cost":3.10},
        {"weight":12, "cost":3.31},
        {"weight":13, "cost":3.52}
    ];
    const firstClassPackageService = [
        {"weight":1, "cost":3.50},
        {"weight":2, "cost":3.50},
        {"weight":3, "cost":3.50},
        {"weight":4, "cost":3.50},
        {"weight":5, "cost":3.75},
        {"weight":6, "cost":3.75},
        {"weight":7, "cost":3.75},
        {"weight":8, "cost":3.75},
        {"weight":9, "cost":4.10},
        {"weight":10, "cost":4.45},
        {"weight":11, "cost":4.80},
        {"weight":12, "cost":5.15},
        {"weight":13, "cost":5.50}
    ]; 
    let weightClass = 0.0;
    let i = 0;
    let cost = -1;
    switch(req.body.type) {
        case 'letStamp':
            if(req.body.weight > lettersStamped[lettersStamped.length-1].weight) {
                cost = "Too heavy!";
            }
            else {
                while(weightClass < req.body.weight && i < lettersStamped.length) {
                    weightClass = lettersStamped[i].weight;
                    cost = lettersStamped[i].cost;
                    i++;
                }
            }
            break;
        case 'letMeter':
            if(req.body.weight > lettersMetered[lettersMetered.length-1].weight) {
                cost = "Too heavy!";
            }
            else {
                while(weightClass < req.body.weight && i < lettersMetered.length) {
                    weightClass = lettersMetered[i].weight;
                    cost = lettersMetered[i].cost;
                    i++;
                }
            }
            break;
        case 'lrgEnv':
            if(req.body.weight > largeEnvelopes[largeEnvelopes.length-1].weight) {
                cost = "Too heavy!";
            }
            else {
                while(weightClass < req.body.weight && i < largeEnvelopes.length) {
                    weightClass = largeEnvelopes[i].weight;
                    cost = largeEnvelopes[i].cost;
                    i++;
                }
            }
            break;
        case 'fcpsr':
            if(req.body.weight > firstClassPackageService[firstClassPackageService.length-1].weight) {
                cost = "Too heavy!";
            }
            else {
                while(weightClass < req.body.weight && i < firstClassPackageService.length) {
                    weightClass = firstClassPackageService[i].weight;
                    cost = firstClassPackageService[i].cost;
                    i++;
                }
            }
            break;
        default:
            res.status(404).json({message: "TYPE NOT FOUND"});
            break;
    }

    res.status(200).json({message: "Rate fetch successful", rate: cost});
}