const assert = require("node:assert/strict");

function createCounter(start = 0) {
  let count = start;

  return {
    increment() {
      count += 1;
      return count;
    },
    decrement() {
      count -= 1;
      return count;
    },
    getValue() {
      return count;
    },
  };
}

const firstCounter = createCounter(2);
const secondCounter = createCounter();

assert.equal(firstCounter.increment(), 3);
assert.equal(firstCounter.decrement(), 2);
assert.equal(firstCounter.getValue(), 2);
assert.equal(secondCounter.getValue(), 0);

console.log(`First counter: ${firstCounter.getValue()}`);
console.log(`Second counter: ${secondCounter.getValue()}`);
