var net = require('net');
var sd = require('silly-datetime');
var fs = require('fs');
var gatePort = 3389;
var javaPort = 12345;
var host = getIPAddress();
var gatewayServer = net.createServer().listen(gatePort, '120.25.227.72');
var javaClient = net.createConnection(javaPort, host);
var socket = new HashTable;
var flag = false;
var id = 0x00;

fs.appendFile("gateway.js.log", host);

function getIPAddress() {
    var ans;
    var interfaces = require('os').networkInterfaces();
    for (var devName in interfaces) {
        var iface = interfaces[devName];
        for (var i = 0; i < iface.length; i++) {
            var alias = iface[i];
            if (alias.family === 'IPv4' && alias.address !== '127.0.0.1' && !alias.internal) {
                return alias.address;
            }
        }
    }
}

var entry = new Object();

function HashTable() {
    var size = 0;
    
    this.add = function (key, value) {
        if (!this.containsKey(key)) {
            size++;
        }
        entry[key] = value;
    }
    this.getValue = function (key) {
        return this.containsKey(key) ? entry[key] : null;
    }
    this.remove = function (key) {
        if (this.containsKey(key) && (delete entry[key])) {
            size--;
        }
    }
    this.containsKey = function (key) {
        return (key in entry);
    }
    this.containsValue = function (value) {
        for (var prop in entry) {
            if (entry[prop] == value) {
                return true;
            }
        }
        return false;
    }
    this.getValues = function () {
        var values = new Array();
        for (var prop in entry) {
            values.push(entry[prop]);
        }
        return values;
    }
    this.getKeys = function () {
        var keys = new Array();
        for (var prop in entry) {
            keys.push(prop);
        }
        return keys;
    }
    this.getSize = function () {
        return size;
    }
    this.clear = function () {
        size = 0;
        entry = new Object();
    }
}

javaClient.on('data', function (data) {
    var flag = false;
    var state = 0;
    var length;

    for (var i = 0; i < data.length;) {//12
        if (state == 0 && data[i] == 10) {
         //   console.log('begin');
            state = 1;
            i++;
        }
        else if (state == 1) {
            state = 2;
            length = data[i];

            i++;
        }
        else if (state == 2) {
            if(data[i] == 20 || data[i] == 21) {
                state = 3;
                i += length;
           
            }
            else{
                state = 0;
     
                i += length + 1;
            }
        }
        else if (state == 3) {
            var Id = data[i];
            console.log('id = ' + Id);
            var msg = data.slice(0, i);
            i++;
            state = 0;
            var s = socket.getValue(Id);
            if(s!=null){
                s.write(msg);
            }

            flag = true;
        }
    }
    if(flag)return;
    for (var prop in entry) {
        console.log('send ');
        entry[prop].write(data);
    }
})

javaClient.on('close', function () {
    var time = sd.format(new Date(), 'YYYY-MM-DD HH:mm');
    fs.appendFile("gateway.js.log", time + 'The socket with Java is closed\n');
})
javaClient.on('error', function (err) {
    var time = sd.format(new Date(), 'YYYY-MM-DD HH:mm');
    fs.appendFile("gateway.js.log",'from Java to Client ' + time + err);
})

gatewayServer.on('connection', function (gatewaySocket) {
    id++;
    var thisid = id;
   
    socket.add(id,gatewaySocket);

    gatewaySocket.on('data', function (data) {
        var msg = new Buffer(data.length+1);
        for(var i=0;i<data.length;i++)msg[i] = data[i];
        msg[data.length-1] = id;
        msg[data.length] = 0x00;
        javaClient.write(msg);
    });

    gatewaySocket.on('close', function (data) {
          socket.remove(thisid);
          console.log('user'+thisid+'leave the game');
    });

    gatewaySocket.on('error', function (err) {
        gatewaySocket.destroy();
    });
});
