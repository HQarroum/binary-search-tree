#include "../binary_search_tree.h"
#include <gtest/gtest.h>
#include <stdint.h>

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

TEST(INSERTION, OF_NODES) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    bst_insert(tree, &data[i]);
  }
  
  // Verifying that the nodes have been inserted.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    EXPECT_NE(bst_find(tree, &data[i]), nullptr);
  }

  // Destroying the tree.
  bst_destroy(tree);
}

TEST(INSERTION, PLACEMENT_OF_NODES) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    bst_insert(tree, &data[i]);
  }
  
  EXPECT_EQ(tree->root->data, &data[0]);
  EXPECT_EQ(tree->root->left->data, &data[3]);
  EXPECT_EQ(tree->root->left->left->data, &data[5]);
  EXPECT_EQ(tree->root->left->right->data, &data[6]);
  EXPECT_EQ(tree->root->right->data, &data[1]);
  EXPECT_EQ(tree->root->right->left->data, &data[2]);
  EXPECT_EQ(tree->root->right->right->data, &data[4]);
  EXPECT_EQ(tree->root->right->right->right->data, &data[7]);

  // Destroying the tree.
  bst_destroy(tree);
}

TEST(INSERTION, SIZE_OF_THE_TREE) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    EXPECT_EQ(tree->size, i);
    bst_insert(tree, &data[i]);
  }

  EXPECT_EQ(tree->size, ARRAY_SIZE(data));
  
  // Destroying the tree.
  bst_destroy(tree);
}

TEST(INSERTION, NODE_PROPERTIES) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    const bst_node_t* node = bst_insert(tree, &data[i]);
    EXPECT_EQ(node->tree, tree);
  }

  EXPECT_EQ(tree->root->parent, nullptr);
  EXPECT_EQ(tree->root->left->parent, tree->root);
  EXPECT_EQ(tree->root->left->left->parent, tree->root->left);
  EXPECT_EQ(tree->root->left->right->parent, tree->root->left);
  EXPECT_EQ(tree->root->right->parent, tree->root);
  EXPECT_EQ(tree->root->right->left->parent, tree->root->right);
  EXPECT_EQ(tree->root->right->right->parent, tree->root->right);
  EXPECT_EQ(tree->root->right->right->right->parent, tree->root->right->right);
  
  // Destroying the tree.
  bst_destroy(tree);
}

TEST(INSERTION, DUPLICATE_DATA) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    bst_insert(tree, &data[i]);
    EXPECT_EQ(bst_insert(tree, &data[i]), nullptr);
  }
  
  // Destroying the tree.
  bst_destroy(tree);
}
