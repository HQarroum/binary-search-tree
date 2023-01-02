package com.algorithms.trees.bst

/**
 * Describes a node that can be associated with
 * a binary search tree.
 */
data class Node<T>(val value: T) {
  var data             = value
  var left: Node<T>?   = null
  var right: Node<T>?  = null
  var parent: Node<T>? = null

  /**
   * @return the number of children associated
   * with the current node.
   */
  fun children(): Int {
    val array = arrayOf(this.left, this.right)
    var idx   = 0

    for (n in array) {
      if (n == null) {
        break
      }
      idx += 1
    }
    return (idx)
  }
}
