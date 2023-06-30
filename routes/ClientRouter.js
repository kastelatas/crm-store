const Router = require("express");
const router = new Router();
const ClientController = require("../controllers/ClientController");

router.get("/", ClientController.getAll);

module.exports = router;
