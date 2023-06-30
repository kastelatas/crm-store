const Router = require("express");
const router = new Router();
const IngredientController = require("../controllers/IngredientController");

/**
 * @typedef Ingredient
 * @property {number} id.required - The ID of the ingredient
 * @property {string} name.required - The name of the ingredient
 * @property {number} quantity.required - The quantity of the ingredient
 * @property {string} measurementUnit.required - The measurement unit of the ingredient
 */

/**
 * Get the list of all ingredients
 * @route GET /api/ingredients
 * @group Ingredients - Operations related to ingredients
 * @returns {Array.<Ingredient>} 200 - The list of ingredients
 */
router.get("/", IngredientController.getAll);

/**
 * Get information about an ingredient by ID
 * @route GET /api/ingredients/{ingredientId}
 * @group Ingredients - Operations related to ingredients
 * @param {number} ingredientId.path.required - The ID of the ingredient
 * @returns {Ingredient} 200 - Information about the ingredient
 * @returns {object} 404 - Ingredient not found
 */
router.get("/:ingredientId", IngredientController.getOne);

/**
 * Create a new ingredient
 * @route POST /api/ingredients
 * @group Ingredients - Operations related to ingredients
 * @param {Ingredient.model} request.body.required - The data for the new ingredient
 * @returns {Ingredient} 201 - The created ingredient
 * @returns {object} 400 - Invalid ingredient data
 */
router.post("/", IngredientController.create);

/**
 * Update information about an ingredient by ID
 * @route PUT /api/ingredients/{ingredientId}
 * @group Ingredients - Operations related to ingredients
 * @param {number} ingredientId.path.required - The ID of the ingredient
 * @param {Ingredient} request.body.required - The updated ingredient data
 * @returns {Ingredient} 200 - Updated information about the ingredient
 * @returns {object} 400 - Invalid ingredient data
 * @returns {object} 404 - Ingredient not found
 */
router.put("/:ingredientId", IngredientController.update);

/**
 * Delete an ingredient by ID
 * @route DELETE /api/ingredients/{ingredientId}
 * @group Ingredients - Operations related to ingredients
 * @param {number} ingredientId.path.required - The ID of the ingredient
 * @returns {object} 204 - Ingredient successfully deleted
 * @returns {object} 404 - Ingredient not found
 */
router.delete("/:ingredientId", IngredientController.delete);

module.exports = router;
