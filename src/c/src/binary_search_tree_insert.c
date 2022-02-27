#include <binary_search_tree.h>

/**
 * @brief A helper function to attach a node to another node.
 * @param node the node to attach the new node to.
 * @param new_node the new node to attach.
 * @param direction whether the new node should be attached to the left or right.
 * @return a pointer to the newly attached node.
 * @note Complexity is O(log(n)) on average, O(n) on the worst case.
 */
static const bst_node_t* bst_attach_node(bst_node_t* node, bst_node_t* new_node, bst_direction_t direction) {
  if (direction == LEFT) {
    node->left = new_node;
  } else {
    node->right = new_node;
  }
  new_node->parent = node;
  new_node->tree = node->tree;
  new_node->tree->size++;
  return (new_node);
}

/**
 * @brief Inserts a new node into the given subtree.
 * @param node the root of the subtree to insert the node into.
 * @param new_node the new node to insert.
 * @return a pointer to the newly inserted node.
 * @note Complexity is O(log(n)) on average, O(n) on the worst case.
 */
static const bst_node_t* bst_insert_from(bst_node_t* node, bst_node_t* new_node) {
  int result = node->tree->options.comparator(new_node->data, node->data);

  if (result < 0) {
    if (node->left) {
      return (bst_insert_from(node->left, new_node));
    } else {
      return (bst_attach_node(node, new_node, LEFT));
    }
  } else if (result > 0) {
    if (node->right) {
      return (bst_insert_from(node->right, new_node));
    } else {
      return (bst_attach_node(node, new_node, RIGHT));
    }
  } else {
    return (node);
  }
}

/**
 * @brief Inserts the given `data` in the binary-search tree.
 * @param tree a pointer to the binary-search tree.
 * @param data a pointer to the data to insert in the binary-search tree.
 * @return a pointer to the created node that wraps the pointer to the given data.
 * @note Complexity is O(log(n)) on average, O(n) on the worst case.
 */
const bst_node_t* bst_insert(bst_tree_t* tree, const void* data) {
  bst_node_t* node = bst_create_node(data);

  /* The tree is empty. */
  if (!tree->root) {
    tree->size = 1;
    node->tree = tree;
    return (tree->root = node);
  }

  return (bst_insert_from(tree->root, node));
}
