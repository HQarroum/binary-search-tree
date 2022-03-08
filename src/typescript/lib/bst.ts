import { ITree } from './tree';
import { Node } from './node';
import { DfsIterator } from './iterators/dfs-iterator';

/**
 * @brief Describes the direction binding that can
 * exist between two nodes.
 */
enum Direction {
  LEFT,
  RIGHT
}

/**
 * @brief Definition of the binary search tree.
 */
export class BinarySearchTree<T> implements ITree<T>, Iterable<Node<T>> {

  /**
   * The root node of the tree.
   */
  private root_: Node<T> | null;

  /**
   * The function used to compare two values.
   */
  private comparator: (a: T, b: T) => number;

  /**
   * The size of the tree.
   */
  private size_: number;

  /**
   * Binary-search tree constructor.
   * @param opts the options to pass to the binary-search tree
   * such as the comparator function.
   */
  constructor(opts: { comparator: (a: T, b: T) => number }) {
    this.root_      = null;
    this.comparator = opts.comparator;
    this.size_      = 0;
  }

  /**
   * @returns the size of the binary-search tree.
   */
  size(): number {
    return this.size_;
  }

  /**
   * @returns the root node of the binary-search tree.
   */
  root(): Node<T> | null {
    return this.root_;
  }

  /**
   * @brief A helper function to attach a node to another node.
   * @param node the node to attach the new node to.
   * @param data the data to associate with the new node.
   * @param direction whether the new node should be attached to the left or right.
   * @return a reference to the newly attached node.
   * @note Complexity is O(log(n)) on average, O(n) on the worst case.
   */
  private attach(node: Node<T>, value: T, direction: Direction) {
    const new_node = new Node<T>(value);

    if (direction == Direction.LEFT) {
      node.left = new_node;
    } else {
      node.right = new_node;
    }

    new_node.parent = node;
    new_node.tree = this;
    this.size_++;
    return (new_node);
  }

  /**
   * @brief Inserts a new node into the given subtree.
   * @param node the root of the subtree to insert the node into.
   * @param data the data to associate with the new node.
   * @return a pointer to the newly inserted node.
   * @note Complexity is O(log(n)) on average, O(n) on the worst case.
   */
  private insert_in(node: Node<T>, value: T): Node<T> | null {
    // Comparing the value associated with the nodes.
    const result = this.comparator(value, node.value);

    if (result < 0) {
      return (node.left ?
        this.insert_in(node.left, value) :
        this.attach(node, value, Direction.LEFT)
      );
    } else if (result > 0) {
      return (node.right ?
        this.insert_in(node.right, value) :
        this.attach(node, value, Direction.RIGHT)
      );
    } else {
      return (null);
    }
  }

  insert(value: T): void {
    if (!this.root_) {
      this.root_      = new Node<T>(value);
      this.root_.tree = this;
      this.size_      = 1;
    }
    this.insert_in(this.root_, value);
  }

  find(value: T, node: Node<T> | null = this.root_): Node<T> | null {
    if (!node) {
      return (null);
    }

    // Comparing the value associated with the nodes.
    const result = this.comparator(value, node.value);

    if (result < 0) {
      return (this.find(value, node.left));
    } else if (result > 0) {
      return (this.find(value, node.right));
    } else {
      return (node);
    }
  }

  /**
   * @return the node with the biggest value in the tree,
   * or null if the tree is empty.
   * @param node an optional node to start the search from.
   */
  max(node: Node<T> | null = this.root_): Node<T> | null {
    while (node && node.right != null) {
      node = node.right;
    }
    return (node);
  }

  /**
   * @return the node with the smallest value in the tree,
   * or null if the tree is empty.
   * @param node an optional node to start the search from.
   */
  min(node: Node<T> | null = this.root_): Node<T> | null {
    while (node && node.left != null) {
      node = node.left;
    }
    return (node);
  }

  sort(node: Node<T> | null = this.root_): T[] {
    const result: T[] = [];

    if (!node) {
      return ([]);
    }

    // Iterating over the nodes using a depth-first iteration
    // and pushing the values to the result array.
    this.forEach((node) => result.push(node.value));
    return (result);
  }

  /**
   * @returns a depth-first iterator.
   */
  [Symbol.iterator](): Iterator<Node<T>> {
    return (new DfsIterator<T>(this));
  }

  /**
   * Allows to iterate over the nodes of the tree
   * using a depth-first iteration.
   * @param callback a callback function to call for each
   * node in the tree.
   */
  forEach(callback: (node: Node<T>) => void): void {
    for (const node of this) {
      callback(node);
    }
  }

  toString(node: Node<T> | null = this.root_, result = "", prefix = ""): string {
    if (!node) {
      // We reached the end of a subtree.
      return (result);
    }
    // Concatenate the prefix with the current node's data.
    result += `${prefix}├──${node.value}\n`;
    // Whether the current node is the left child of its parent.
    const isRight = node.parent && node.parent.right == node;
    // A separator to display between the current node's children.
    const separator = isRight ? "│  " : "   ";
    // Recursively display the left children.
    result = this.toString(node.right, result, prefix + separator);
    // Recursively display the left children.
    result = this.toString(node.left, result, prefix + separator);
    return (result);
  }
}
