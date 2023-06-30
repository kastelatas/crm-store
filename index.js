require("dotenv").config();
const express = require("express");
const app = express();
const cors = require("cors");
const server = require("http").createServer(app);
const sequelize = require("./db");
const router = require("./routes/index");
const configureWebSocket = require("./websocket");

const PORT = process.env.PORT || 8000;

app.use(cors());
app.use(express.json());
app.use(express.static("public"));
app.use("/api", router);

configureWebSocket(server);

const start = async () => {
  try {
    await sequelize.authenticate();
    await sequelize.sync({
      force: false,
    });
    server.listen(PORT, () => {
      console.log(`Server started on port ${PORT}`);
    });
  } catch (e) {
    console.log(e);
  }
};

start();
