const { DataTypes } = require("sequelize");
const sequelize = require("../db");
const Client = require("./Client");
const Menu = require("./menu");

const Order = sequelize.define("Order", {
  id: {
    type: DataTypes.INTEGER,
    primaryKey: true,
    autoIncrement: true,
  },
  orderDate: {
    type: DataTypes.DATE,
    allowNull: false,
  },
  totalAmount: {
    type: DataTypes.INTEGER,
    allowNull: false,
  },
  status: {
    type: DataTypes.STRING,
    allowNull: false,
  },
});

Order.belongsTo(Client);
Client.hasMany(Order);

Order.belongsToMany(Menu, { through: "OrderMenu" });
Menu.belongsToMany(Order, { through: "OrderMenu" });

module.exports = Order;
