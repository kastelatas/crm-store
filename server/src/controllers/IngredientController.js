const Ingredient = require("../models/Ingredient");

class IngredientController {
  async getAll(req, res) {
    try {
      const ingredients = await Ingredient.findAll();
      res.json(ingredients);
    } catch (error) {
      console.error("Ошибка при получении ингредиентов:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
  async getOne(req, res) {
    try {
      const { ingredientId } = req.params;
      const ingredient = await Ingredient.findByPk(ingredientId);
      if (!ingredient) {
        return res.status(404).json({ error: "Ingredient not found" });
      }
      res.json(ingredient);
    } catch (error) {
      console.error("Ошибка при получении информации об ингредиенте:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
  async create(req, res) {
    try {
      const { name, quantity, measurementUnit } = req.body;
      const ingredient = await Ingredient.create({
        name,
        quantity,
        measurementUnit,
      });
      res.json(ingredient);
    } catch (error) {
      console.error("Ошибка при создании ингредиента:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
  async update(req, res) {
    try {
      const { ingredientId } = req.params;
      const { name, quantity, measurementUnit } = req.body;
      const ingredient = await Ingredient.findByPk(ingredientId);
      if (!ingredient) {
        return res.status(404).json({ error: "Ingredient not found" });
      }
      ingredient.name = name;
      ingredient.quantity = quantity;
      ingredient.measurementUnit = measurementUnit;
      await ingredient.save();
      res.json(ingredient);
    } catch (error) {
      console.error("Ошибка при обновлении информации об ингредиенте:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
  async delete(req, res) {
    try {
      const { ingredientId } = req.params;
      const ingredient = await Ingredient.findByPk(ingredientId);
      if (!ingredient) {
        return res.status(404).json({ error: "Ingredient not found" });
      }
      await ingredient.destroy();
      res.json({ message: "Ingredient deleted successfully" });
    } catch (error) {
      console.error("Ошибка при удалении ингредиента:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
}

module.exports = new IngredientController();
