import WS from './ws.js';

const logContainer = document.getElementById('log-container');
const closeButton = document.getElementById('close');
const openButton = document.getElementById('open');

const socket = new WS(logContainer);

openButton.addEventListener('click', () => {
  // socket.onopen();
  // socket.onmessage();
})

closeButton.addEventListener('click', () => {
  socket.close();
})

socket.onopen();
socket.onmessage();