const Router = require("express");
const router = new Router();

const СlientRouter = require("./ClientRouter");
const MenuRouter = require("./MenuRouter");
const IngredientRouter = require("./IngredientRouter");
const OrderRouter = require("./OrderRouter");

router.use("/client", СlientRouter);
router.use("/menu", MenuRouter);
router.use("/ingredient", IngredientRouter);
router.use("/order", OrderRouter);

module.exports = router;
