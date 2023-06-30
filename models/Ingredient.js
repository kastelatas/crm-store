const { DataTypes } = require("sequelize");
const sequelize = require("../db");

const Ingredient = sequelize.define("Ingredient", {
  id: {
    type: DataTypes.INTEGER,
    primaryKey: true,
    autoIncrement: true,
  },
  name: {
    type: DataTypes.STRING,
    allowNull: false,
  },
  measurementUnit: {
    type: DataTypes.STRING,
    allowNull: false,
  },
});

module.exports = Ingredient;
