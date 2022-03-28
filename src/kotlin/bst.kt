package com.algorithms.trees.bst

import com.algorithms.trees.bst.iterators.DfsIterator
import com.algorithms.trees.bst.ITree

/**
 * Type definition for a comparator function.
 */
typealias Comparator<T> = (T, T) -> Int

/**
 * Describes the direction binding that can
 * exist between two nodes.
 */
enum class Direction {
  LEFT,
  RIGHT
}

/**
 * A binary-search tree is a rooted binary tree data structure
 * whose internal nodes each store a key greater than all the keys
 * in the node's left subtree and less than those in its right subtree.
 */
class BinarySearchTree<T>(private val comparator: Comparator<T>) : ITree<T>, Iterable<T> {
  private var root: Node<T>? = null
  private var size: Int      = 0

  /**
   * @return the root node of the binary-search tree.
   */
  override fun root(): Node<T>? {
    return (this.root)
  }

  /**
   * @return the size of the binary-search tree.
   */
  override fun size(): Int {
    return (size)
  }

  /**
   * A helper function to attach a node to another node.
   * @param node the node to attach the new node to.
   * @param value the data to associate with the new node.
   * @param direction whether the new node should be attached to the left or right.
   * @return a reference to the newly attached node.
   * @note Complexity is O(log(n)) on average, O(n) on the worst case.
   */
  private fun attach(node: Node<T>, value: T, direction: Direction): Node<T> {
    val newNode = Node(value)

    when (direction) {
      Direction.LEFT -> node.left = newNode
      Direction.RIGHT -> node.right = newNode
    }

    newNode.parent = node
    size += 1
    return (newNode)
  }

  /**
   * Inserts a new node into the given subtree.
   * @param node the root of the subtree to insert the node into.
   * @param value the data to associate with the new node.
   * @return a pointer to the newly inserted node.
   * @note Complexity is O(log(n)) on average, O(n) on the worst case.
   */
  private fun insertIn(node: Node<T>, value: T): Node<T> {
    // Comparing the value associated with the nodes.
    val result = comparator(value, node.value)

    return when {
      // If the value is less than the node's value,
      // insert the value in the left subtree.
      result < 0 -> node.left?.also { insertIn(it, value) } ?: attach(node, value, Direction.LEFT)
      // If the value is greater than the node's value,
      // insert the value in the right subtree.
      result > 0 -> node.right?.also { insertIn(it, value) } ?: attach(node, value, Direction.RIGHT)
      // If the value is equal to the node's value,
      // do nothing.
      else -> node
    }
  }

  /**
   * Inserts the given value in the binary-search tree.
   * @param value the value to insert.
   */
  override fun insert(value: T) {
    root?.run {
      insertIn(this, value)
    } ?: run {
      root = Node(value)
      size = 1
    }
  }

  /**
   * Private method used to recursively remove the node associated with `data`
   * from the given subtree.
   * @param node The node to remove from the binary-search tree.
   * @param value The data associated with the node to remove.
   */
  private fun remove_in(node: Node<T>?, value: T): Node<T>? {
    if (node == null) {
      return (null)
    }

    // Comparing the given data to the current node's data.
    val result = this.comparator(value, node.value)

    if (result < 0)
      node.left = this.remove_in(node.left, value)
    else if (result > 0)
      node.right = this.remove_in(node.right, value)
    else {
      if (node.left == null && node.right == null) {
        // The node has no children.
        if (this.root == node) {
          this.root = null
        }
        this.size -= 1
        return (null)
      } else if (node.left == null || node.right == null) {
        // The node has a single child.
        val successor = if (node.right != null) node.right else node.left
        successor!!.parent = node.parent
        if (this.root == node) {
          this.root = successor
        }
        this.size -= 1
        return (successor)
      } else {
        // The node has two children.
        val successor = this.min(node.right)
        node.data = successor?.data!!
        node.right = this.remove_in(node.right, successor.data!!)
      }
    }
    return (node)
  }
  
