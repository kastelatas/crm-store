const Client = require("./src/models/Client");
const Order = require("./src/models/Order");
const Ingredient = require("./src/models/Ingredient");
const Menu = require("./src/models/Menu");
const MenuIngredient = require("./src/models/MenuIngredient");

async function generateFakeClients(numClients, faker) {
  try {
    for (let i = 0; i < numClients; i++) {
      await Client.create({
        name: faker.name.findName(),
        phone: faker.phone.phoneNumber(),
      });
    }
    console.log(`${numClients} fake clients created successfully.`);
  } catch (err) {
    console.error("Error generating fake clients:", err);
  }
}

async function generateFakeIngredients(numIngredients, faker) {
  try {
    for (let i = 0; i < numIngredients; i++) {
      await Ingredient.create({
        name: faker.commerce.productName(),
        quantity: faker.random.number({ min: 1, max: 100 }),
        measurementUnit: faker.random.arrayElement([
          "kg",
          "g",
          "l",
          "ml",
          "pcs",
        ]),
      });
    }
    console.log(`${numIngredients} fake ingredients created successfully.`);
  } catch (err) {
    console.error("Error generating fake ingredients:", err);
  }
}

async function generateFakeMenus(numMenus, faker) {
  try {
    for (let i = 0; i < numMenus; i++) {
      await Menu.create({
        name: faker.commerce.productName(),
        price: faker.random.number({ min: 10, max: 1000 }),
        description: faker.lorem.sentence(),
      });
    }
    console.log(`${numMenus} fake menus created successfully.`);
  } catch (err) {
    console.error("Error generating fake menus:", err);
  }
}

async function generateFakeMenuIngredients(numMenuIngredients, faker) {
  try {
    const menus = await Menu.findAll();
    const ingredients = await Ingredient.findAll();

    for (let i = 0; i < numMenuIngredients; i++) {
      const randomMenu = faker.random.arrayElement(menus);
      const randomIngredient = faker.random.arrayElement(ingredients);

      await MenuIngredient.create({
        MenuId: randomMenu.id,
        IngredientId: randomIngredient.id,
      });
    }

    console.log(
      `${numMenuIngredients} fake menu ingredients created successfully.`
    );
  } catch (err) {
    console.error("Error generating fake menu ingredients:", err);
  }
}

async function generateFakeOrders(numOrders, faker) {
  try {
    const clients = await Client.findAll();
    const menus = await Menu.findAll();

    for (let i = 0; i < numOrders; i++) {
      const randomClient = faker.random.arrayElement(clients);
      const orderDate = faker.date.past();
      const totalAmount = faker.random.number({ min: 10, max: 1000 });
      const status = faker.random.arrayElement([
        "pending",
        "completed",
        "cancelled",
      ]);

      const order = await Order.create({
        orderDate,
        totalAmount,
        status,
        ClientId: randomClient.id,
      });

      const numMenuItems = faker.random.number({ min: 1, max: 5 });
      for (let j = 0; j < numMenuItems; j++) {
        const randomMenu = faker.random.arrayElement(menus);
        await order.addMenu(randomMenu);
      }
    }

    console.log(`${numOrders} fake orders created successfully.`);
  } catch (err) {
    console.error("Error generating fake orders:", err);
  }
}

module.exports = {
  generateFakeClients,
  generateFakeIngredients,
  generateFakeMenus,
  generateFakeMenuIngredients,
  generateFakeOrders,
};
