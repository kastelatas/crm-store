class WS {
  constructor(url, traceContainer) {
    this.socket = new WebSocket(url);
    this.traceContainer = traceContainer;
  }

  close() {
    console.log('ws closed');
    this.socket.close();
  }

  onopen() {
    this.socket.onopen = () => {
      console.log('ws connected');
    }
  }

  onmessage() {
    this.socket.onmessage = (evt) => {
      const event = JSON.parse(evt.data);
      this.traceContainer.innerHTML += `<tr> <td max-width="100px">${event.time}</td> <td>${event.type}</td>  <td>${event.data}</td>`;
    }
  }

  onerror() {
    this.socket.onerror = (evt) => {
      console.error('WebSocket error observed:', evt);
    }
  }
}

export default WS;