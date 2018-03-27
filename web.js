const express = require('express');
const app = express();
const fs = require('fs');

var seq = 0;

//sample
app.get('/', (req, res) => res.send('Hello World!\n'));

//sample
app.get('/log', function(req, res){
	console.log("%j", req.query);
	res.end(seq++);
});

//acutal implementation
app.get('/update', function(req, res){

	//get time using getUTC
	var tempdate = new Date();
	var year = tempdate.getUTCFullYear();	
	var month = tempdate.getUTCMonth() + 1;
	var day = tempdate.getUTCDate();
	var hour = tempdate.getUTCHours() + 9;
	var min = tempdate.getUTCMinutes();

	// to handle the case when hour is bigger than 24
	if(hour > 24) {
		hour = hour - 24;
		day = day + 1;

		if(day > 32) {
			day = day - 31;
			month = month + 1;

			if(month > 12) {
				month = month - 12;
				year = year + 1;
			}
		}
	}

	// to print-out in two digit format
	if(month < 10) {
		month = "0" + month.toString();
	}

	if(day < 10) {
		day = "0" + day.toString();
	}

	if(hour < 10) {
		hour = "0" + hour.toString();
	}

	if(min < 10) {
		min = "0" + min.toString();
	}

	// preparation for actual print-out
	var time = year.toString() + month.toString() + day.toString() + "," + hour.toString() + ":" + min.toString();
	var api_key = req.query.api_key;
	var temperature = req.query.field1;
	temperature = Number(temperature);
	temperature = temperature.toFixed(2);

	//save into file
	fs.appendFile("data.txt", time + "," + temperature.toString() + '\r\n', function(err){
		if(err) throw err;
		res.end(seq++);	
	});
});

app.get('/get', function(req, res){
	fs.readFile('data.txt', "utf8", function(err, data){
		if(err) throw err;
		res.send(data);
		res.end();
	});
});

app.listen(8080, () => console.log('Example app listening on port 8080'));