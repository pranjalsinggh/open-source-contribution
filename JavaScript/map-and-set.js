const assert = require("node:assert/strict");

const attendeeIds = [12, 7, 12, 4, 7, 9];
const uniqueAttendeeIds = [...new Set(attendeeIds)];

const votes = new Map();
for (const candidate of ["Mina", "Leo", "Mina", "Ari", "Leo", "Mina"]) {
  votes.set(candidate, (votes.get(candidate) ?? 0) + 1);
}

assert.deepEqual(uniqueAttendeeIds, [12, 7, 4, 9]);
assert.equal(votes.get("Mina"), 3);
assert.equal(votes.get("Leo"), 2);
assert.equal(votes.has("Ari"), true);
assert.equal(votes.has("Sam"), false);

console.log(`Unique attendee IDs: ${uniqueAttendeeIds.join(", ")}`);
console.log(`Mina's votes: ${votes.get("Mina")}`);
console.log(`Candidates: ${[...votes.keys()].join(", ")}`);
