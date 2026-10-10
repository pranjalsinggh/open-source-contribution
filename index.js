const cart = [
  { name: "Notebook", price: 3.5, quantity: 2 },
  { name: "Pen", price: 1.25, quantity: 4 },
  { name: "Backpack", price: 24.99, quantity: 1 },
];

const currency = new Intl.NumberFormat("en-US", {
  style: "currency",
  currency: "USD",
});

const lineItems = cart.map(
  ({ name, price, quantity }) =>
    `${quantity} x ${name}: ${currency.format(price * quantity)}`,
);
const total = cart.reduce(
  (sum, { price, quantity }) => sum + price * quantity,
  0,
);

console.log("Shopping cart");
console.log(lineItems.join("\n"));
console.log(`Total: ${currency.format(total)}`);
