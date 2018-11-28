var fs = require('fs');
var fileName = process.argv[2]

var fileOutput = fs.readFileSync(fileName).toString();

var lines = fileOutput.split('\n');

console.log((lines.length -1));