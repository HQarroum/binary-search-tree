import { ITree } from './tree';

/**
 * Describes a node that can be associated with
 * a binary search tree.
 */
export class Node<T> {
    public value: T;
    public left: Node<T> | null;
    public right: Node<T> | null;
    public parent: Node<T> | null;
    public tree: ITree<T> | null;

    /**
     * Node constructor.
     * @param value the value to associate with the node.
     */
    constructor(value: T) {
      this.value = value;
      this.left = null;
      this.right = null;
      this.parent = null;
      this.tree = null;
    }
}
