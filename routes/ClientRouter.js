const Router = require("express");
const router = new Router();
const ClientController = require("../controllers/ClientController");

/**
 * @typedef Client
 * @property {number} id.required - The ID of the client
 * @property {string} name.required - The name of the client
 * @property {string} phone.required - The phone number of the client
 */

/**
 * Get the list of all clients
 * @route GET /api/clients
 * @group Clients - Operations related to clients
 * @returns {Array.<Client>} 200 - The list of clients
 */
router.get("/", ClientController.getAll);

/**
 * Get information about a client by ID
 * @route GET /api/clients/{clientId}
 * @group Clients - Operations related to clients
 * @param {number} clientId.path.required - The ID of the client
 * @returns {Client} 200 - Information about the client
 * @returns {object} 404 - Client not found
 */
router.get("/:clientId", ClientController.getOne);

/**
 * Create a new client
 * @route POST /api/clients
 * @group Clients - Operations related to clients
 * @param {Client.model} request.body.required - The data for the new client
 * @returns {Client} 201 - The created client
 * @returns {object} 400 - Invalid client data
 */
router.post("/", ClientController.create);

/**
 * Update information about a client by ID
 * @route PUT /api/clients/{clientId}
 * @group Clients - Operations related to clients
 * @param {number} clientId.path.required - The ID of the client
 * @param {Client} request.body.required - The updated client data
 * @returns {Client} 200 - Updated information about the client
 * @returns {object} 400 - Invalid client data
 * @returns {object} 404 - Client not found
 */
router.put("/:clientId", ClientController.update);

/**
 * Delete a client by ID
 * @route DELETE /api/clients/{clientId}
 * @group Clients - Operations related to clients
 * @param {number} clientId.path.required - The ID of the client
 * @returns {object} 204 - Client successfully deleted
 * @returns {object} 404 - Client not found
 */
router.delete("/:clientId", ClientController.delete);

module.exports = router;