  /**
   * Removes the node associated with `data` from the binary-search tree.
   * @param data The data associated with the node to remove.
   */
  override fun remove(data: T) {
    this.remove_in(this.root, data)
  }

  /**
   * @brief Clears the given subtree.
   * @param node the root of the subtree to clear.
   * @note Complexity is O(n) on average.
   */
  fun clear(node: Node<T>?) {
    if (node == null) return

    // Recursively clear the left subtree.
    clear(node.left)
    clear(node.right)

    // Detaching the node from its parent.
    when {
      node.parent?.left == node -> node.parent?.left = null
      node.parent?.right == node -> node.parent?.right = null
    }

    // Decrementing the size of the tree.
    size -= 1

    // If the node is the root, we need to assign
    // the root to a null pointer type.
    if (root == node) {
      root = null
    }
  }

  /**
   * @brief Clears the binary-search tree.
   * @return the number of nodes removed from the tree.
   * @note Complexity is O(n) on average.
   */
  fun clear() {
    this.clear(this.root)
  }

  /**
   * A function to find the node associated with `data`
   * in the given subtree.
   * @param value the value to search for.
   * @param node the root of the subtree to search in.
   * @returns the node associated with the given value,
   * or null if the value is not in the tree.
   */
  override fun find(value: T, node: Node<T>?): Node<T>? {
    if (node == null) {
      return (null)
    }

    // Comparing the value associated with the nodes.
    val result = comparator(value, node.value)

    return when {
      // Looking in the left subtree.
      result < 0 -> find(value, node.left)
      // Looking in the right subtree.
      result > 0 -> find(value, node.right)
      // We found the node.
      else -> node
    }
  }

  /**
   * @return the node with the biggest value in the tree,
   * or null if the tree is empty.
   * @param node an optional node to start the search from.
   */
  override fun max(node: Node<T>?): Node<T>? {
    var current = node

    while (current?.right != null) {
      current = current.right
    }
    return (current)
  }

  /**
   * @return the node with the smallest value in the tree,
   * or null if the tree is empty.
   * @param node an optional node to start the search from.
   */
  override fun min(node: Node<T>?): Node<T>? {
    var current = node

    while (current?.left != null) {
      current = current.left
    }
    return (current)
  }

  /**
   * Sorts the binary-search tree in ascending order.
   * @param node the root of the subtree to sort.
   * @returns an array containing the sorted values.
   */
  override fun sort(node: Node<T>?): ArrayList<T> {
    val result = ArrayList<T>()

    if (node == null) {
      return (result)
    }

    // Iterating over the nodes using a depth-first iteration
    // and pushing the values to the result array.
    for (item in this) {
      result.add(item)
    }
    return (result)
  }

  /**
   * @returns a depth-first iterator.
   */
  override fun iterator(): Iterator<T> {
    return (DfsIterator(this))
  }

  /**
   * @param node the root of the subtree to display.
   * @param result the string representation of the subtree.
   * @param prefix a prefix to add to each line.
   * @returns a string representation of the binary-search tree.
   */
  private fun print(node: Node<T>? = this.root, result: String = "", prefix: String = ""): String {
    var resultStr = result

    if (node == null) {
      // We reached the end of a subtree.
      return (result)
    }
    // Concatenate the prefix with the current node's data.
    resultStr += "${prefix}├──${node.value}\n"
    // Whether the current node is the left child of its parent.
    val isRight = node.parent?.right == node
    // A separator to display between the current node's children.
    val separator = if (isRight) "│  " else "   "
    // Recursively display the left children.
    resultStr = print(node.right, resultStr, prefix + separator)
    // Recursively display the left children.
    resultStr = print(node.left, resultStr, prefix + separator)
    return (resultStr)
  }

  /**
   * Returns a string representation of the binary-search tree.
   */
  override fun toString(): String {
    return (print(this.root))
  }
}
