#include <binary_search_tree.hpp>
#include <gtest/gtest.h>
#include <stdint.h>

/**
 * @brief A helper function used to construct an array at compile-time.
 * @param t the list of values of type `T` to insert in the array.
 * @return a static constant array of `T` values.
 */
template <typename V, typename... T>
constexpr auto array_of(T&&... t) -> std::array <V, sizeof...(T)> {
  return {{ std::forward<T>(t)... }};
}

/** The tree must be layed-out acccording to the following structure. */
/**                        50                                          */
/**                       /  \                                         */
/**                     20     70                                      */
/**                    /  \   /  \                                     */
/**                  10   40 60  90                                    */
/**                               \                                    */
/**                                100                                 */
static constexpr auto data = array_of<int>(50, 70, 60, 20, 90, 10, 40, 100);

TEST(SEARCH, OF_SPECIFIC_NODE) {
  // Creating a new binary search tree.
  auto tree = bst::tree_t<int>();

  // Inserting the data.
  for (auto value : data) {
    tree.insert(value);
    auto optional = tree.find(value);
    EXPECT_EQ((*optional)->value(), value);
  }
}

TEST(SEARCH, OF_SPECIFIC_NODE_IN_SUBTREE) {
  // Creating a new binary search tree.
  auto tree = bst::tree_t<int>();

  // Inserting the data.
  for (auto value : data) {
    tree.insert(value);
  }

  EXPECT_EQ((*tree.find(tree.root(), data[0]))->value(), data[0]);
  EXPECT_EQ((*tree.find(tree.root(), data[3]))->value(), data[3]);
  EXPECT_EQ((*tree.find(tree.root()->left, data[5]))->value(), data[5]);
  EXPECT_EQ((*tree.find(tree.root(), data[1]))->value(), data[1]);
  EXPECT_EQ((*tree.find(tree.root()->right, data[2]))->value(), data[2]);
  EXPECT_EQ((*tree.find(tree.root()->right, data[4]))->value(), data[4]);
  EXPECT_EQ((*tree.find(tree.root()->right->right, data[7]))->value(), data[7]);
}

TEST(SEARCH, MIN_NODE) {
  // Creating a new binary search tree.
  auto tree = bst::tree_t<int>();

  // Inserting the data.
  for (auto value : data) {
    tree.insert(value);
  }

  EXPECT_EQ(tree.min()->value(), data[5]);
  EXPECT_EQ(tree.min(tree.root())->value(), data[5]);
}

TEST(SEARCH, MAX_NODE) {
  // Creating a new binary search tree.
  auto tree = bst::tree_t<int>();

  // Inserting the data.
  for (auto value : data) {
    tree.insert(value);
  }

  EXPECT_EQ(tree.max()->value(), data[7]);
  EXPECT_EQ(tree.max(tree.root())->value(), data[7]);
}
