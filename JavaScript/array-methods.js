'use strict';

const products = [
  { name: 'Notebook', price: 4.5, quantity: 3 },
  { name: 'Pen', price: 1.25, quantity: 10 },
  { name: 'Backpack', price: 32, quantity: 0 },
];

function getProductNames(items) {
  return items.map((item) => item.name);
}

function getAvailableProducts(items) {
  return items.filter((item) => item.quantity > 0);
}

function getInventoryValue(items) {
  return items.reduce(
    (total, item) => total + item.price * item.quantity,
    0,
  );
}

if (require.main === module) {
  console.log('Product names:', getProductNames(products));
  console.log('Available products:', getAvailableProducts(products));
  console.log('Inventory value:', getInventoryValue(products).toFixed(2));
}

module.exports = {
  getAvailableProducts,
  getInventoryValue,
  getProductNames,
};
