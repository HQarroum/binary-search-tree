#include "binary_search_tree.hpp"

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

int main(void) {
  bst::tree_t<int> tree = bst::tree_t<int>();

  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    tree.insert(&data[i]);
  }
}