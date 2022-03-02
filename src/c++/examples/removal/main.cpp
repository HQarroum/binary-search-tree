#include <array>
#include <iostream>
#include <sstream>
#include <binary_search_tree.hpp>

/**
 * @brief Displays information about the given tree.
 */
template <typename T>
std::string format(const bst::tree_t<T>& tree) {
  std::stringstream ss;

  ss << "Size : "
    << tree.size()
    << std::endl
    << std::endl
    << tree;
  return (ss.str());
}

int main(void) {
  auto tree = bst::tree_t<int>();

  // Insert the data into the tree.
  tree.insert(50, 70, 60, 20, 90, 10, 40, 100);

  // Displaying the tree.
  std::cout << format(tree) << std::endl;

  // Clearing the tree.
  tree.clear();

  // Displaying the tree.
  std::cout << format(tree) << std::endl;

  // Inserting new elements.
  tree.insert(25, 30, 15, 20, 45);

  // Displaying the tree.
  std::cout << format(tree) << std::endl;

  // Removing nodes.
  for (auto node : tree) {
    tree.remove(node);
  }

  // Displaying the tree.
  std::cout << format(tree) << std::endl;

  // Inserting new elements.
  tree.insert(25, 30, 15, 20, 45);

  // Displaying the tree.
  std::cout << format(tree) << std::endl;

  // Removing nodes.
  tree.remove(25, 30, 15, 20, 45);

  // Displaying the tree.
  std::cout << format(tree) << std::endl;

  return (0);
}