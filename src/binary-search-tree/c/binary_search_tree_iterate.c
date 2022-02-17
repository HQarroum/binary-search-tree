#include "binary_search_tree.h"

/**
 * @brief Iterates over the nodes of the binary-search tree using the given traversal strategy.
 * @param tree The tree to traverse.
 * @param callback A callback function invoked for each node.
 * @param strategy A strategy defining how to traverse the tree.
 * @param user_data A pointer to user data to pass to the callback function.
 */
void bst_traverse_from(const bst_node_t* node, bst_callback_t callback, bst_traversal_strategy_t strategy, void* user_data) {
  strategy(node, callback, user_data);
}

/**
 * @brief Iterates over the nodes of the binary-search tree using the given traversal strategy.
 * @param tree The tree to traverse.
 * @param callback A callback function invoked for each node.
 * @param strategy A strategy defining how to traverse the tree.
 * @param user_data A pointer to user data to pass to the callback function.
 */
void bst_traverse(const bst_tree_t* tree, bst_callback_t callback, bst_traversal_strategy_t strategy, void* user_data) {
  bst_traverse_from(tree->root, callback, strategy, user_data);
}

/**
 * @brief Iterates over the nodes of the binary-search tree using a depth-first traversal strategy.
 * @param tree The tree to traverse.
 * @param callback A callback function invoked for each node.
 * @param strategy A strategy defining how to traverse the tree.
 * @param user_data A pointer to user data to pass to the callback function.
 */
void bst_for_each(const bst_tree_t* tree, bst_callback_t callback, void* user_data) {
  bst_depth_first_traversal(tree->root, callback, user_data);
}
