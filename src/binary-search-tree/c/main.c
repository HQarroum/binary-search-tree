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

void callback(const bst_node_t* node, void* user_data) {
  bst_search_ctx_t* ctx = (bst_search_ctx_t*) user_data;

  /* Comparing the value associated with the nodes. */
  int result = node->tree->options.comparator(ctx->data, node->data);

  if (!result) {
    ctx->result = node;
  }
  ctx->iterations++;
}

int main(void) {
  srand(time(NULL));

  // Creating a new binary search tree.
  bst_tree_t* tree = bst_create((bst_options_t) {
    .comparator = bst_integer_comparator
  });

  // Sample data to insert.
  int data[] = { 50, 30, 70, 20, 40, 60, 80 };

  // Inserting nodes in the binary-search tree.
  for (size_t i = 0; i < ARRAY_SIZE(data); ++i) {
    bst_insert(tree, &data[i]);
  }
  
  char* prefix = calloc(10000, (sizeof(*prefix)));
  print_nodes(prefix, tree->root);
  free(prefix);
  
  // bst_search_ctx_t ctx = {
  //   .data = &data[0],
  //   .result = NULL,
  //   .iterations = 0
  // };

  //bst_traverse(tree, &callback, &bst_search_traversal, &ctx);
  //printf("Found %d in %d iterations\n", *(int*) ctx.result->data, ctx.iterations);
  const bst_node_t* result = bst_get_kth_smallest(tree, 2);
  printf("%d\n", result);
  if (result) printf("%d\n", *(int*)result->data);
  return (0);
}