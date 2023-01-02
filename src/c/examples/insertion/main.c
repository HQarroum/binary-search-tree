#include <stdio.h>
#include "binary_search_tree.h"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

// Sample data.
static const int data[] = { 50, 70, 60, 20, 90, 10, 40, 100 };

/**
 * Main function.
 */
int main(void) {
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    bst_insert(tree, &data[i]);
  }

  // Displaying the size of the tree.
  printf("Tree elements : %zu\n", bst_size(tree));

  // Destroying the tree.
  bst_destroy(tree);

  return (0);
}