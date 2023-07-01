const WebSocket = require("ws");
const handleOrderToKitchenEvent = require("./events/orderToKitchenEventHandler");

const configureWebSocket = (server) => {
  const wss = new WebSocket.Server({ server });

  wss.on("connection", (ws) => {
    console.log("New client connected to WebSocket");

    ws.on("message", (message) => {
      console.log("Message received:", message);

      const parsedMessage = JSON.parse(message);
      const messageType = parsedMessage.type;
      const eventData = parsedMessage.data;

      switch (messageType) {
        case "orderToKitchen":
          handleOrderToKitchenEvent(ws, eventData);
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
