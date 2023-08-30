import WS from './ws.js';

const logContainer = document.getElementById('log-container');
const closeButton = document.getElementById('close');
const openButton = document.getElementById('open');

let socket = null;

openButton.addEventListener('click', () => {
  socket = new WS('ws://localhost:8080', logContainer)
  socket.onopen();
  socket.onmessage();
})

closeButton.addEventListener('click', () => {
  socket.close();
})

// socket.onopen();
// socket.onmessage();