#include "../binary_search_tree.h"
#include <gtest/gtest.h>
#include <stdint.h>
#include <algorithm>
#include <vector>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

  /** The tree must be layed-out acccording to the following structure. */
  /**                        50                                          */
  /**                       /  \                                         */
  /**                     20     70                                      */
  /**                    /  \   /  \                                     */
  /**                  10   40 60  90                                    */
  /**                               \                                    */
  /**                                100                                 */
static const int data[] = { 50, 70, 60, 20, 90, 10, 40, 100 };

/**
 * @brief A structure defining the number
 * of iterations performed as well as the iterated nodes
 * in the order in which they were traversed.
 */
struct context_t {
  size_t iterations;
  const bst_node_t* nodes[ARRAY_SIZE(data)];
};

/**
 * @brief Called back for each node in the tree.
 * @param node the currently visited node.
 * @param data a pointer to the user-defined data.
 */
void default_traversal_callback(const bst_node_t* node, bst_iterator_ctx_t* ctx) {
  if (!node) {
    assert("Node is NULL");
  }
}

/**
 * @brief Called back for each node in the tree.
 * @param node the currently visited node.
 * @param data a pointer to the user-defined data.
 */
void ordered_traversal_callback(const bst_node_t* node, bst_iterator_ctx_t* ctx) {
  if (!node) {
    assert("Node is NULL");
  }
  context_t* context = (context_t*) ctx->data;
  context->nodes[context->iterations++] = node;
}

/**
 * @brief Defines whether the given array is sorted.
 * @param array an array of nodes.
 * @param size the size of the array.
 * @return true if the array is sorted, false otherwise.
 */
static bool is_sorted(const bst_node_t* array[], size_t size) {
  for (size_t i = 0; i < size - 1; ++i) {
    const int* a = static_cast<const int*>(array[i]->data);
    const int* b = static_cast<const int*>(array[i + 1]->data);
    if (*a > *b) return (false);
  }
  return (true);
}

TEST(ITERATION, DEFAULT_TRAVERSAL) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i)
    bst_insert(tree, &data[i]);

  // Iterating over the nodes.
  bst_iterator_ctx_t ctx = bst_for_each(tree, &default_traversal_callback, NULL);

  // The number of iterations must be equal to the number of nodes.
  EXPECT_EQ(ctx.iterations, ARRAY_SIZE(data));

  bst_destroy(tree);
}

TEST(ITERATION, IN_ORDER_TRAVERSAL) {
  context_t context_tree    = {};

  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i)
    bst_insert(tree, &data[i]);

  // Iterating over the tree.
  bst_iterator_ctx_t ctx = bst_traverse(tree, &ordered_traversal_callback, &bst_in_order_traversal, &context_tree);
  EXPECT_EQ(ctx.iterations, ARRAY_SIZE(data));
  EXPECT_EQ(context_tree.iterations, ctx.iterations);
  EXPECT_TRUE(is_sorted(context_tree.nodes, context_tree.iterations));

  bst_destroy(tree);
}

TEST(ITERATION, POST_ORDER_TRAVERSAL) {
  context_t context = {};

  const int expected[] = { 10, 40, 20, 60, 100, 90, 70, 50 };

  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i)
    bst_insert(tree, &data[i]);

  // Iterating over the nodes.
  bst_iterator_ctx_t ctx = bst_traverse(tree, &ordered_traversal_callback, &bst_post_order_traversal, &context);

  // The number of iterations must be equal to the number of nodes.
  EXPECT_EQ(context.iterations, ARRAY_SIZE(data));
  EXPECT_EQ(context.iterations, ctx.iterations);
  
  // Comparing the results.
  for (size_t i = 0; i < context.iterations; ++i) {
    const int* value = static_cast<const int*>(context.nodes[i]->data);
    EXPECT_EQ(*value, expected[i]);
  }

  bst_destroy(tree);
}

TEST(ITERATION, DEPTH_FIRST_TRAVERSAL) {
  context_t context = {};

  const int expected[] = { 50, 20, 10, 40, 70, 60, 90, 100 };

  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i)
    bst_insert(tree, &data[i]);

  // Iterating over the nodes.
  bst_iterator_ctx_t ctx = bst_traverse(tree, &ordered_traversal_callback, &bst_depth_first_traversal, &context);

  // The number of iterations must be equal to the number of nodes.
  EXPECT_EQ(context.iterations, ARRAY_SIZE(data));
  EXPECT_EQ(context.iterations, ctx.iterations);
  
  // Comparing the results.
  for (size_t i = 0; i < context.iterations; ++i) {
    const int* value = static_cast<const int*>(context.nodes[i]->data);
    EXPECT_EQ(*value, expected[i]);
  }

  bst_destroy(tree);
}

TEST(ITERATION, BREADTH_FIRST_TRAVERSAL) {
  context_t context = {};

  const int expected[] = { 50, 20, 70, 10, 40, 60, 90, 100 };

  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i)
    bst_insert(tree, &data[i]);

  // Iterating over the nodes.
  bst_iterator_ctx_t ctx = bst_traverse(tree, &ordered_traversal_callback, &bst_breadth_first_traversal, &context);

  // The number of iterations must be equal to the number of nodes.
  EXPECT_EQ(context.iterations, ARRAY_SIZE(data));
  EXPECT_EQ(context.iterations, ctx.iterations);
  
  // Comparing the results.
  for (size_t i = 0; i < context.iterations; ++i) {
    const int* value = static_cast<const int*>(context.nodes[i]->data);
    EXPECT_EQ(*value, expected[i]);
  }

  bst_destroy(tree);
}
