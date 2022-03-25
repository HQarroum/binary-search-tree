import { BinarySearchTree } from '../../';

/** The tree must be layed-out acccording to the following structure. */
/**                        50                                          */
/**                       /  \                                         */
/**                     20     70                                      */
/**                    /  \   /  \                                     */
/**                  10   40 60  90                                    */
/**                               \                                    */
/**                                100                                 */
const data = [50, 70, 60, 20, 90, 10, 40, 100];

/**
 * Creates a new binary search tree.
 */
const tree = new BinarySearchTree<number>({
  comparator: (a, b) => a - b
});

// Add the data to the tree.
data.forEach((value) => tree.insert(value));

console.log(tree.toString());
