#include "../binary_search_tree.h"
#include <gtest/gtest.h>
#include <stdint.h>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

  /** The tree must be layed-out acccording to the following structure.  */
  /**                       hello                                        */
  /**                     /      \                                       */
  /**                   foo      world                                   */
  /**                   /          /                                      */
  /**                 bar         qux                                     */
  /**                    \      /      \                                 */
  /**                   baz  long_str   string                            */
static const char* data[] = {
  "hello",
  "world",
  "foo",
  "bar",
  "baz",
  "qux",
  "string",
  "long_string"
};

TEST(INSERTION_STRING, OF_NODES) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_string_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i)
    bst_insert(tree, data[i]);
  
  // Verifying that the nodes have been inserted.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i)
    EXPECT_NE(bst_find(tree, data[i]), nullptr);

  // Destroying the tree.
  bst_destroy(tree);
}

TEST(INSERTION_STRING, PLACEMENT_OF_NODES) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_string_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i)
    bst_insert(tree, data[i]);
  
  EXPECT_EQ(tree->root->data, data[0]);
  EXPECT_EQ(tree->root->left->data, data[2]);
  EXPECT_EQ(tree->root->right->data, data[1]);
  EXPECT_EQ(tree->root->left->left->data, data[3]);
  EXPECT_EQ(tree->root->right->left->data, data[5]);
  EXPECT_EQ(tree->root->right->left->left->data, data[7]);
  EXPECT_EQ(tree->root->left->left->right->data, data[4]);
  EXPECT_EQ(tree->root->right->left->right->data, data[6]);
  
  // Destroying the tree.
  bst_destroy(tree);
}

TEST(INSERTION_STRING, SIZE_OF_THE_TREE) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_string_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    EXPECT_EQ(tree->size, i);
    bst_insert(tree, data[i]);
  }

  EXPECT_EQ(tree->size, ARRAY_SIZE(data));
  
  // Destroying the tree.
  bst_destroy(tree);
}

TEST(INSERTION_STRING, NODE_PROPERTIES) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_string_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    const bst_node_t* node = bst_insert(tree, data[i]);
    EXPECT_EQ(node->tree, tree);
  }

  EXPECT_EQ(tree->root->parent, nullptr);
  EXPECT_EQ(tree->root->left->parent, tree->root);
  EXPECT_EQ(tree->root->right->parent, tree->root);
  EXPECT_EQ(tree->root->left->left->parent, tree->root->left);
  EXPECT_EQ(tree->root->right->left->parent, tree->root->right);
  EXPECT_EQ(tree->root->right->left->left->parent, tree->root->right->left);
  EXPECT_EQ(tree->root->left->left->right->parent, tree->root->left->left);
  EXPECT_EQ(tree->root->right->left->right->parent, tree->root->right->left);
  
  // Destroying the tree.
  bst_destroy(tree);
}
