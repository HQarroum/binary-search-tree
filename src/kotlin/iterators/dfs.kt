package com.algorithms.trees.bst;

class DfsIterator<T>(tree: BinarySearchTree<T>) : Iterator<T> {
  val tree: BinarySearchTree<T> = tree;
  var node: Node<T>?            = tree.root;
  var iterations: Int           = 0;

  override fun next(): T {
    if (iterations == 0) {
      // Initializing the node to the smallest node
      // in the binary search tree.
      node = tree.min();
    } else {
      if (node!!.right != null) {
        node = tree.min(node!!.right);
      } else {
        var current = node!!.parent;

        while (current != null && node === current.right) {
          node = current;
          current = current.parent;
        }
        node = current;
      }
    }
    
    iterations++;
    return (node?.data!!);
  }

  override fun hasNext(): Boolean {
    return iterations < tree.size();
  }
}