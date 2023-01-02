package com.algorithms.trees.bst

interface ITree<T> {

  /**
   * @returns the size of the tree.
   */
  fun size(): Int

  /**
   * @returns the root node of the binary-search tree.
   */
  fun root(): Node<T>?

  /**
   * A function to find the node associated with `data`
   * in the given subtree.
   * @param value the value to search for.
   * @param node the root of the subtree to search in.
   * @returns the node associated with the given value,
   * or null if the value is not in the tree.
   */
  fun find(value: T, node: Node<T>? = root()): Node<T>?

  /**
   * @return the node with the biggest value in the tree,
   * or null if the tree is empty.
   * @param node an optional node to start the search from.
   */
  fun max(node: Node<T>? = root()): Node<T>?

  /**
   * @return the node with the smallest value in the tree,
   * or null if the tree is empty.
   * @param node an optional node to start the search from.
   */
  fun min(node: Node<T>? = root()): Node<T>?

  /**
   * Inserts the given value in the binary-search tree.
   * @param value the value to insert.
   */
  fun insert(value: T)

  /**
   * Removes the node associated with `data` from the binary-search tree.
   * @param data The data associated with the node to remove.
   */
  fun remove(data: T)

  /**
   * Sorts the binary-search tree in ascending order.
   * @param node the root of the subtree to sort.
   * @returns an array containing the sorted values.
   */
  fun sort(node: Node<T>? = root()): ArrayList<T>
}