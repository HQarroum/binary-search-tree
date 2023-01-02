#include <binary_search_tree.h>

/**
 * @brief Removes the node associated with the given `data` from the binary-search tree
 * starting from the given subtree.
 * @param node the node of the subtree to walk the tree from. 
 * @param data the data to remove from the binary-search tree.
 * @return a pointer to the successor node, or a NULL value
 * if there is no successor.
 */
bst_node_t* bst_remove_from(bst_node_t* node, const void* data) {
  if (!node || !data)
    return (0);
  
  /* Retrieving the tree associated with the node. */
  bst_tree_t* tree = node->tree;
  /* Comparing the value associated with the nodes. */
  int result = node->tree->options.comparator(data, node->data);
  
  if (result < 0)
    node->left = bst_remove_from(node->left, data);
  else if (result > 0)
    node->right = bst_remove_from(node->right, data);
  else {
    /* The node doesn't have any children. */
    if (!node->left && !node->right) {
      /* If the node is the root, we need to set the root to NULL. */
      if (tree->root == node) tree->root = NULL;
      free(node);
      tree->size--;
      return (NULL);
    /* The node has one child. */
    } else if (!node->left || !node->right) {
      /* Finding the child node. */
      bst_node_t* successor = node->right ? node->right : node->left;
      /* Setting the new parent of the child node. */
      successor->parent = node->parent;
      /* If the node is the root, the child node becomes the new root. */
      if (tree->root == node) tree->root = successor;
      free(node);
      tree->size--;
      return (successor);
    /* The node has two children. */
    } else {
      const bst_node_t* successor = bst_get_min_from(node->right);
      node->data = successor->data;
      node->right = bst_remove_from(node->right, successor->data);
    }
  }
  return (node);
}

/**
 * @brief Removes the node associated with the given `data` from the binary-search tree.
 * @param tree a pointer to the binary-search tree.
 * @param data the data to remove from the binary-search tree.
 * @return 0 if the node was removed, -1 otherwise.
 */
bst_node_t* bst_remove(bst_tree_t* tree, const void* data) {
  return (bst_remove_from(tree->root, data));
}

/**
 * @brief Clears the given binary-search subtree.
 * @param node the node associated with the subtree to clear.
 * @return the number of nodes removed from the tree.
 */
void bst_clear_from(bst_node_t* node) {
  if (!node) return;

  /* Recursively clear the left subtree. */
  bst_clear_from(node->left);
  bst_clear_from(node->right);

  /* Detaching the node from its parent. */
  if (node->parent && node->parent->left == node)
    node->parent->left = NULL;
  if (node->parent && node->parent->right == node)
    node->parent->right = NULL;

  /* Decremeneting the size of the tree. */
  node->tree->size--;

  /* If the node is the root, we need to set the root to NULL. */
  if (node->tree->root == node) {
    node->tree->root = NULL;
  }
  free(node);
}

/**
 * @brief Clears the binary-search tree.
 * @param tree the tree to destroy.
 * @return the number of nodes removed from the tree.
 */
void bst_clear(bst_tree_t* tree) {
  bst_clear_from(tree->root);
}

/**
 * @brief Destroys the binary-search tree and its associated
 * nodes.
 * @param tree the tree to destroy.
 */
void bst_destroy(bst_tree_t* tree) {
  bst_clear(tree);
  free(tree);
}
