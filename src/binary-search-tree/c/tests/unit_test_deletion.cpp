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
  /**                             /  \                                    */
  /**                            89  100                                 */
static const int data[] = { 50, 70, 60, 20, 90, 10, 40, 100, 89 };

TEST(DELETION, OF_NODES) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    bst_insert(tree, &data[i]);
  }

  // Deleting a node with no leafs.
  /**                        50                                          */
  /**                       /  \                                         */
  /**                     20     70                                      */
  /**                    /  \   /  \                                     */
  /**                  10   40 60  90                                    */
  /**                             /                                      */
  /**                            89                                      */
  bst_remove(tree, &data[7]);
  EXPECT_EQ(bst_find(tree, &data[7]), (bst_node_t*) NULL);
  EXPECT_EQ(bst_size(tree), ARRAY_SIZE(data) - 1);

  // Deleting a node with one leaf.
  /**                        50                                          */
  /**                       /  \                                         */
  /**                     20     70                                      */
  /**                    /  \   /  \                                     */
  /**                  10   40 60  89                                    */
  bst_remove(tree, &data[4]);
  EXPECT_EQ(bst_find(tree, &data[4]), (bst_node_t*) NULL);
  EXPECT_EQ(bst_size(tree), ARRAY_SIZE(data) - 2);
  EXPECT_EQ(*static_cast<const int*>(tree->root->right->right->data), 89);
  EXPECT_EQ(tree->root->right->right->left, (bst_node_t*) NULL);
  EXPECT_EQ(tree->root->right->right->right, (bst_node_t*) NULL);

  // Deleting a node with two leafs.
  /**                        50                                          */
  /**                       /  \                                         */
  /**                     20   89                                        */
  /**                    /  \   /                                        */
  /**                  10   40 60                                        */
  bst_remove(tree, &data[1]);
  EXPECT_EQ(bst_find(tree, &data[1]), (bst_node_t*) NULL);
  EXPECT_EQ(bst_size(tree), ARRAY_SIZE(data) - 3);
  EXPECT_EQ(*static_cast<const int*>(tree->root->right->data), 89);
  EXPECT_EQ(tree->root->right->right, (bst_node_t*) NULL);
  EXPECT_EQ(*static_cast<const int*>(tree->root->right->left->data), 60);

  // Deleting the root node.
  /**                        60                                          */
  /**                       /  \                                         */
  /**                     20   89                                        */
  /**                    /  \                                            */
  /**                  10   40                                           */
  bst_remove(tree, &data[0]);
  EXPECT_EQ(bst_find(tree, &data[0]), (bst_node_t*) NULL);
  EXPECT_EQ(bst_size(tree), ARRAY_SIZE(data) - 4);
  EXPECT_EQ(*static_cast<const int*>(tree->root->right->data), 89);
  EXPECT_EQ(tree->root->right->right, (bst_node_t*) NULL);
  EXPECT_EQ(tree->root->right->left, (bst_node_t*) NULL);

  // Destroying the tree.
  bst_destroy(tree);
}

TEST(DELETION, OF_NODES_IN_SUBTREE) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    bst_insert(tree, &data[i]);
  }

  /**                        50                                          */
  /**                       /  \                                         */
  /**                     40     70                                      */
  /**                    /      /  \                                     */
  /**                  10      60  90                                    */
  /**                             /                                      */
  /**                            89                                      */
  bst_remove_from(tree->root->left, &data[3]);
  EXPECT_EQ(bst_find(tree, &data[3]), (bst_node_t*) NULL);
  EXPECT_EQ(bst_size(tree), ARRAY_SIZE(data) - 1);
  EXPECT_EQ(*static_cast<const int*>(tree->root->left->data), 40);

  // Destroying the tree.
  bst_destroy(tree);
}

TEST(DELETION, OF_ALL_NODES) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    bst_insert(tree, &data[i]);
  }

  bst_clear(tree);
  EXPECT_EQ(bst_size(tree), 0);
  EXPECT_EQ(tree->root, (bst_node_t*) NULL);

  // Destroying the tree.
  bst_destroy(tree);
}

TEST(DELETION, OF_ALL_NODES_IN_SUBTREE) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = &bst_integer_comparator
  });

  // Inserting the data.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    bst_insert(tree, &data[i]);
  }

  /**                        50                                          */
  /**                       /                                            */
  /**                     20                                             */
  /**                    /  \                                            */
  /**                  10   40                                           */
  /**                                                                    */
  /**                                                                    */
  bst_clear_from(tree->root->right);
  EXPECT_EQ(bst_size(tree), 4);

  // Destroying the tree.
  bst_destroy(tree);
}
