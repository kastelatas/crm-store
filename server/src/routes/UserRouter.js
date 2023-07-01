const Router = require("express");
const router = new Router();
const UserController = require("../controllers/UserController");
const authMiddleware = require("../middleware/authMiddleware");

/**
 * @typedef User
 * @property {number} id.required - The ID of the user
 * @property {string} email.required - The email of the user
 * @property {string} password.required - The password of the user
 * @property {string} role - The role of the user (default: "USER")
 */

/**
 * Register a new user
 * @route POST /api/users/registration
 * @group Users - Operations related to users
 * @param {User.model} request.body.required - The data for user registration
 * @returns {object} 200 - User registration successful
 * @returns {object} 400 - Invalid user data
 * @returns {object} 409 - User with the provided email already exists
 */
router.post("/registration", UserController.registration);

/**
 * Authenticate and log in a user
 * @route POST /api/users/login
 * @group Users - Operations related to users
 * @param {User.model} request.body.required - The data for user login
 * @returns {object} 200 - User login successful
 * @returns {object} 400 - Invalid user data
 * @returns {object} 401 - Incorrect email or password
 */
router.post("/login", UserController.login);

/**
 * Check user authentication
 * @route GET /api/users/auth
 * @group Users - Operations related to users
 * @returns {object} 200 - User is authenticated
 * @returns {object} 401 - User is not authenticated
 */
router.get("/auth", authMiddleware, UserController.check);

module.exports = router;
