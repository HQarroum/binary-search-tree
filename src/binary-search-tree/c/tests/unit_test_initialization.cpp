#include "../binary_search_tree.h"
#include <gtest/gtest.h>
#include <stdint.h>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

TEST(INITIALIZATION, OF_TREE) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  EXPECT_NE(tree, nullptr);
  EXPECT_EQ(tree->root, nullptr);
  EXPECT_EQ(tree->size, 0);
  EXPECT_EQ(tree->options.comparator, &bst_integer_comparator);

  // Destroying the tree.
  bst_destroy(tree);
}

TEST(INITIALIZATION, OF_TREE_WITH_INVALID_COMPARATOR) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = NULL
  });

  EXPECT_EQ(tree, nullptr);
}

TEST(INITIALIZATION, OF_NODE) {
  int value = 1;
  // Creating a new node.
  bst_node_t* node = bst_create_node(&value);

  EXPECT_NE(node, nullptr);
  EXPECT_EQ(node->data, &value);
  EXPECT_EQ(node->left, nullptr);
  EXPECT_EQ(node->right, nullptr);
  EXPECT_EQ(node->parent, nullptr);
  EXPECT_EQ(node->tree, nullptr);

  // Destroying the node.
  free(node);
}

TEST(INITIALIZATION, OF_NODE_WITH_INVALID_DATA) {
  // Creating a new node.
  bst_node_t* node = bst_create_node(NULL);

  EXPECT_EQ(node, nullptr);

  // Destroying the node.
  free(node);
}
