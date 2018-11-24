const http = require('http');
const querystring = require('querystring');

// I really prefer using express.
function onRequest(req, res)
{
    if(req.url == "/home") {
        res.writeHead(200, {'Content-Type': "text/plain"});
        res.write("Welcome to the Home Page");
        res.end();
    } else if(req.url == "/getData") {
        res.writeHead(200, {'Content-Type': "Application/JSON"});
        var json = {};
        json.name = "Br. Burton";
        json.class = "cs313";
        res.write(JSON.stringify(json));
        res.end();

    } else if(req.url.match(/toJson[?]/)) {
        var parsedUrl = querystring.parse(req.url.split('?')[1]);
        
        res.write(JSON.stringify(parsedUrl));
        res.end();
    } else {
        res.writeHead(404);
        res.end();
    }
}


http.createServer(onRequest).listen(8888);


