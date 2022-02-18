#include "binary_search_tree.h"

/**
 * @brief Iterates over the nodes of the binary-search tree using the given traversal strategy.
 * @param tree The tree to traverse.
 * @param callback A callback function invoked for each node.
 * @param strategy A strategy defining how to traverse the tree.
 * @param user_data A pointer to user data to pass to the callback function.
 */
bst_iterator_ctx_t bst_traverse_from(const bst_node_t* node, bst_callback_t callback, bst_traversal_strategy_t strategy, void* user_data) {
  /* Initializing the iteration context. */
  bst_iterator_ctx_t ctx = {
    .data = user_data,
    .iterations = 0,
    .state = BST_ITERATION_IN_PROGRESS
  };
  
  if (strategy) {
    strategy(node, callback, &ctx);
    ctx.state = BST_ITERATION_DONE;
  } else {
    ctx.state = BST_ITERATION_ERROR;
  }
    
  return (ctx);
}

/**
 * @brief Iterates over the nodes of the binary-search tree using the given traversal strategy.
 * @param tree The tree to traverse.
 * @param callback A callback function invoked for each node.
 * @param strategy A strategy defining how to traverse the tree.
 * @param user_data A pointer to user data to pass to the callback function.
 */
bst_iterator_ctx_t bst_traverse(const bst_tree_t* tree, bst_callback_t callback, bst_traversal_strategy_t strategy, void* user_data) {
  return (bst_traverse_from(tree->root, callback, strategy, user_data));
}

/**
 * @brief Iterates over the nodes of the binary-search tree using a depth-first traversal strategy.
 * @param tree The tree to traverse.
 * @param callback A callback function invoked for each node.
 * @param strategy A strategy defining how to traverse the tree.
 * @param user_data A pointer to user data to pass to the callback function.
 */
bst_iterator_ctx_t bst_for_each(const bst_tree_t* tree, bst_callback_t callback, void* user_data) {
  return (bst_traverse(tree, callback, &bst_depth_first_traversal, user_data));
}
