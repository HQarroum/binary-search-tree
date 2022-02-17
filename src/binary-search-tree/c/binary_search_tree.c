#include "binary_search_tree.h"

/**
 * @brief Creates a new dynamically allocated binary-search tree instance.
 * @param options a set of options to pass to the implementation.
 * @return a pointer to the newly created binary-search tree
 */
bst_tree_t* bst_create(bst_options_t options) {
  /* The comparator function is required to
     create the binary-search tree. */
  if (options.comparator == NULL) {
    return (NULL);
  }

  /* Allocating memory for the binary-search tree. */
  bst_tree_t* tree = malloc(sizeof(bst_tree_t));
  
  tree->root    = NULL;
  tree->size    = 0;
  tree->options = options;
  return (tree);
}

/**
 * @brief Creates a new dynamically allocated binary-search node instance.
 * @param data a pointer to the data to initialize the node with.
 * @return a pointer to the newly created binary-search node
 */
bst_node_t* bst_create_node(const void* data) {
  /* Non-null data is required to create a node. */
  if (data == NULL)
    return (NULL);

  /* Allocating memory for the node. */
  bst_node_t* node = malloc(sizeof(bst_node_t));

  node->data   = data;
  node->left   = NULL;
  node->right  = NULL;
  node->parent = NULL;
  node->tree   = NULL;
  return (node);
}

/**
 * @param tree The tree to return the size of.
 * @return the number of nodes contained by the
 * binary search tree.
 */
size_t bst_size(const bst_tree_t* tree) {
  return (tree->size);
}
