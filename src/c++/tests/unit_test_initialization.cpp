#include <binary_search_tree.hpp>
#include <gtest/gtest.h>
#include <stdint.h>

TEST(INITIALIZATION, OF_TREE) {
  // Creating a new binary search tree.
  auto tree = bst::tree_t<int>();

  EXPECT_EQ(tree.size(), (size_t) 0);
}

TEST(INITIALIZATION, OF_TREE_WITH_INVALID_COMPARATOR) {
  
}

TEST(INITIALIZATION, OF_NODE) {
  // Creating a new node.
  auto node = bst::node_t<int>(50);

  EXPECT_EQ(node.left, nullptr);
  EXPECT_EQ(node.right, nullptr);
  EXPECT_EQ(node.parent, nullptr);
  EXPECT_EQ(node.tree, nullptr);
  EXPECT_EQ(node.value(), 50);
}

TEST(INITIALIZATION, OF_NODE_WITH_INVALID_DATA) {
  
}
