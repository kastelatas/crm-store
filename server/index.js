require("dotenv").config();
const express = require("express");
const app = express();
const server = require("http").createServer(app);
const cors = require("cors");
const morgan = require("morgan");
const rfs = require("rotating-file-stream");
const fs = require("fs");
const path = require("path");
const configureSwagger = require("./swagger");
const sequelize = require("./db");
const router = require("./src/routes");
const configureWebSocket = require("./src/websocket");

const PORT = process.env.PORT || 8000;

const logDirectory = path.join(__dirname, "logs");

const accessLogStream = rfs.createStream("access.log", {
  interval: "1d",
  path: logDirectory,
});

fs.mkdirSync(logDirectory, { recursive: true });

app.use(morgan("common", { stream: accessLogStream }));
app.use(cors());
app.use(express.json());
app.use(express.static("public"));
app.use("/api", router);

configureWebSocket(server);
configureSwagger(app);

app.use((req, res, next) => {
  if (req.originalUrl === "/favicon.ico") {
    res.status(204).json({ nope: true });
  } else {
    next();
  }
});

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
