const Order = require("../models/Order");
const Client = require("../models/Client");
const Menu = require("../models/Menu");

class OrderController {
  async getAll(req, res) {
    try {
      const orders = await Order.findAll({
        include: [
          {
            model: Client,
          },
          {
            model: Menu,
            through: "OrderMenu",
          },
        ],
      });
      res.json(orders);
    } catch (error) {
      console.error("Ошибка при получении заказов:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
  async create(req, res) {
    try {
      const { clientId, orderDate, totalAmount, status, menuItems } = req.body;

      // Проверяем существование клиента
      const client = await Client.findByPk(clientId);
      if (!client) {
        return res.status(404).json({ error: "Client not found" });
      }

      // Создаем заказ
      const order = await Order.create({ orderDate, totalAmount, status });

      // Связываем заказ с клиентом
      await order.setClient(client);

      // Связываем заказ с пунктами меню
      await order.setMenus(menuItems);

      res.json(order);
    } catch (error) {
      console.error("Ошибка при создании заказа:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
  async getOne(req, res) {
    try {
      const { orderId } = req.params;
      const order = await Order.findByPk(orderId, {
        include: [
          {
            model: Client,
          },
          {
            model: Menu,
            through: "OrderMenu",
          },
        ],
      });
      if (!order) {
        return res.status(404).json({ error: "Order not found" });
      }
      res.json(order);
    } catch (error) {
      console.error("Ошибка при получении информации о заказе:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
  async update(req, res) {
    try {
      const { orderId } = req.params;
      const { clientId, orderDate, totalAmount, status, menuItems } = req.body;

      // Проверяем существование заказа
      const order = await Order.findByPk(orderId);
      if (!order) {
        return res.status(404).json({ error: "Order not found" });
      }

      // Проверяем существование клиента
      const client = await Client.findByPk(clientId);
      if (!client) {
        return res.status(404).json({ error: "Client not found" });
      }

      // Обновляем информацию о заказе
      order.orderDate = orderDate;
      order.totalAmount = totalAmount;
      order.status = status;
      await order.save();

      // Связываем заказ с клиентом
      await order.setClient(client);

      // Связываем заказ с пунктами меню
      await order.setMenus(menuItems);

      res.json(order);
    } catch (error) {
      console.error("Ошибка при обновлении информации о заказе:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
  async delete(req, res) {
    try {
      const { orderId } = req.params;
      const order = await Order.findByPk(orderId);
      if (!order) {
        return res.status(404).json({ error: "Order not found" });
      }
      await order.destroy();
      res.json({ message: "Order deleted successfully" });
    } catch (error) {
      console.error("Ошибка при удалении заказа:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
}

module.exports = new OrderController();
