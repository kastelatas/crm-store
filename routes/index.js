const Router = require("express");
const router = new Router();

const UserRouter = require("./UserRouter");
const ClientRouter = require("./ClientRouter");
const MenuRouter = require("./MenuRouter");
const IngredientRouter = require("./IngredientRouter");
const OrderRouter = require("./OrderRouter");
const MenuIngredient = require("./MenuIngredient");

router.use("/user", UserRouter);
router.use("/clients", ClientRouter);
router.use("/menu", MenuRouter);
router.use("/ingredient", IngredientRouter);
router.use("/orders", OrderRouter);
router.use("/menuIngredient", MenuIngredient);

module.exports = router;
