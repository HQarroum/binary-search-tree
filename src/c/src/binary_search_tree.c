#include <binary_search_tree.h>

/**
 * @brief Creates a new dynamically allocated binary-search tree instance.
 * @param options a set of options to pass to the implementation.
 * @return a pointer to the newly created binary-search tree
 */
bst_tree_t* bst_create(bst_options_t options) {
  bst_tree_t* tree = NULL;

  /* The comparator function is required to */
  /* create the binary-search tree. */
  if (options.comparator == NULL) {
    return (NULL);
  }

  /* Allocating memory for the binary-search tree. */
  if ((tree = calloc(1, sizeof(bst_tree_t))) == NULL) {
    return (NULL);
  }
  
  tree->options = options;
  return (tree);
}

/**
 * @brief Creates a new dynamically allocated binary-search node instance.
 * @param data a pointer to the data to initialize the node with.
 * @return a pointer to the newly created binary-search node
 */
bst_node_t* bst_create_node(const void* data) {
  bst_node_t* node = NULL;

  /* Non-null data is required to create a node. */
  if (data == NULL) {
    return (NULL);
  }

  /* Allocating memory for the node. */
  if ((node = calloc(1, sizeof(bst_node_t))) == NULL) {
    return (NULL);
  }

  /* Assigning the data to the node. */
  node->data = data;

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

/**
 * @brief A callback storing the nodes in an array
 * as they are traversed, and keeps track of the size
 * of the array.
 * @param node the currently visited node.
 * @param data a pointer to a `bst_data_t` structure.
 */
static void bst_sort_callback(const bst_node_t* node, bst_iterator_ctx_t* ctx) {
  bst_sort_result_t* sort_data = (bst_sort_result_t*) ctx->data;
  sort_data->nodes[sort_data->size++] = node;
}

/**
 * @brief Sort the nodes in the given subtree.
 * @param node the root of the subtree to sort.
 * @return a structure `bst_sort_data_t` containing the sorted nodes.
 */
static bst_sort_result_t bst_sort_from(bst_node_t* node) {
  /* Initializing the sort result structure. */
  bst_sort_result_t data = {
    .nodes = NULL,
    .size = 0
  };

  /* Allocating memory for the nodes. */
  if ((data.nodes = calloc(bst_size(node->tree), sizeof(bst_node_t*))) == NULL) {
    return (data);
  }

  /* Using an in-order traversal to sort the nodes. */
  bst_traverse_from(node, &bst_sort_callback, &bst_in_order_traversal, &data);
  return (data);
}

/**
 * @brief Sort the nodes in the tree in ascending order.
 * @param tree the tree to sort.
 * @return a structure `bst_sort_data_t` containing the sorted nodes.
 */
bst_sort_result_t bst_sort(bst_tree_t* tree) {
  if (tree && tree->root) {
    return (bst_sort_from(tree->root));
  }
  return ((bst_sort_result_t) {
    .nodes = NULL,
    .size = 0
  });
}