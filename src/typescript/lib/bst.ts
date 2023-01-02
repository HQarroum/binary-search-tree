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

    if (direction === Direction.LEFT) {
      node.left = new_node;
    } else {
      node.right = new_node;
    }

    new_node.parent = node;
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

  /**
   * Inserts the given value in the binary-search tree.
   * @param value the value to insert.
   */
  insert(value: T): void {
    if (!this.root_) {
      this.root_ = new Node<T>(value);
      this.size_ = 1;
    }
    this.insert_in(this.root_, value);
  }

  /**
   * A function to find the node associated with `data`
    in the given subtree.
   * @param value the value to search for.
   * @param node the root of the subtree to search in.
   * @returns the node associated with the given value,
   * or null if the value is not in the tree.
   */
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
   * Private method used to recursively remove the node associated with `data`
   * from the given subtree.
   * @param node The node to remove from the binary-search tree.
   * @param data The data associated with the node to remove.
   */
  remove_in(node: Node<T> | null, data: T): Node<T> | null {
    if (!node) {
      return (null);
    }

    // Comparing the given data to the current node's data.
    const result = this.comparator(data, node.value);

    if (result < 0)
      node.left = this.remove_in(node.left, data);
    else if (result > 0)
      node.right = this.remove_in(node.right, data);
    else {
      if (!node.left && !node.right) {
        // The node has no children.
        if (this.root_ == node) {
          this.root_ = null;
        }
        this.size_ -= 1;
        return (null);
      } else if (!node.left || !node.right) {
        // The node has a single child.
        const successor = node.right ? node.right : node.left;
        successor!!.parent = node.parent;
        if (this.root_ == node) {
          this.root_ = successor;
        }
        this.size_ -= 1;
        return (successor);
      } else {
        // The node has two children.
        const successor = this.min(node.right);
        node.value = successor?.value!!;
        node.right = this.remove_in(node.right, successor?.value!!);
      }
    }
    return (node);
  }
  
  /**
   * Removes the node associated with `data` from the binary-search tree.
   * @param data The data associated with the node to remove.
   * @returns 
   */
  remove(data: T): void {
    this.remove_in(this.root_, data);
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

  /**
   * A helper function to compute the kth value in the given subtree
   * iterating from the left or the right direction.
   * @param k the kth number to find.
   * @param direction the direction to iterate towards.
   * @param node the root of the subtree to search.
   * @returns a node with the kth value or null if the tree is empty.
   */
  private kth_number(k: number, direction: Direction, node: Node<T> | null = this.root_): Node<T> | null {
    return (function iterate (node: Node<T> | null): Node<T> | null {
      if (!node) {
        return (null);
      }

      // Iterating until we find the smallest node.
      const result = iterate(direction === Direction.LEFT ? node.left : node.right);

      if (result) {
        return (result);
      }

      // Once we reached the largest value, we decrement k for each
      // number of nodes traversed backwards.
      k = k - 1;

      // If the current node is the kth smallest, we return it.
      if (k == 0) {
        return (node);
      }

      return (iterate(direction === Direction.LEFT ? node.right : node.left));
    })(node);
  }

  /**
   * Computes the kth smallest value in the given subtree.
   * @param k The kth smallest value in the binary-search tree.
   * @param node The root of the subtree to search in.
   * @returns the kth smallest value in the binary-search tree,
   * or null if the tree is empty.
   */
  kth_smallest(k: number, node: Node<T> | null = this.root_): Node<T> | null {
    return (this.kth_number(k, Direction.LEFT, node));
  }

  /**
   * Computes the kth largest value in the given subtree.
   * @param k The kth largest value in the binary-search tree.
   * @param node The root of the subtree to search in.
   * @returns the kth largest value in the binary-search tree,
   * or null if the tree is empty.
   */
  kth_largest(k: number, node: Node<T> | null = this.root_): Node<T> | null {
    return (this.kth_number(k, Direction.RIGHT, node));
  }

  /**
   * Sorts the binary-search tree in ascending order.
   * @param node the root of the subtree to sort.
   * @returns an array containing the sorted values.
   */
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

  /**
   * @param node the root of the subtree to display.
   * @param result the string representation of the subtree.
   * @param prefix a prefix to add to each line.
   * @returns a string representation of the binary-search tree.
   */
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
