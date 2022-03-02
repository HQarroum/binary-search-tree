#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <binary_search_tree.h>

/**
 * The number of elements to insert into the tree.
 */
static const size_t iterations = 100000;

int main(void) {
  // Initializing the seed.
  srand(time(NULL));

  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // The array which hold the random values.
  int array[iterations] = {0};

  // Inserting the data.
  for (size_t i = 0; i < iterations; ++i) {
    array[i] = rand();
    bst_insert(tree, &array[i]);
    assert(bst_find(tree, &array[i]) != NULL);
  }
  
  return (0);
}
