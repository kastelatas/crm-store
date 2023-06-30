const Router = require("express");
const router = new Router();
const IngredientController = require("../controllers/IngredientController");

router.get("/", IngredientController.getAll);

module.exports = router;
