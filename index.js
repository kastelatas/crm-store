const express = require("express");
const app = express();
const server = require("http").createServer(app);
const configureWebSocket = require("./websocket");

const PORT = process.env.PORT || 5000;

// Middleware и настройки Express
app.use(express.json());
app.use(express.static("public"));

configureWebSocket(server);

const start = async () => {
  try {
    // await sequelize.authenticate();
    // await sequelize.sync({
    //   force: false,
    // });
    server.listen(PORT, () => {
      console.log(`Сервер запущен на порту ${PORT}`);
    });
  } catch (e) {
    console.log(e);
  }
};

start();
