package com.algorithms.trees.bst;

/**
 * Describes a node that can be associated with
 * a binary search tree.
 */
data class Node<T>(val value: T) {
  var data             = value;
  var left: Node<T>?   = null;
  var right: Node<T>?  = null;
  var parent: Node<T>? = null;
}
