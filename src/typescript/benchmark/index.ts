import { strict as assert } from 'assert';
import { BinarySearchTree } from '../';

/**
 * The number of elements to insert.
 */
const iterations = 100000;

/**
 * Generates a random number between `min` and `max`.
 * @param min the minimum value.
 * @param max the maximum value.
 */
function* random(min: number, max: number): IterableIterator<number> {
  while (true) {
    yield Math.floor(Math.random() * (max - min + 1)) + min;
  }
}

/**
 * Creating an array of random numbers.
 */
const array = Array<number>(iterations)
  .fill(0)
  .map(() => random(0, iterations).next().value);

console.time('benchmark');

// Creating the tree.
const tree = new BinarySearchTree<number>({
  comparator: (a, b) => a - b
});

// Insert and searching for each element.
for (const value of array) {
  tree.insert(value);
  assert(tree.find(value) !== null);
}

console.timeEnd('benchmark');
