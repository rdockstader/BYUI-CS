const http = require('http');
var concat = require('concat-stream')


http.get(process.argv[2], function(request) {
    request.setEncoding('utf8');

    request.pipe(concat(function (data) {
        console.log(data.toString().length);
        console.log(data.toString());
    }));
})
