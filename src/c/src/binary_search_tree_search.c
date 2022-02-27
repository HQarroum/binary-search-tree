#include <binary_search_tree.h>

/**
 * @brief Recursively traverse the subtree to find
 * the node associated with the given `data`.
 * @param node the node to start the traversal from.
 * @param data the data to find in the given subtree.
 * @return a pointer to the found node, or NULL if the node
 * was not found.
 * @note Complexity is O(log(n)) on average, O(n) in the worst case.
 */
const bst_node_t* bst_find_in(const bst_node_t* node, const void* data) {
  /* Ensure that the node and the given data are valid. */
  if (!node || !node->data || !data) {
    return (NULL);
  }

  /* Comparing the value associated with the nodes. */
  int result = node->tree->options.comparator(data, node->data);

  if (result < 0) {
    return (bst_find_in(node->left, data));
  } else if (result > 0) {
    return (bst_find_in(node->right, data));
  } else {
    return (node);
  }
}

/**
 * @brief A function to find the node associated with `data`
 * in a binary-search tree.
 * @param tree a pointer to the tree to look up the data in
 * @param data a pointer to the data to look up
 * @return a pointer to the node containing the data, or NULL if the node
 * was not found.
 * @note Complexity is O(log(n)) on average, O(n) in the worst case.
 */
const bst_node_t* bst_find(const bst_tree_t* tree, const void* data) {
  if (!tree || !tree->root || !data) {
    return (NULL);
  }
  return (bst_find_in(tree->root, data));
}

/**
 * @brief Recursively traverse the given subtree to find
 * the node associated with the smallest value.
 * @param node the node to start the traversal from.
 * @return a pointer to the node associated with the smallest value.
 * @note Complexity is O(log(n)) on average, O(n) on the worst case.
 */
const bst_node_t* bst_get_min_from(const bst_node_t* node) {
  while (node->left != NULL)
    node = node->left;
  return (node);
}

/**
 * @brief Recursively traverse the binary-search tree to find
 * the node associated with the smallest value.
 * @param tree the tree to look up the smallest value in.
 * @return a pointer to the node associated with the smallest value.
 * @note Complexity is O(log(n)) on average, O(n) on the worst case.
 */
const bst_node_t* bst_get_min(const bst_tree_t* tree) {
  return (bst_get_min_from(tree->root));
}

/**
 * @brief Recursively traverse the given subtree to find
 * the node associated with the biggest value.
 * @param node the node to start the traversal from.
 * @return a pointer to the node associated with the biggest value.
 * @note Complexity is O(log(n)) on average, O(n) on the worst case.
 */
const bst_node_t* bst_get_max_from(const bst_node_t* node) {
  while (node->right != NULL)
    node = node->right;
  return (node);
}

/**
 * @brief Recursively traverse the binary-search tree to find
 * the node associated with the biggest value.
 * @param tree the tree to look up the biggest value in.
 * @return a pointer to the node associated with the biggest value.
 * @note Complexity is O(log(n)) on average, O(n) on the worst case.
 */
const bst_node_t* bst_get_max(const bst_tree_t* tree) {
  return (bst_get_max_from(tree->root));
}

/**
 * @brief Computes the kth number associated with a given direction
 * in a subtree.
 * @param node the root node associated with the subtree to
 * look up the kth largest value in.
 * @param k a pointer to the kth number to look up.
 * @param direction whether to look up the kth smallest or largest value.
 * @return the node associated with the kth value associated with the given direction
 * in the given subtree, or NULL if no nodes were matching.
 */
static const bst_node_t* bst_get_kth_number_from(const bst_node_t* node, size_t* k, bst_direction_t direction) {
  /* Ensure that the node is valid. */
  if (!node) {
    return (NULL);
  }

  /* Iterating until we reach the largest value. */
  const bst_node_t* result = bst_get_kth_number_from(direction == RIGHT ?
    node->right : node->left,
    k,
    direction
  );

  /* If the kth largest value is in the right subtree,
   * return the node associated with the kth largest value. */
  if (result) {
    return (result);
  }

  /* Once we reached the largest value, we decrement k for each
  number of nodes traversed backwards. */
  (*k)--;

  /* If the current node is the kth smallest, we return it. */
  if (*k == 0) {
    return (node);
  }

  /* Iterating over the opposite subtree to traverse all nodes. */
  return (bst_get_kth_number_from(direction == RIGHT ?
    node->left : node->right,
    k,
    direction
  ));
}

/**
 * @brief A helper function to find the kth largest value in
 * the given subtree.
 * @param node the root node associated with the subtree to
 * look up the kth largest value in.
 * @param k the kth largest value to look up.
 * @param count the number of nodes visited so far.
 * @return the node associated with the kth largest value in
 * the given subtree, or NULL if no nodes were matching.
 */
const bst_node_t* bst_get_kth_largest_from(const bst_node_t* node, size_t k) {
  return (bst_get_kth_number_from(node, &k, RIGHT));
}

/**
 * @brief A helper function to find the kth smallest value in
 * the given subtree.
 * @param node the root node associated with the subtree to
 * look up the kth smallest value in.
 * @param k the kth smallest value to look up.
 * @param count the number of nodes visited so far.
 * @return the node associated with the kth smallest value in
 * the given subtree, or NULL if no nodes were matching.
 */
const bst_node_t* bst_get_kth_smallest_from(const bst_node_t* node, size_t k) {
  return (bst_get_kth_number_from(node, &k, LEFT));
}

/**
 * @brief A helper function to find the kth largest value in
 * the given binary-search tree.
 * @param tree the tree to look up the kth largest value in.
 * @param k the kth largest value to look up.
 * @return the node associated with the kth largest value in
 * the given binary-search tree, or NULL if no nodes were matching.
 */
const bst_node_t* bst_get_kth_largest(const bst_tree_t* tree, size_t k) {
  return (bst_get_kth_largest_from(tree->root, k));
}

/**
 * @brief A helper function to find the kth smallest value in
 * the given binary-search tree.
 * @param tree the tree to look up the kth smallest value in.
 * @param k the kth smallest value to look up.
 * @return the node associated with the kth smallest value in
 * the given binary-search tree, or NULL if no nodes were matching.
 */
const bst_node_t* bst_get_kth_smallest(const bst_tree_t* tree, size_t k) {
  return (bst_get_kth_smallest_from(tree->root, k));
}
