#include <array>
#include <iostream>
#include <sstream>
#include <assert.h>
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

int main(void) {
  auto tree = bst::tree_t<int>();

  // Insert the data into the tree.
  std::for_each(data.begin(), data.end(), [&tree] (int value) {
    tree.insert(value);
  });

  // Searching for an element.
  auto optional = tree.find(100);
  assert(optional.has_value());
  std::cout << (*optional)->data << std::endl;

  // Searching for many elements using an iterator.
  auto result = tree.find(data.begin(), data.end());
  assert(result.size() == data.size());
  for (auto node : result) {
    std::cout << (*node)->data << " ";
  }
  std::cout << std::endl;

  return (0);
}