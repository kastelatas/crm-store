const MenuIngredient = require("../models/MenuIngredient");
const Menu = require("../models/Menu");
const Ingredient = require("../models/Ingredient");

class MenuIngredientController {
  async getAll(req, res) {
    try {
      const menuIngredients = await MenuIngredient.findAll({
        include: [
          {
            model: Menu,
          },
          {
            model: Ingredient,
          },
        ],
      });
      res.json(menuIngredients);
    } catch (error) {
      console.error(
        'Ошибка при получении связей "Ингредиенты в блюде":',
        error
      );
      res.status(500).json({ error: "Internal server error" });
    }
  }
  async create(req, res) {
    try {
      const { menuId, ingredientId } = req.body;

      // Проверяем существование блюда
      const menu = await Menu.findByPk(menuId);
      if (!menu) {
        return res.status(404).json({ error: "Menu not found" });
      }

      // Проверяем существование ингредиента
      const ingredient = await Ingredient.findByPk(ingredientId);
      if (!ingredient) {
        return res.status(404).json({ error: "Ingredient not found" });
      }

      // Создаем связь "Ингредиент в блюде"
      const menuIngredient = await MenuIngredient.create();

      // Связываем связь "Ингредиент в блюде" с блюдом и ингредиентом
      await menuIngredient.setMenu(menu);
      await menuIngredient.setIngredient(ingredient);

      res.json(menuIngredient);
    } catch (error) {
      console.error('Ошибка при создании связи "Ингредиент в блюде":', error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
  async delete(req, res) {
    try {
      const { menuIngredientId } = req.params;
      const menuIngredient = await MenuIngredient.findByPk(menuIngredientId);
      if (!menuIngredient) {
        return res.status(404).json({ error: "MenuIngredient not found" });
      }
      await menuIngredient.destroy();
      res.json({ message: "MenuIngredient deleted successfully" });
    } catch (error) {
      console.error('Ошибка при удалении связи "Ингредиент в блюде":', error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
}

module.exports = new MenuIngredientController();
