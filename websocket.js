const WebSocket = require("ws");

const configureWebSocket = (server) => {
  const wss = new WebSocket.Server({ server });

  wss.on("connection", (ws) => {
    console.log("Новый клиент подключился к WebSocket");

    ws.on("message", (message) => {
      console.log("Получено сообщение:", message);

      const parsedMessage = JSON.parse(message);
      const messageType = parsedMessage.type;

      switch (messageType) {
        case value:
          break;

        default:
          break;
      }
      // console.log("message", typeof message);
      // console.log("parsedMessage", parsedMessage);
      // console.log("messageType", messageType);

      ws.send(`Ответ на сообщение "${message}"`);
    });

    ws.on("close", () => {
      console.log("Клиент отключился от WebSocket");
    });
  });
};

module.exports = configureWebSocket;
