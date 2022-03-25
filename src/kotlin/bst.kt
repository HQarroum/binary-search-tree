package com.algorithms.trees.bst;

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
class BinarySearchTree<T>(comparator: Comparator<T>) : Iterable<T> {
  var root: Node<T>? = null;
  var size: Int      = 0;
  var comparator     = comparator;

  /**
   * @returns the size of the binary-search tree.
   */
  fun size(): Int {
    return (size);
  }

  /**
   * A helper function to attach a node to another node.
   * @param node the node to attach the new node to.
   * @param data the data to associate with the new node.
   * @param direction whether the new node should be attached to the left or right.
   * @return a reference to the newly attached node.
   * @note Complexity is O(log(n)) on average, O(n) on the worst case.
   */
  fun attach(node: Node<T>, value: T, direction: Direction): Node<T> {
    var new_node = Node<T>(value);

    when (direction) {
      Direction.LEFT -> node.left = new_node;
      Direction.RIGHT -> node.right = new_node;
    }

    new_node.parent = node;
    size++;
    return (new_node);
  }

  /**
   * Inserts a new node into the given subtree.
   * @param node the root of the subtree to insert the node into.
   * @param data the data to associate with the new node.
   * @return a pointer to the newly inserted node.
   * @note Complexity is O(log(n)) on average, O(n) on the worst case.
   */
  fun insert_in(node: Node<T>, value: T): Node<T> {
    // Comparing the value associated with the nodes.
    val result = comparator(value, node.value);

    // If the value is less than the node's value,
    // insert the value in the left subtree.
    if (result < 0) {
      return (node.left?.also { insert_in(it, value) } ?: attach(node, value, Direction.LEFT));
    } else if (result > 0) {
      // If the value is greater than the node's value,
      // insert the value in the right subtree.
      return (node.right?.also { insert_in(it, value) } ?: attach(node, value, Direction.RIGHT));
    } else {
      // If the value is equal to the node's value,
      // do nothing.
      return (node);
    }
  }

  /**
   * Inserts the given value in the binary-search tree.
   * @param value the value to insert.
   */
  fun insert(value: T) {
    root?.run {
      insert_in(this, value);
    } ?: {
      root = Node<T>(value);
      size = 1;
    }();
  }

  /**
   * A function to find the node associated with `data`
   * in the given subtree.
   * @param value the value to search for.
   * @param node the root of the subtree to search in.
   * @returns the node associated with the given value,
   * or null if the value is not in the tree.
   */
  fun find(value: T, node: Node<T>? = this.root): Node<T>? {
    if (node == null) {
      return (null);
    }

    // Comparing the value associated with the nodes.
    val result = comparator(value, node.value);

    if (result < 0) {
      // Looking in the left subtree.
      return (find(value, node.left));
    } else if (result > 0) {
      // Looking in the right subtree.
      return (find(value, node.right));
    } else {
      // We found the node.
      return (node);
    }
  }

  /**
   * @return the node with the biggest value in the tree,
   * or null if the tree is empty.
   * @param node an optional node to start the search from.
   */
  fun max(node: Node<T>? = this.root): Node<T>? {
    var current = node;

    while (current != null && current.right != null) {
      current = current.right;
    }
    return (current);
  }

  /**
   * @return the node with the smallest value in the tree,
   * or null if the tree is empty.
   * @param node an optional node to start the search from.
   */
  fun min(node: Node<T>? = this.root): Node<T>? {
    var current = node;

    while (current != null && current.left != null) {
      current = current.left;
    }
    return (current);
  }

  /**
   * Sorts the binary-search tree in ascending order.
   * @param node the root of the subtree to sort.
   * @returns an array containing the sorted values.
   */
  fun sort(node: Node<T>? = this.root): ArrayList<T> {
    var result: ArrayList<T> = ArrayList<T>();

    if (node == null) {
      return (result);
    }

    // Iterating over the nodes using a depth-first iteration
    // and pushing the values to the result array.
    for (item in this) {
      result.add(item);
    }
    return (result);
  }

  /**
   * @returns a depth-first iterator.
   */
  override fun iterator(): Iterator<T> {
    return (DfsIterator(this));
  }
}

fun main() {
  val tree = BinarySearchTree<Int>({ a: Int, b: Int -> a - b });
  
  for (i in arrayOf(50, 70, 60, 20, 90, 10, 40, 100)) {
    tree.insert(i);
  }
  println(tree.root?.value);
  println(tree.root?.left?.value);
  println(tree.root?.right?.value);
  println(tree.root?.left?.left?.value);
  println(tree.root?.left?.right?.value);
  println(tree.max());
  println(tree.min());
  println(tree.find(200));
  println(tree.find(50));
  println(tree.sort());
}
