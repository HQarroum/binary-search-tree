import { Node } from './node';

export interface ITree<T> {
  
  /**
   * @returns the size of the tree.
   */
  size(): number;

  /**
   * @returns the root node of the binary-search tree.
   */
  root(): Node<T> | null;

  /**
   * @return the node with the biggest value in the tree,
   * or null if the tree is empty.
   * @param node an optional node to start the search from.
   */
  max(node?: Node<T>): Node<T> | null;

  /**
   * @return the node with the smallest value in the tree,
   * or null if the tree is empty.
   * @param node an optional node to start the search from.
   */
  min(node?: Node<T>): Node<T> | null;
}