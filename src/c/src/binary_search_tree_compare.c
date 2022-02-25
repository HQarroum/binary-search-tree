#include <binary_search_tree.h>

/**
 * @brief A function implementation comparing the value of two nodes as integers.
 * @param a the value of the reference node.
 * @param b the value of the compared node.
 * @return 0 if the values are equal, a negative value if the value of `a` is less than `b`,
 * and a positive value if the value of `a` is greater than `b`.
 */
int bst_integer_comparator(const void* a, const void* b) {
  return (*(const int*)a - *(const int*)b);
}

/**
 * @brief A function implementation comparing the value of two nodes as strings.
 * @param a the value of the reference node.
 * @param b the value of the compared node.
 * @return 0 if the values are equal, a negative value if the value of `a` is less than `b`,
 * and a positive value if the value of `a` is greater than `b`.
 */
int bst_string_comparator(const void* a, const void* b) {
  return (strcmp((const char*)a, (const char*)b));
}
