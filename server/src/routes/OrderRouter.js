const Router = require("express");
const router = new Router();
const OrderController = require("../controllers/OrderController");

/**
 * @typedef Order
 * @property {number} id.required - The ID of the order
 * @property {string} orderDate.required - The order date
 * @property {number} totalAmount.required - The total amount of the order
 * @property {string} status.required - The status of the order
 * @property {number} ClientId.required - The ID of the client associated with the order
 */

/**
 * Get the list of all orders
 * @route GET /api/orders
 * @group Orders - Operations related to orders
 * @returns {Array.<Order>} 200 - The list of orders
 */
router.get("/", OrderController.getAll);

/**
 * Get information about an order by ID
 * @route GET /api/orders/{orderId}
 * @group Orders - Operations related to orders
 * @param {number} orderId.path.required - The ID of the order
 * @returns {Order} 200 - Information about the order
 * @returns {object} 404 - Order not found
 */
router.get("/:orderId", OrderController.getOne);

/**
 * Create a new order
 * @route POST /api/orders
 * @group Orders - Operations related to orders
 * @param {Order.model} request.body.required - The data for the new order
 * @returns {Order} 201 - The created order
 * @returns {object} 400 - Invalid order data
 */
router.post("/", OrderController.create);

/**
 * Update information about an order by ID
 * @route PUT /api/orders/{orderId}
 * @group Orders - Operations related to orders
 * @param {number} orderId.path.required - The ID of the order
 * @param {Order} request.body.required - The updated order data
 * @returns {Order} 200 - Updated information about the order
 * @returns {object} 400 - Invalid order data
 * @returns {object} 404 - Order not found
 */
router.put("/:orderId", OrderController.update);

/**
 * Delete an order by ID
 * @route DELETE /api/orders/{orderId}
 * @group Orders - Operations related to orders
 * @param {number} orderId.path.required - The ID of the order
 * @returns {object} 204 - Order successfully deleted
 * @returns {object} 404 - Order not found
 */
router.delete("/:orderId", OrderController.delete);

module.exports = router;
