#include <time.h>
#include <stdio.h>
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

  // The array which hold the random values.
  int array[iterations];

  // Filling the array with random values.
  for (size_t i = 0; i < iterations; ++i) {
    array[i] = rand();
  }

  // Initializing the clock.
  clock_t begin = clock();

  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Insert and searching for each element.
  for (size_t i = 0; i < iterations; ++i) {
    bst_insert(tree, &array[i]);
    assert(bst_find(tree, &array[i]) != NULL);
  }

  double time_spent = (double)(clock() - begin) / (CLOCKS_PER_SEC / 1000);
  printf("Time spent: %fms\n", time_spent);
  
  return (0);
}
