#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/**
 * @brief Defines the possible states for an
 * iteration process.
 */
typedef enum bst_iteration_state_t {
  BST_ITERATION_IN_PROGRESS,
  BST_ITERATION_DONE,
  BST_ITERATION_ERROR
} bst_iteration_state_t;

/**
 * @brief A structure defining the context of an iterator
 * traversing the tree.
 */
typedef struct bst_iterator_ctx_t {
  const void* data;
  size_t iterations;
  bst_iteration_state_t state;
} bst_iterator_ctx_t;

/**
 * @brief Type definition for the comparator function
 * implementation used to compare nodes together.
 */
typedef int (*bst_comparator_t)(const void*, const void*);

/**
 * @brief Describes the options that can be passed to the
 * binary-search tree.
 */
typedef struct bst_options_t {
  bst_comparator_t comparator;
} bst_options_t;

/**
 * @brief Describes the direction binding that can
 * exist between two nodes.
 */
typedef enum bst_direction_t {
  LEFT,
  RIGHT
} bst_direction_t;

/**
 * @brief Describes a binary-search tree node
 * attributes.
 */
typedef struct bst_node_t {
  const void*        data;
  struct bst_node_t* left;
  struct bst_node_t* right;
  struct bst_node_t* parent;
  struct bst_tree_t* tree;
} bst_node_t;

/**
 * @brief Describes the binary-search tree
 * attributes.
 */
typedef struct bst_tree_t {
  bst_node_t*   root;
  size_t        size;
  bst_options_t options;
} bst_tree_t;


typedef struct bst_sort_result_t {
  const bst_node_t** nodes;
  size_t size;
} bst_sort_result_t;

/**
 * @brief Type definition for the callback function
 * implementation used to traverse the binary-search tree.
 * @param node the currently visited node.
 */
typedef void (*bst_callback_t)(const bst_node_t* node, bst_iterator_ctx_t* ctx);

/**
 * @brief Type definition for the callback function
 * implementation used to traverse the binary-search tree.
 * @param node the starting node from which the traversal will start.
 */
typedef void (*bst_traversal_strategy_t)(const bst_node_t* node, bst_callback_t callback, bst_iterator_ctx_t* ctx);

/**
 * @brief Creates a new dynamically allocated binary-search tree instance.
 * @param options a set of options to pass to the implementation.
 * @return a pointer to the newly created binary-search tree
 */
bst_tree_t* bst_create(bst_options_t options);

/**
 * @brief Creates a new dynamically allocated binary-search node instance.
 * @param data a pointer to the data to initialize the node with.
 * @return a pointer to the newly created binary-search node
 */
bst_node_t* bst_create_node(const void* data);

/**
 * @brief Inserts the given `data` in the binary-search tree.
 * @param tree a pointer to the binary-search tree.
 * @param data a pointer to the data to insert in the binary-search tree.
 * @return a pointer to the created node that wraps the pointer to the given data.
 */
const bst_node_t* bst_insert(bst_tree_t* tree, const void* data);

/**
 * @brief Recursively traverse the subtree to find
 * the node associated with the given `data`.
 * @param node the node to start the traversal from.
 * @param data the data to find in the given subtree.
 * @return a pointer to the found node, or NULL if the node
 * was not found.
 */
const bst_node_t* bst_find_in(const bst_node_t* node, const void* data);

/**
 * @brief A helper function to look up the data `data` from a pointer to a tree.
 * @param tree a pointer to the tree to look up the data in
 * @param data a pointer to the data to look up
 * @return a pointer to the node containing the data, or NULL if the data is not found
 */
const bst_node_t* bst_find(const bst_tree_t* tree, const void* data);

/**
 * @brief Removes the node associated with the given `data` from the binary-search tree
 * starting from the `subtree_root_node`.
 * @param root the root node of the subtree to remove the node from. 
 * @param data the data to remove from the binary-search tree.
 * @return 0 if the node was removed, -1 otherwise.
 */
bst_node_t* bst_remove_from(bst_node_t* root, const void* data);

/**
 * @brief Removes the node associated with the given `data` from the binary-search tree.
 * @param tree a pointer to the binary-search tree.
 * @param data the data to remove from the binary-search tree.
 * @return 0 if the node was removed, -1 otherwise.
 */
bst_node_t* bst_remove(bst_tree_t* tree, const void* data);

/**
 * @brief Recursively traverse the given subtree to find
 * the node associated with the smallest value.
 * @param node the node to start the traversal from.
 * @return a pointer to the node associated with the smallest value.
 */
const bst_node_t* bst_get_min_from(const bst_node_t* node);

/**
 * @brief Recursively traverse the binary-search tree to find
 * the node associated with the smallest value.
 * @param tree the tree to look up the smallest value in.
 * @return a pointer to the node associated with the smallest value.
 */
const bst_node_t* bst_get_min(const bst_tree_t* tree);

/**
 * @brief Recursively traverse the given subtree to find
 * the node associated with the biggest value.
 * @param node the node to start the traversal from.
 * @return a pointer to the node associated with the biggest value.
 */
const bst_node_t* bst_get_max_from(const bst_node_t* node);

/**
 * @brief Recursively traverse the binary-search tree to find
 * the node associated with the biggest value.
 * @param tree the tree to look up the biggest value in.
 * @return a pointer to the node associated with the biggest value.
 */
