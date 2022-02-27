#include <array>
#include <iostream>
#include "binary_search_tree.hpp"

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

  tree.insert(50, 70, 60, 20, 90, 10, 40, 100);

  for (auto node : tree) {
    std::cout << node << " ";
  }

  tree.clear();

  std::cout << tree << std::endl;

  //std::cout << tree.find(100)->data << std::endl;
  //std::cout << tree.min()->data << std::endl;
}