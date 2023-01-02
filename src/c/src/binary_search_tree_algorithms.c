#include <binary_search_tree.h>

/**
 * @brief A traversal strategy to traverse the binary-search tree in-order.
 * Can be used to implement a tree-sort on the tree elements to sort the tree.
 * @param node The node to start the traversal from.
 * @param callback A callback function invoked for each node.
 */
void bst_in_order_traversal(const bst_node_t* node, bst_callback_t callback, bst_iterator_ctx_t* ctx) {
  if (node && callback && ctx->state == BST_ITERATION_IN_PROGRESS) {
    bst_in_order_traversal(node->left, callback, ctx);
    ctx->iterations++;
    callback(node, ctx);
    bst_in_order_traversal(node->right, callback, ctx);
  }
}

/**
 * @brief A traversal strategy to traverse the binary-search tree post-order.
 * @param node The node to start the traversal from.
 * @param callback A callback function invoked for each node.
 */
void bst_post_order_traversal(const bst_node_t* node, bst_callback_t callback, bst_iterator_ctx_t* ctx) {
  if (node && callback && ctx->state == BST_ITERATION_IN_PROGRESS) {
    bst_post_order_traversal(node->left, callback, ctx);
    bst_post_order_traversal(node->right, callback, ctx);
    ctx->iterations++;
    callback(node, ctx);
  }
}

/**
 * @brief A traversal strategy to traverse the binary-search tree in a depth-first manner.
 * @param node The node to start the traversal from.
 * @param callback A callback function invoked for each node.
 */
void bst_depth_first_traversal(const bst_node_t* node, bst_callback_t callback, bst_iterator_ctx_t* ctx) {
  if (node && callback && ctx->state == BST_ITERATION_IN_PROGRESS) {
    ctx->iterations++;
    callback(node, ctx);
    bst_depth_first_traversal(node->left, callback, ctx);
    bst_depth_first_traversal(node->right, callback, ctx);
  }
}

/**
 * @brief A traversal strategy to traverse the binary-search tree in a breadth-first manner.
 * @param node The node to start the traversal from.
 * @param callback A callback function invoked for each node.
 */
void bst_breadth_first_traversal(const bst_node_t* node, bst_callback_t callback, bst_iterator_ctx_t* ctx) {
  if (node && callback && ctx->state == BST_ITERATION_IN_PROGRESS) {
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
      ctx->iterations++;
      callback(current, ctx);

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

/**
 * @brief A traversal strategy to allow users to search for an element in the tree
 * by being called back at each iteration of the traversal.
 * @param node The node to start the traversal from.
 * @param callback A callback function invoked for each node.
 * @param ctx The iteration context.
 */
void bst_search_traversal(const bst_node_t* node, bst_callback_t callback, bst_iterator_ctx_t* ctx) {
  /* Ensure that the node and the given data are valid. */
  if (!node || !node->data || !ctx->data || ctx->state != BST_ITERATION_IN_PROGRESS || !callback) {
    return;
  }

  /* Comparing the value associated with the nodes. */
  int result = node->tree->options.comparator(ctx->data, node->data);

  /* Incrementing the iteration count. */
  ctx->iterations++;
  
  if (result < 0) {
    callback(node, ctx);
    bst_search_traversal(node->left, callback, ctx);
  } else if (result > 0) {
    callback(node, ctx);
    bst_search_traversal(node->right, callback, ctx);
  } else {
    callback(node, ctx);
  }
}