const bst_node_t* bst_get_max(const bst_tree_t* tree);

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
const bst_node_t* bst_get_kth_largest_from(const bst_node_t* node, size_t k);

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
const bst_node_t* bst_get_kth_smallest_from(const bst_node_t* node, size_t k);

/**
 * @brief A helper function to find the kth largest value in
 * the given binary-search tree.
 * @param tree the tree to look up the kth largest value in.
 * @param k the kth largest value to look up.
 * @return the node associated with the kth largest value in
 * the given binary-search tree, or NULL if no nodes were matching.
 */
const bst_node_t* bst_get_kth_largest(const bst_tree_t* tree, size_t k);

/**
 * @brief A helper function to find the kth smallest value in
 * the given binary-search tree.
 * @param tree the tree to look up the kth smallest value in.
 * @param k the kth smallest value to look up.
 * @return the node associated with the kth smallest value in
 * the given binary-search tree, or NULL if no nodes were matching.
 */
const bst_node_t* bst_get_kth_smallest(const bst_tree_t* tree, size_t k);

/**
 * @param tree The tree to return the size of.
 * @return the number of nodes contained by the
 * binary search tree.
 */
size_t bst_size(const bst_tree_t* tree);

/**
 * @brief Sort the nodes in the tree in ascending order.
 * @param tree the tree to sort.
 * @return a structure `bst_data_t` containing the sorted nodes.
 */
bst_sort_result_t bst_sort(bst_tree_t* tree);

/**
 * @brief Iterates over the nodes of the binary-search tree using the given traversal strategy.
 * @param tree The tree to traverse.
 * @param callback A callback function invoked for each node.
 * @param strategy A strategy defining how to traverse the tree.
 */
bst_iterator_ctx_t bst_traverse_from(const bst_node_t* node, bst_callback_t callback, bst_traversal_strategy_t strategy, void* user_data);

/**
 * @brief Iterates over the nodes of the binary-search tree using the given traversal strategy.
 * @param tree The tree to traverse.
 * @param callback A callback function invoked for each node.
 * @param strategy A strategy defining how to traverse the tree.
 */
bst_iterator_ctx_t bst_traverse(const bst_tree_t* tree, bst_callback_t callback, bst_traversal_strategy_t strategy, void* user_data);

/**
 * @brief Iterates over the nodes of the binary-search tree using the given traversal strategy.
 * @param tree The tree to traverse.
 * @param callback A callback function invoked for each node.
 * @param strategy A strategy defining how to traverse the tree.
 */
bst_iterator_ctx_t bst_for_each(const bst_tree_t* tree, bst_callback_t callback, void* user_data);

/**
 * @brief A traversal strategy to traverse the binary-search tree in-order.
 * Can be used to implement a tree-sort on the tree elements to sort the tree.
 * @param node The node to start the traversal from.
 * @param callback A callback function invoked for each node.
 */
void bst_in_order_traversal(const bst_node_t* node, bst_callback_t callback, bst_iterator_ctx_t* ctx);

/**
 * @brief A traversal strategy to traverse the binary-search tree post-order.
 * @param node The node to start the traversal from.
 * @param callback A callback function invoked for each node.
 */
void bst_post_order_traversal(const bst_node_t* node, bst_callback_t callback, bst_iterator_ctx_t* ctx);

/**
 * @brief A traversal strategy to traverse the binary-search tree in a depth-first manner.
 * @param node The node to start the traversal from.
 * @param callback A callback function invoked for each node.
 */
void bst_depth_first_traversal(const bst_node_t* node, bst_callback_t callback, bst_iterator_ctx_t* ctx);

/**
 * @brief A traversal strategy to traverse the binary-search tree in a breadth-first manner.
 * @param node The node to start the traversal from.
 * @param callback A callback function invoked for each node.
 */
void bst_breadth_first_traversal(const bst_node_t* node, bst_callback_t callback, bst_iterator_ctx_t* ctx);

void bst_search_traversal(const bst_node_t* node, bst_callback_t callback, bst_iterator_ctx_t* ctx);

/**
 * @brief A function implementation comparing the value of two nodes as integers.
 * @param a the value of the reference node.
 * @param b the value of the compared node.
 * @return 0 if the values are equal, a negative value if the value of `a` is less than `b`,
 * and a positive value if the value of `a` is greater than `b`.
 */
int bst_integer_comparator(const void* a, const void* b);

/**
 * @brief A function implementation comparing the value of two nodes as strings.
 * @param a the value of the reference node.
 * @param b the value of the compared node.
 * @return 0 if the values are equal, a negative value if the value of `a` is less than `b`,
 * and a positive value if the value of `a` is greater than `b`.
 */
int bst_string_comparator(const void* a, const void* b);

/**
 * @brief Clears the given binary-search subtree.
 * @param node the node associated with the subtree to clear.
 * @return the number of nodes removed from the tree.
 */
void bst_clear_from(bst_node_t* node);

/**
 * @brief Clears the binary-search tree.
 * @param tree the tree to destroy.
 * @return the number of nodes removed from the tree.
 */
void bst_clear(bst_tree_t* tree);

/**
 * @brief Destroys the binary-search tree and its associated
 * nodes.
 * @param tree the tree to destroy.
 */
void bst_destroy(bst_tree_t* tree);

#ifdef __cplusplus
}
#endif

#endif /* BINARY_SEARCH_TREE_H */
