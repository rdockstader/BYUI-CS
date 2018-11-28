const fs = require('fs');
const path = require('path');
var fileName = process.argv[2];


function checkPath(fileName) {
    var filter = process.argv[3];
    //console.log(path.extname(fileName) + ':' + filter);
    return path.extname(fileName).substring(1) == filter;
}

fs.readdir(fileName, function(err, data) {
    if(err) {
        console.log(err);
    }
    else {
        data.filter(checkPath).forEach(function (fileName) {
            console.log(fileName);
        })
    }
})