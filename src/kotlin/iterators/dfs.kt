package com.algorithms.trees.bst.iterators

import com.algorithms.trees.bst.ITree
import com.algorithms.trees.bst.Node

/**
 * A depth-first-search iterator implementation.
 */
class DfsIterator<T>(tree: ITree<T>) : Iterator<T> {
  private val tree: ITree<T>  = tree
  private var node: Node<T>?  = tree.root()
  private var iterations: Int = 0

  /**
   * @return the next node in the tree.
   */
  override fun next(): T {
    if (iterations == 0) {
      // Initializing the node to the smallest node
      // in the binary search tree.
      node = tree.min()
    } else {
      if (node!!.right != null) {
        node = tree.min(node!!.right)
      } else {
        var current = node!!.parent

        while (current != null && node === current.right) {
          node = current
          current = current.parent
        }
        node = current
      }
    }
    
    iterations++
    return (node?.data!!)
  }

  /**
   * @return true if there are more nodes in the tree,
   * false otherwise.
   */
  override fun hasNext(): Boolean {
    return (iterations < tree.size())
  }
}