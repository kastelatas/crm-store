const Menu = require("../models/Menu");

class MenuController {
  async getAll(req, res) {
    try {
      const menus = await Menu.findAll();
      res.json(menus);
    } catch (error) {
      console.error("Ошибка при получении пунктов меню:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
  async getOne(req, res) {
    try {
      const { menuId } = req.params;
      const menu = await Menu.findByPk(menuId);
      if (!menu) {
        return res.status(404).json({ error: "Menu item not found" });
      }
      res.json(menu);
    } catch (error) {
      console.error("Ошибка при получении информации о пункте меню:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
  async create(req, res) {
    try {
      const { name, price, description } = req.body;
      const menu = await Menu.create({ name, price, description });
      res.json(menu);
    } catch (error) {
      console.error("Ошибка при создании пункта меню:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
  async update(req, res) {
    try {
      const { menuId } = req.params;
      const { name, price, description } = req.body;
      const menu = await Menu.findByPk(menuId);
      if (!menu) {
        return res.status(404).json({ error: "Menu item not found" });
      }
      menu.name = name;
      menu.price = price;
      menu.description = description;
      await menu.save();
      res.json(menu);
    } catch (error) {
      console.error("Ошибка при обновлении информации о пункте меню:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
  async delete(req, res) {
    try {
      const { menuId } = req.params;
      const menu = await Menu.findByPk(menuId);
      if (!menu) {
        return res.status(404).json({ error: "Menu item not found" });
      }
      await menu.destroy();
      res.json({ message: "Menu item deleted successfully" });
    } catch (error) {
      console.error("Ошибка при удалении пункта меню:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
}

module.exports = new MenuController();
