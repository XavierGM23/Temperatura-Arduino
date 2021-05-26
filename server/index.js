const http = require('http');
const express = require('express');
const SocketIO = require('socket.io');

const app = express();
const server = http.createServer(app);
const io = require('socket.io')(server);

const serverPort = 3000;

app.use(express.static(__dirname + '/public'));

server.listen(serverPort, () => {
	console.log(`Servidor en el puerto ${serverPort}`);
});

const SerialPort = require('serialport');
const ReadLine = SerialPort.parsers.Readline;

const port = new SerialPort('COM3', {
	baudRate: 9600
});
const parser = port.pipe(new ReadLine({ delimiter: '\r\n' }));

parser.on('open', () => {
	console.log('connection is opened');
});

parser.on('data', (data) => {
	let arr = data.split(',');
	let tempControl = parseInt(arr[0]);
	let tempSet = parseInt(arr[1]);

	console.log(`${tempControl} °C`, `${tempSet} °C`);

	// console.log(typeof(arr[0])); // Devuelve un string

	console.log(arr);

	io.emit('arr', data);
});

parser.on('error', (err) => console.log(err));
port.on('error', (err) => console.log(err));
