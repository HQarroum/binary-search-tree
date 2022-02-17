#include "binary_search_tree.h"

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

    /* Enqueue the root node. */
    queue[queue_write_idx--] = node;
    queue_size++;

    while (queue_size > 0) {
      /* Dequeue the next node. */
      const bst_node_t* current = queue[queue_read_idx--];
      queue_size--;

      /* Call the callback. */
      callback(current, user_data);

      /* Enqueue the left child. */
      if (current->left) {
        queue[queue_write_idx--] = current->left;
        queue_size++;
      }
      
      /* Enqueue the right child. */
      if (current->right) {
        queue[queue_write_idx--] = current->right;
        queue_size++;
      }
    }
  }
}

void bst_search_traversal(const bst_node_t* node, bst_callback_t callback, void* user_data) {
  bst_search_ctx_t* ctx = (bst_search_ctx_t*) user_data;

  /* Ensure that the node and the given data are valid. */
  if (!node || !node->data || !ctx->data) {
    return;
  }

  /* Comparing the value associated with the nodes. */
  int result = node->tree->options.comparator(ctx->data, node->data);

  if (result < 0) {
    callback(node, user_data);
    bst_search_traversal(node->left, callback, user_data);
  } else if (result > 0) {
    callback(node, user_data);
    bst_search_traversal(node->right, callback, user_data);
  } else {
    callback(node, user_data);
  }
}