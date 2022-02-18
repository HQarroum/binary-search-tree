#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "binary_search_tree.h"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

void print_nodes(char* prefix, const bst_node_t* node)
{
    if( node != NULL )
    {
      int left = 0;
      
      if (node->parent) {
        left = node->parent->left == node ? 1 : 0;
      }
      printf("%s", prefix);
      printf("%s", (left ? "├──" : "└──" ));
      printf("%d\n", *(int*) node->data);
      
      char* p1 = calloc(10000, (sizeof(*p1)));
      strcat(p1, prefix);
      strcat(p1, (left ? "│   " : "    "));
      print_nodes(p1, node->left);
      char* p2 = calloc(10000, (sizeof(*p2)));
      strcat(p2, prefix);
      strcat(p2, (left ? "│   " : "    "));
      print_nodes(p2, node->right);
    }
}

void print(const bst_node_t* node)
{
  char* prefix = calloc(10000, (sizeof(*prefix)));
  print_nodes(prefix, node);
  free(prefix);
}

  /** The tree must be layed-out acccording to the following structure. */
  /**                        50                                          */
  /**                       /  \                                         */
  /**                     20     70                                      */
  /**                    /  \   /  \                                     */
  /**                  10   40 60  90                                    */
  /**                               \                                    */
  /**                                100                                 */
static const int data[] = { 50, 70, 60, 20, 90, 10, 40, 100 };

/**
 * @brief Called back for each node in the tree.
 * @param node the currently visited node.
 * @param data a pointer to the user-defined data.
 */
static void default_traversal_callback(const bst_node_t* node, bst_iterator_ctx_t* ctx) {

}

int main(void) {
  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = bst_integer_comparator
  });

  // Inserting nodes in the binary-search tree.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    bst_insert(tree, &data[i]);
  }

  bst_sort_result_t data = bst_sort(tree);
  for (size_t i = 0; i < data.size; ++i) {
    printf("%d\n", *(int*) data.nodes[i]->data);
  }
  free(data.nodes);

  bst_iterator_ctx_t ctx = bst_for_each(tree, &default_traversal_callback, NULL);
  printf("%d\n", ctx.iterations);

  //print(tree->root);
  
  return (0);
}