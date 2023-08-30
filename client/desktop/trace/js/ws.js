class WS {
  constructor(traceContainer) {
    this.socket = new WebSocket('ws://localhost:8080');
    this.traceContainer = traceContainer;
  }
  send(data) {
    this.socket.send(data);
  }
  close() {
    console.log('ws closed');
    this.socket.close();
  }

  onopen() {
    console.log('ws connected');
  }

  onmessage() {
    this.socket.onmessage = (evt) => {
      const event = JSON.parse(evt.data);
      this.traceContainer.innerHTML += `<tr> <td max-width="100px">${event.time}</td> <td>${event.type}</td>  <td>${event.data}</td>`;
    }
  }

  onerror(evt) {
    console.error('WebSocket error observed:', evt);
  }
}


export default WS;