#include <array>
#include <iostream>
#include <sstream>
#include <binary_search_tree.hpp>

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

/**
 * @brief Displays information about the given tree.
 */
template <typename T>
std::string format(const bst::tree_t<T>& tree) {
  std::stringstream ss;

  ss << "Size : " << tree.size() << std::endl
    << "Min : " << tree.min()->value() << std::endl
    << "Max : " << tree.max()->value() << std::endl
    << std::endl << tree;
  return (ss.str());
}

int main(void) {
  auto tree = bst::tree_t<int>();

  // Insert the data manually into the tree.
  std::for_each(data.begin(), data.end(), [&tree] (int value) {
    tree.insert(value);
  });

  // Displaying the tree.
  std::cout << format(tree) << std::endl;

  // Inserting elements inline.
  tree.insert(30, 15, 25, 35, 45, 55, 65, 75, 85, 95, 150);

  // Displaying the tree.
  std::cout << format(tree) << std::endl;

  // Inserting elements using a container iterator.
  auto array = array_of<int>(50, 22, 56);
  tree.insert(array.begin(), array.end());

  // Displaying the tree.
  std::cout << format(tree) << std::endl;

  return (0);
}