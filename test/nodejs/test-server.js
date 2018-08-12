//Lets require/import the HTTP module
var http = require('http');
var dispatcher = require('httpdispatcher');

//Lets define a port we want to listen to
const PORT=19000;

//Create a server
var server = http.createServer(handleRequest);

//Lets start our server
server.listen(PORT, function(request, response){
    //Callback triggered when server is successfully listening. Hurray!
    console.log("Server listening on: http://localhost:%s", PORT);
});

//Lets use our dispatcher
function handleRequest(request, response){
    try {
        //log the request on console
        console.log(request.url);
        //Disptach
        dispatcher.dispatch(request, response);
    } catch(err) {
        console.log(err);
    }
}

//A sample GET request
dispatcher.onGet("/events/goals/1", function(req, res) {
    console.log("Goal 1");
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end("{test:test}");
});

//A sample GET request
dispatcher.onGet("/events/goals/2", function(req, res) {
    console.log("Goal 2");
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end("{test:test}");
});
