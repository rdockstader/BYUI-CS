const http = require('http');

http.get(process.argv[2], function(result) {
    result.setEncoding('utf8');
    result.on("data", function(data) {
        console.log(data);
    })
});