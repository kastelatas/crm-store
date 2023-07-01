const handleOrderToKitchenEvent = (ws, data) => {
  console.log("Custom event received:", data.message);

  ws.send(`Response to a custom event "${data.message}"`);
};

module.exports = handleOrderToKitchenEvent;
