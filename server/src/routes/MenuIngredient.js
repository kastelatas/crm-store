const Router = require("express");
const router = new Router();
const MenuIngredientController = require("../controllers/MenuIngredientController");

/**
 * @typedef MenuIngredient
 * @property {number} id.required - The ID of the menu ingredient
 * @property {number} MenuId.required - The ID of the menu
 * @property {number} IngredientId.required - The ID of the ingredient
 */

/**
 * Get the list of all menu ingredients
 * @route GET /api/menu-ingredients
 * @group Menu Ingredients - Operations related to menu ingredients
 * @returns {Array.<MenuIngredient>} 200 - The list of menu ingredients
 */
router.get("/", MenuIngredientController.getAll);

/**
 * Create a new menu ingredient
 * @route POST /api/menu-ingredients
 * @group Menu Ingredients - Operations related to menu ingredients
 * @param {MenuIngredient.model} request.body.required - The data for the new menu ingredient
 * @returns {MenuIngredient} 201 - The created menu ingredient
 * @returns {object} 400 - Invalid menu ingredient data
 */
router.post("/", MenuIngredientController.create);

/**
 * Delete a menu ingredient by ID
 * @route DELETE /api/menu-ingredients/{menuIngredientId}
 * @group Menu Ingredients - Operations related to menu ingredients
 * @param {number} menuIngredientId.path.required - The ID of the menu ingredient
 * @returns {object} 204 - Menu ingredient successfully deleted
 * @returns {object} 404 - Menu ingredient not found
 */
router.delete("/:menuIngredientId", MenuIngredientController.delete);

module.exports = router;
