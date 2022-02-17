#include "binary_search_tree.h"

bst_node_t* bst_attach_node(bst_node_t* node, bst_node_t* new_node, bst_direction_t direction) {
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

const bst_node_t* bst_insert_from(bst_node_t* root, bst_node_t* new_node) {
  bst_tree_t* tree = root->tree;
  int result       = tree->options.comparator(new_node->data, root->data);

  if (result < 0) {
    if (root->left) {
      return (bst_insert_from(root->left, new_node));
    } else {
      return (bst_attach_node(root, new_node, LEFT));
    }
  } else if (result > 0) {
    if (root->right) {
      return (bst_insert_from(root->right, new_node));
    } else {
      return (bst_attach_node(root, new_node, RIGHT));
    }
  } else {
    return (NULL);
  }
}
/**
 * @brief Inserts the given `data` in the binary-search tree.
 * @param tree a pointer to the binary-search tree.
 * @param data a pointer to the data to insert in the binary-search tree.
 * @return a pointer to the created node that wraps the pointer to the given data.
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
