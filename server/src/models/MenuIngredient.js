const { DataTypes } = require("sequelize");
const sequelize = require("../db");
const Menu = require("./Menu");
const Ingredient = require("./Ingredient");

const MenuIngredient = sequelize.define("MenuIngredient", {
  id: {
    type: DataTypes.INTEGER,
    primaryKey: true,
    autoIncrement: true,
  },
});

Menu.belongsToMany(Ingredient, { through: MenuIngredient });
Ingredient.belongsToMany(Menu, { through: MenuIngredient });

module.exports = MenuIngredient;
