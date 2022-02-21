#include <binary_search_tree.h>
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

TEST(SEARCH, OF_SPECIFIC_NODE) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    bst_insert(tree, &data[i]);
    EXPECT_EQ(bst_find(tree, &data[i])->data, &data[i]);
  }

  // Destroying the tree.
  bst_destroy(tree);
}

TEST(SEARCH, OF_INVALID_NODE) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    bst_insert(tree, &data[i]);
  }

  const int test_data[] = { 0, 1, 2 };

  EXPECT_EQ(bst_find(tree, &test_data[0]), nullptr);
  EXPECT_EQ(bst_find(tree, &test_data[1]), nullptr);
  EXPECT_EQ(bst_find(tree, nullptr), nullptr);
  EXPECT_EQ(bst_find(nullptr, nullptr), nullptr);

  // Destroying the tree.
  bst_destroy(tree);
}

TEST(SEARCH, OF_SPECIFIC_NODE_IN_SUBTREE) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    bst_insert(tree, &data[i]);
  }

  EXPECT_EQ(bst_find_in(tree->root, &data[0])->data, &data[0]);
  EXPECT_EQ(bst_find_in(tree->root, &data[3])->data, &data[3]);
  EXPECT_EQ(bst_find_in(tree->root->left, &data[5])->data, &data[5]);
  EXPECT_EQ(bst_find_in(tree->root, &data[1])->data, &data[1]);
  EXPECT_EQ(bst_find_in(tree->root->right, &data[2])->data, &data[2]);
  EXPECT_EQ(bst_find_in(tree->root->right, &data[4])->data, &data[4]);
  EXPECT_EQ(bst_find_in(tree->root->right->right, &data[7])->data, &data[7]);

  // Destroying the tree.
  bst_destroy(tree);
}

TEST(SEARCH, MIN_NODE) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    bst_insert(tree, &data[i]);
  }

  EXPECT_EQ(bst_get_min(tree)->data, &data[5]);
  EXPECT_EQ(bst_get_min_from(tree->root)->data, &data[5]);

  // Destroying the tree.
  bst_destroy(tree);
}

TEST(SEARCH, MAX_NODE) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    bst_insert(tree, &data[i]);
  }

  EXPECT_EQ(bst_get_max(tree)->data, &data[7]);
  EXPECT_EQ(bst_get_max_from(tree->root)->data, &data[7]);

  // Destroying the tree.
  bst_destroy(tree);
}
