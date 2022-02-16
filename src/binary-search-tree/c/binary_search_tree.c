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

bst_node_t* bst_attach_node(bst_node_t* node, bst_node_t* new_node, bst_direction_t direction) {
  /* When no directions are set, we don't attach the node. */
  if (direction == NO_DIRECTION) {
    return (NULL);
  }

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

/**
 * @brief Recursively traverse the subtree to find
 * the node associated with the given `data`.
 * @param node the node to start the traversal from.
 * @param data the data to find in the given subtree.
 * @return a pointer to the found node, or NULL if the node
 * was not found.
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
 * @brief A helper function to find the node associated with `data`
 * a binary-search tree.
 * @param tree a pointer to the tree to look up the data in
 * @param data a pointer to the data to look up
 * @return a pointer to the node containing the data, or NULL if the node
 * was not found.
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
 */
const bst_node_t* bst_get_min(const bst_tree_t* tree) {
  return (bst_get_min_from(tree->root));
}

/**
 * @brief Recursively traverse the given subtree to find
 * the node associated with the biggest value.
 * @param node the node to start the traversal from.
 * @return a pointer to the node associated with the biggest value.
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
 */
const bst_node_t* bst_get_max(const bst_tree_t* tree) {
  return (bst_get_max_from(tree->root));
}

/**
 * @brief Removes the node associated with the given `data` from the binary-search tree
 * starting from the `subtree_root_node`.
 * @param node the node of the subtree to walk the tree from. 
 * @param data the data to remove from the binary-search tree.
 * @return 0 if the node was removed, -1 otherwise.
 */
bst_node_t* bst_remove_from(bst_node_t* node, const void* data) {
  if (!node || !data)
    return (0);
  
  /* Retieving the tree associated with the node. */
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
 * @param tree The tree to return the size of.
 * @return the number of nodes contained by the
 * binary search tree.
 */
size_t bst_size(const bst_tree_t* tree) {
  return (tree->size);
}

/**
 * @brief Clears the given binary-search subtree.
 * @param node the node associated with the subtree to clear.
 * @return the number of nodes removed from the tree.
 */
void bst_clear_from(bst_node_t* node) {
  if (!node) return;
  bst_clear_from(node->left);
  bst_clear_from(node->right);
  if (node->parent) {
    if (node->parent->left == node) node->parent->left = NULL;
    if (node->parent->right == node) node->parent->right = NULL;
  }
  node->tree->size--;
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

/**
 * @brief A function implementation comparing the value of two nodes as integers.
 * @param a the value of the reference node.
 * @param b the value of the compared node.
 * @return 0 if the values are equal, a negative value if the value of `a` is less than `b`,
 * and a positive value if the value of `a` is greater than `b`.
 */
int bst_integer_comparator(const void* a, const void* b) {
  return (*(const int*)a - *(const int*)b);
}

/**
 * @brief A function implementation comparing the value of two nodes as strings.
 * @param a the value of the reference node.
 * @param b the value of the compared node.
 * @return 0 if the values are equal, a negative value if the value of `a` is less than `b`,
 * and a positive value if the value of `a` is greater than `b`.
 */
int bst_string_comparator(const void* a, const void* b) {
  return (strcmp((const char*)a, (const char*)b));
}

/**
 * @brief A traversal strategy to traverse the binary-search tree in-order.
 * Can be used to implement a tree-sort on the tree elements to sort the tree.
 * @param node The node to start the traversal from.
 * @param callback A callback function invoked for each node.
 */
void bst_in_order_traversal(const bst_node_t* node, bst_callback_t callback, void* user_data) {
  if (node) {
    bst_in_order_traversal(node->left, callback, user_data);
    callback(node, user_data);
    bst_in_order_traversal(node->right, callback, user_data);
  }
}

/**
 * @brief A traversal strategy to traverse the binary-search tree post-order.
 * @param node The node to start the traversal from.
 * @param callback A callback function invoked for each node.
 */
void bst_post_order_traversal(const bst_node_t* node, bst_callback_t callback, void* user_data) {
  if (node) {
    bst_post_order_traversal(node->left, callback, user_data);
    bst_post_order_traversal(node->right, callback, user_data);
    callback(node, user_data);
  }
}

/**
 * @brief A traversal strategy to traverse the binary-search tree in a depth-first manner.
 * @param node The node to start the traversal from.
 * @param callback A callback function invoked for each node.
 */
void bst_depth_first_traversal(const bst_node_t* node, bst_callback_t callback, void* user_data) {
  if (node) {
    callback(node, user_data);
    bst_depth_first_traversal(node->left, callback, user_data);
    bst_depth_first_traversal(node->right, callback, user_data);
  }
}

/**
 * @brief A traversal strategy to traverse the binary-search tree in a breadth-first manner.
 * @param node The node to start the traversal from.
 * @param callback A callback function invoked for each node.
 */
void bst_breadth_first_traversal(const bst_node_t* node, bst_callback_t callback, void* user_data) {
  if (node) {
    size_t queue_write_idx = node->tree->size - 1;
    size_t queue_read_idx  = queue_write_idx;
    size_t queue_size      = 0;
  
    /* The queue holding the nodes to be visited. */
    const bst_node_t* queue[node->tree->size];

    queue[queue_write_idx--] = node;
    queue_size++;

    while (queue_size > 0) {
      const bst_node_t* current = queue[queue_read_idx--];
      queue_size--;
      callback(current, user_data);

      if (current->left) {
        queue[queue_write_idx--] = current->left;
        queue_size++;
      }

      if (current->right) {
        queue[queue_write_idx--] = current->right;
        queue_size++;
      }
    }
  }
}

/**
 * @brief Iterates over the nodes of the binary-search tree using the given traversal strategy.
 * @param tree The tree to traverse.
 * @param callback A callback function invoked for each node.
 * @param strategy A strategy defining how to traverse the tree.
 */
void bst_traverse_from(const bst_node_t* node, bst_callback_t callback, bst_traversal_strategy_t strategy, void* user_data) {
  strategy(node, callback, user_data);
}

/**
 * @brief Iterates over the nodes of the binary-search tree using the given traversal strategy.
 * @param tree The tree to traverse.
 * @param callback A callback function invoked for each node.
 * @param strategy A strategy defining how to traverse the tree.
 */
void bst_traverse(const bst_tree_t* tree, bst_callback_t callback, bst_traversal_strategy_t strategy, void* user_data) {
  bst_traverse_from(tree->root, callback, strategy, user_data);
}

/**
 * @brief Iterates over the nodes of the binary-search tree using a depth-first traversal strategy.
 * @param tree The tree to traverse.
 * @param callback A callback function invoked for each node.
 * @param strategy A strategy defining how to traverse the tree.
 */
void bst_for_each(const bst_tree_t* tree, bst_callback_t callback, void* user_data) {
  bst_depth_first_traversal(tree->root, callback, user_data);
}
