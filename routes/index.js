const Router = require("express");
const router = new Router();

const UserRouter = require("./UserRouter");
const ClientRouter = require("./ClientRouter");
const MenuRouter = require("./MenuRouter");
const IngredientRouter = require("./IngredientRouter");
const OrderRouter = require("./OrderRouter");

router.use("/user", UserRouter);
router.use("/client", ClientRouter);
router.use("/menu", MenuRouter);
router.use("/ingredient", IngredientRouter);
router.use("/order", OrderRouter);

module.exports = router;
