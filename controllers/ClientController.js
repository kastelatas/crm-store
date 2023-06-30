const Client = require("../models/Client");

class ClientController {
  async getAll(req, res) {
    try {
      const clients = await Client.findAll();
      res.json(clients);
    } catch (error) {
      console.error("Ошибка при получении клиентов:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }

  async getOne(req, res) {
    try {
      const { clientId } = req.params;
      const client = await Client.findByPk(clientId);
      if (!client) {
        return res.status(404).json({ error: "Client not found" });
      }
      res.json(client);
    } catch (error) {
      console.error("Ошибка при получении информации о клиенте:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }

  async create(req, res) {
    try {
      const { name, email, phone } = req.body;
      const client = await Client.create({ name, email, phone });
      res.json(client);
    } catch (error) {
      console.error("Ошибка при создании клиента:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
  async update(req, res) {
    try {
      const { clientId } = req.params;
      const { name, email, phone } = req.body;
      const client = await Client.findByPk(clientId);
      if (!client) {
        return res.status(404).json({ error: "Client not found" });
      }
      client.name = name;
      client.email = email;
      client.phone = phone;
      await client.save();
      res.json(client);
    } catch (error) {
      console.error("Ошибка при обновлении информации о клиенте:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
  async delete(req, res) {
    try {
      const { clientId } = req.params;
      const client = await Client.findByPk(clientId);
      if (!client) {
        return res.status(404).json({ error: "Client not found" });
      }
      await client.destroy();
      res.json({ message: "Client deleted successfully" });
    } catch (error) {
      console.error("Ошибка при удалении клиента:", error);
      res.status(500).json({ error: "Internal server error" });
    }
  }
}

module.exports = new ClientController();
