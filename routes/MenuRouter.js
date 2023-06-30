const Router = require("express");
const router = new Router();
const MenuController = require("../controllers/MenuController");

/**
 * @typedef Menu
 * @property {number} id.required - The ID of the menu
 * @property {string} name.required - The name of the menu
 * @property {number} price.required - The price of the menu
 * @property {string} description.required - The description of the menu
 */

/**
 * Get the list of all menus
 * @route GET /api/menus
 * @group Menus - Operations related to menus
 * @returns {Array.<Menu>} 200 - The list of menus
 */
router.get("/", MenuController.getAll);

/**
 * Get information about a menu by ID
 * @route GET /api/menus/{menuId}
 * @group Menus - Operations related to menus
 * @param {number} menuId.path.required - The ID of the menu
 * @returns {Menu} 200 - Information about the menu
 * @returns {object} 404 - Menu not found
 */
router.get("/:menuId", MenuController.getOne);

/**
 * Create a new menu
 * @route POST /api/menus
 * @group Menus - Operations related to menus
 * @param {Menu.model} request.body.required - The data for the new menu
 * @returns {Menu} 201 - The created menu
 * @returns {object} 400 - Invalid menu data
 */
router.post("/", MenuController.create);

/**
 * Update information about a menu by ID
 * @route PUT /api/menus/{menuId}
 * @group Menus - Operations related to menus
 * @param {number} menuId.path.required - The ID of the menu
 * @param {Menu} request.body.required - The updated menu data
 * @returns {Menu} 200 - Updated information about the menu
 * @returns {object} 400 - Invalid menu data
 * @returns {object} 404 - Menu not found
 */
router.put("/:menuId", MenuController.update);

/**
 * Delete a menu by ID
 * @route DELETE /api/menus/{menuId}
 * @group Menus - Operations related to menus
 * @param {number} menuId.path.required - The ID of the menu
 * @returns {object} 204 - Menu successfully deleted
 * @returns {object} 404 - Menu not found
 */
router.delete("/:menuId", MenuController.delete);

module.exports = router;
