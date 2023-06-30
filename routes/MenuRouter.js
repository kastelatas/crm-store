const Router = require("express");
const router = new Router();
const MenuController = require("../controllers/MenuController");

router.get("/", MenuController.getAll);

module.exports = router;
