// Load the TCP Library
net = require('net');
 
// Keep track of the chat clients
var clients = [];
 
// Start a TCP Server
net.createServer(function (socket) {
 
  console.log("Rove-nasty connected");
 
  // Identify this client
  socket.name = socket.remoteAddress + ":" + socket.remotePort 
 
  // Put this new client in the list
  clients.push(socket);
 
  // Handle incoming messages from clients.
  socket.on('data', function (data) {
	console.log(data.toString('utf-8'));
  });
 
  // Remove the client from the list when it leaves
  socket.on('end', function () {
    clients.splice(clients.indexOf(socket), 1);
  });
  
  // Receive message from rover
  function broadcast(message, sender) {
    // Display on cmd line
    process.stdout.write(message)
  }
 
}).listen(11000);
 
// Put a friendly message on the terminal of the server.
console.log("TCP server running at port 11000\n");

process.stdin.resume();
process.stdin.setEncoding('utf8');

process.stdin.on('data', function (chunk) {
	process.stdout.write('Sent to Rover: ' + chunk + "\n");
	clients.forEach(function (client) {
      client.write(chunk);
    });
});