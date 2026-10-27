const users = [
  { id: 1, name: "Ada" },
  { id: 2, name: "Grace" },
];

const orders = [
  { userId: 1, item: "Notebook" },
  { userId: 1, item: "Pencil" },
  { userId: 2, item: "Calculator" },
];

function findUserById(id) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(users.find((user) => user.id === id));
    }, 100);
  });
}

function findOrdersByUserId(userId) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(orders.filter((order) => order.userId === userId));
    }, 100);
  });
}

async function showUserOrders(userId) {
  try {
    console.log(`Looking up user ${userId}...`);

    const user = await findUserById(userId);
    if (!user) {
      throw new Error(`No user found with ID ${userId}.`);
    }

    const userOrders = await findOrdersByUserId(user.id);
    console.log(`${user.name}'s orders:`);

    if (userOrders.length === 0) {
      console.log("- No orders yet.");
      return;
    }

    userOrders.forEach((order) => console.log(`- ${order.item}`));
  } catch (error) {
    console.error(`Could not load orders: ${error.message}`);
  }
}

async function main() {
  console.log("Async/await example");
  await showUserOrders(1);
  await showUserOrders(99);
}

main();
