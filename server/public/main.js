const socket = io();

socket.on('arr', (data) => {
	let arr = data.split(',');
	let tempControl = parseInt(arr[0]);
	let tempSet = parseInt(arr[1]);
	let ovenState = parseInt(arr[2]);
	let fanState = parseInt(arr[3]);
	let coldState = parseInt(arr[4]);
	let normalState = parseInt(arr[5]);
	let heatState = parseInt(arr[6]);

	let temp1 = document.getElementById('control_temperature');
	temp1.innerHTML = `${tempControl} 	°C`;

	let temp2 = document.getElementById('set_temperature');
	temp2.innerHTML = `${tempSet} 	°C`;

	// OVEN STATE

	let state1 = document.querySelector('.oven-span');
	if (ovenState === 1) {
		state1.innerText = 'ON';
	} else {
		state1.innerText = 'OFF';
	}
	if (state1.innerText == 'ON') {
		document.querySelector('.oven-box').classList.add('pressed');
		document.querySelector('.oven-icon').classList.add('filtered');
	} else {
		document.querySelector('.oven-box').classList.remove('pressed');
		document.querySelector('.oven-icon').classList.remove('filtered');
	}

	// FAN STATE

	let state2 = document.querySelector('.fan-span');
	if (fanState === 1) {
		state2.innerText = 'ON';
	} else {
		state2.innerText = 'OFF';
	}
	if (state2.innerText == 'ON') {
		document.querySelector('.fan-box').classList.add('pressed');
		document.querySelector('.fan-icon').classList.add('filtered');
	} else {
		document.querySelector('.fan-box').classList.remove('pressed');
		document.querySelector('.fan-icon').classList.remove('filtered');
	}

	// COLD TEMP STATE
	let state3 = document.querySelector('.cold-span');
	if (coldState === 1) {
		state3.innerText = 'ON';
	} else {
		state3.innerText = 'OFF';
	}
	if (state3.innerText == 'ON') {
		document.querySelector('.cold-box').classList.add('pressed');
		document.querySelector('.cold-icon').classList.add('filtered');
	} else {
		document.querySelector('.cold-box').classList.remove('pressed');
		document.querySelector('.cold-icon').classList.remove('filtered');
	}

	// NORMAL TEMP STATE
	let state4 = document.querySelector('.normal-span');
	if (normalState === 1) {
		state4.innerText = 'ON';
	} else {
		state4.innerText = 'OFF';
	}
	if (state4.innerText == 'ON') {
		document.querySelector('.normal-box').classList.add('pressed');
		document.querySelector('.normal-icon').classList.add('filtered');
	} else {
		document.querySelector('.normal-box').classList.remove('pressed');
		document.querySelector('.normal-icon').classList.remove('filtered');
	}

	// HEAT TEMP STATE
	let state5 = document.querySelector('.heat-span');
	if (heatState === 1) {
		state5.innerText = 'ON';
	} else {
		state5.innerText = 'OFF';
	}
	if (state5.innerText == 'ON') {
		document.querySelector('.heat-box').classList.add('pressed');
		document.querySelector('.heat-icon').classList.add('filtered');
	} else {
		document.querySelector('.heat-box').classList.remove('pressed');
		document.querySelector('.heat-icon').classList.remove('filtered');
	}
});
