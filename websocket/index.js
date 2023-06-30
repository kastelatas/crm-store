const WebSocket = require("ws");

const configureWebSocket = (server) => {
  const wss = new WebSocket.Server({ server });

  wss.on("connection", (ws) => {
    console.log("New client connected to WebSocket");

    ws.on("message", (message) => {
      console.log("Message received:", message);

      const parsedMessage = JSON.parse(message);
      const messageType = parsedMessage.type;

      switch (messageType) {
        case value:
          break;

        default:
          break;
      }

      ws.send(`Message reply "${message}"`);
    });

    ws.on("close", () => {
      console.log("Client disconnected from WebSocket");
    });
  });
};

module.exports = configureWebSocket;
